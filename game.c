/*******************************************************************************
* 
* FILENAME : game.c
*
* DESCRIPTION : Source file containing main game loop
*
* AUTHOR : filipang           
* 
* START DATE :    5/11/2021
*
*******************************************************************************/

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <time.h>

#include "vector.h"

#include "transform.h"
#include "animation.h"
#include "temporary_animation.h"
#include "item.h"
#include "active.h"
#include "creature.h"
#include "map.h"
#include "game.h"
#include "entity.h"

#include "utils.h"
#include "memory.h"
#include "input.h"
#include "graphics.h"
#include "audio.h"
#include "ui.h"
//#include "tests.h"

MemoryArena *global_memory;

#include "vector.c"

#include "utils.c"
#include "memory.c"
#include "input.c"
#include "graphics.c"
#include "audio.c"
#include "ui.c"
//#include "tests.c"

#include "transform.c"
#include "animation.c"
#include "temporary_animation.c"
#include "item.c"
#include "active.c"
#include "creature.c"
#include "map.c"
#include "entity.c"

void gameTimeWindUp()
{
	PersistentGameState *state = memoryGetPersistentGameState();
	state->game_speed += 1;
	if(state->game_speed > 1)
	{
		state->game_speed = 1;
	}
}

void gameTimeWindDown()
{
	PersistentGameState *state = memoryGetPersistentGameState();
	state->game_speed -= 0.02;
	if(state->game_speed < 0)
	{
		state->game_speed = 0;
	}

}

Vector2f gameSpawnRandomCoords()
{
	Vector2f map_pos;
	Vector2f player_position = entityGetPlayer()->transform.position;
	do
	{	   
		map_pos = mapGridToCoords(vector2i(rand() % 18 + 1, 
										   rand() % 18 + 1
										   ));
	} while(vector2fDistance(player_position, map_pos) < 100);

	return map_pos;
}

void gameLoadFirstLevel()
{
	PersistentGameState *state = memoryGetPersistentGameState();
	mapLoadTest();
	creatureCreateEnemy(mapGridToCoords(vector2i(6, 5)), 0);
	activeCreateRandomize(mapGridToCoords(vector2i(8, 8)), 0);
	activeCreateStairsDown(mapGridToCoords(vector2i(12, 8)), 0);

	state->camera_transform.render.w = SCREEN_WIDTH;
	state->camera_transform.render.h = SCREEN_HEIGHT;
	state->camera_transform.collider.w = SCREEN_WIDTH;
	state->camera_transform.collider.h = SCREEN_HEIGHT;
}

void gameLoadNextLevel()
{
	PersistentGameState *state = memoryGetPersistentGameState();

	mapLoadTest();
	srand(time(NULL));

	for(int i = 0; i < 3 * state->current_level; i++)
	{
		creatureCreateEnemy(gameSpawnRandomCoords(), state->current_level);
	}

	int skipped_entities = 0;
	for(int i = 0; i < state->entity_count + skipped_entities; i++)
	{
		Entity *entity_ptr = entityGet(i);
		if(entity_ptr && entity_ptr->created)
		{
			if(entity_ptr->has_active &&
			   entity_ptr->transform.level == state->current_level-1 && 
			   entity_ptr->active.active_action == ACTIVE_STAIRS_DOWN)
			{
				activeCreateStairsUp(entity_ptr->transform.position, state->current_level);
			}
		}
		else
		{
			skipped_entities++;
		}
	}

	activeCreateStairsDown(gameSpawnRandomCoords(), state->current_level);

	itemCreateHealthPotion(gameSpawnRandomCoords(), state->current_level);

	itemCreateDamageScroll(gameSpawnRandomCoords(), state->current_level);


	state->camera_transform.render.w = SCREEN_WIDTH;
	state->camera_transform.render.h = SCREEN_HEIGHT;
}

void gameInitializeState()
{
	gameLoadFirstLevel();
	PersistentGameState *state = memoryGetPersistentGameState();

	Vector2f vec = mapGridToCoords(vector2i(10, 10));
	creatureCreatePlayer(vec, state->current_level);
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 5; j++)
		{
			state->player.inventory[i][j] = -1;
		}
	}
	state->game_speed = 1;
}

void gameProcessCamera()
{
	PersistentGameState *state = memoryGetPersistentGameState();
	Map *map_ptr = mapGetCurrent();

	Entity *player_entity = entityGetPlayer();
	Creature *player_creature = &player_entity->creature;
	if(!player_entity)
	{
		printf("game.c: Camera exception: Seems like player was killed.\n");
		return;
	}
	Transform *player_transform = &player_entity->transform;

	Vector2f map_size = 
	{
		map_ptr->size.x * map_ptr->tile_len,
	    map_ptr->size.y * map_ptr->tile_len
	};

	Transform *camera_transform = &state->camera_transform;
	camera_transform->position.x = player_transform->position.x;
	camera_transform->position.y = player_transform->position.y;

	if(camera_transform->position.x - camera_transform->render.w/2 < 0)
	{
		camera_transform->position.x = camera_transform->render.w/2;
	}

	if(camera_transform->position.y - camera_transform->render.h/2 < 0)
	{
		camera_transform->position.y = camera_transform->render.h/2;
	}

	if(camera_transform->position.x + camera_transform->render.w/2 > 
	   map_size.x)
	{
		camera_transform->position.x = 
			map_size.x - camera_transform->render.w/2;
	}

	if(camera_transform->position.y + camera_transform->render.h/2 >
	   map_size.y)
	{
		camera_transform->position.y = 
			map_size.y - camera_transform->render.h/2;
	}
}

void gameCheckDeath(int *quit)
{
	if(!entityGetPlayer())
	{
		*quit = 1;
	}
}

void gameProcessFrame(int *quit)
{
	TransientGameState *ui_state = memoryGetTransientGameState();
	InputState *input = memoryGetInputState();
	ui_state->highlight_id =   -1;
	ui_state->highlight_type = -1;

	entityProcessList();	

	gameCheckDeath(quit);
	uiProcessInventory();

	gameProcessCamera();
	if(input->debug.key_press)
	{
		ui_state->draw_debug = (ui_state->draw_debug + 1)%2;
	}
}

void gameUpdatePlayerStats()
{
	PersistentGameState *state = memoryGetPersistentGameState();
	for(int i = 0; i < EQUIPPED_ITEM_COUNT; i++)
	{
		Entity *item_entity = entityGet(state->player.equipped_items[i]);	
		Item *item_ptr = &item_entity->item;
		if(item_ptr)
		{

		}
	}
}

int main(int argc, char* args[])
{
	memoryAllocGame();
	GraphicsState *sdl_state = memoryGetGraphicsState();	
	PersistentGameState *state = memoryGetPersistentGameState();

	#ifndef TEST_BATCH_1	
	gameInitializeState(); 
	#endif
	// Start up SDL and create window
    if( !graphicsInitialize() )
    {
        printf( "Failed to initialize graphics!\n" );
		return 0;
    }
	if( audioInitialize() == -1)
	{
		printf( "Failed to initialize audio!\n" );
		return 0;
	}
	int quit = 0;
	double target_frame_time = 1000/60.0;

	#ifdef TEST_BATCH_1
	testBatch1();
	#endif

	long long start_ticks;
	long long current_ticks = 0;
	long long frequency = SDL_GetPerformanceFrequency();

	char cap_frames = 0;
	long long target_ms = 10;
	long long target_ticks = target_ms * frequency;


	while(!quit)
	{
		// Start frame timer
		
		start_ticks = current_ticks;
		// Handle events on queue
		while( SDL_PollEvent( &sdl_state->event ) != 0 )
		{
			// User requests quit
			if( sdl_state->event.type == SDL_QUIT )
				quit = 1;

			inputProcessEvent();

			uiProcessEvent(); 
		}

		#ifndef TEST_BATCH_1
		inputProcessState();

		gameProcessFrame(&quit);
	
		graphicsProcessFrame();	
		#endif

		// End frame timer
		
		#ifndef TEST_BATCH_1

		SDL_Delay(4);
		current_ticks = SDL_GetPerformanceCounter();
		long long elapsed_ticks = current_ticks - start_ticks;

		state->true_delta_time = (double)elapsed_ticks / frequency;
		state->true_time += state->true_delta_time;

//		state->player_action = 1;
		if(state->player_action)
		{	
			gameTimeWindUp();
		}
		else
		{
			gameTimeWindDown();
		}
		state->game_delta_time = state->true_delta_time * state->game_speed;
		state->game_time += state->game_delta_time;
		#endif
	}

    // Free resources and close SDL
	free(global_memory);	
    graphicsClose(sdl_state);

	return 0;
}
