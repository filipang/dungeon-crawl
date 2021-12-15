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
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <time.h>

#include "vector.h"

#include "transform.h"
#include "item.h"
#include "active.h"
#include "creature.h"
#include "map.h"
#include "game.h"

#include "utils.h"
#include "memory.h"
#include "input.h"
#include "graphics.h"
#include "ui.h"
#include "tests.h"

MemoryArena *global_memory;

#include "vector.c"

#include "utils.c"
#include "memory.c"
#include "input.c"
#include "graphics.c"
#include "ui.c"
#include "tests.c"

#include "transform.c"
#include "item.c"
#include "active.c"
#include "creature.c"
#include "map.c"

void gameLoadFirstLevel()
{
	PersistentGameState *state = memoryGetPersistentGameState();
	mapLoadTest();
	creatureCreateEnemy(mapGridToCoords(vector2i(6, 5)));
	activeCreateRandomize(mapGridToCoords(vector2i(8, 8)));
	activeCreateStairsDown(mapGridToCoords(vector2i(12, 8)));

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

	for(int i = 0; i < state->current_level; i++)
	{
		creatureCreateEnemy(mapGridToCoords(vector2i(rand()%17 + 1, rand()%17 + 1)));
	}

	activeCreateRandomize(mapGridToCoords(vector2i(8, 8)));
	for(int i = 0; i < state->active_count; i++)
	{
		Active *active_ptr = activeGet(i);
		if(active_ptr->level == state->current_level-1 && 
		   active_ptr->active_action == ACTIVE_STAIRS_DOWN)
		{
			Transform *transform = (Transform *)active_ptr; 
			activeCreateStairsUp(transform->position);
		}
	}

	activeCreateStairsDown(mapGridToCoords(vector2i(
						   rand()%17 + 1, 
						   rand() % 17 + 1
					 	   )));

	for(int i = 0; i < 15; i++)
	{
		itemCreateTest(mapGridToCoords(vector2i(
							   		       rand()%17 + 1, 
							   			   rand() % 17 + 1
							   		   )));
	}
	state->camera_transform.render.w = SCREEN_WIDTH;
	state->camera_transform.render.h = SCREEN_HEIGHT;
}

void gameInitializeState()
{
	gameLoadFirstLevel();
	PersistentGameState *state = memoryGetPersistentGameState();

	Vector2f vec = mapGridToCoords(vector2i(10, 10));
	creatureCreatePlayer(vec);
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 5; j++)
		{
			state->player.inventory[i][j] = -1;
		}
	}
}

void gameProcessCamera()
{
	PersistentGameState *state = memoryGetPersistentGameState();
	Map *map_ptr = mapGetCurrent();

	Creature *player_creature = creatureGet(state->player.creature_id);
	if(!player_creature)
	{
		printf("game.c: Camera exception: Seems like player was killed.\n");
		return;
	}
	Transform *player_transform = (Transform *)player_creature;

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
	if(!creatureGetPlayer())
	{
		*quit = 1;
	}
}

void gameProcessFrame(int *quit)
{
	creatureProcessList();
	gameCheckDeath(quit);
	uiProcessInventory();

	gameProcessCamera();
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
	int quit = 0;
	double target_frame_time = 1000/60.0;

	#ifdef TEST_BATCH_1
	testBatch1();
	#endif

	while(!quit)
	{
		// Start frame timer
		int start_time = SDL_GetTicks();
		
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
		SDL_Delay(10);
		
		#ifndef TEST_BATCH_1
		double current_time = SDL_GetTicks();
		double elapsed_time = (current_time - start_time) / 1000.0;

		state->true_time += elapsed_time;
		state->true_delta_time = elapsed_time;

		state->player_action = 1;	
		if(state->player_action)
		{	
			state->game_delta_time = state->true_delta_time;
			state->game_time += state->game_delta_time;
		}
		else
		{
			state->game_delta_time = 0;
		}
		#endif
	}

    // Free resources and close SDL
	free(global_memory);	
    graphicsClose(sdl_state);

	return 0;
}
