/*******************************************************************************
* 
* FILENAME : Active.c
*
* DESCRIPTION : Source file containing Active functions
*
* AUTHOR : filipang           
* 
* START DATE :    12/11/2021
*
*******************************************************************************/

struct Entity *activeGetEntity(Active *active)
{
	return (Entity *)((void *)active - struct_offset(Entity, active));	
}

void activeStart(int id)
{
	Entity *entity_active = entityGet(id);
	Active *active_ptr = &entity_active->active;
	InputState *input = memoryGetInputState();
	PersistentGameState *state = memoryGetPersistentGameState();
	if(input->use.key_press)
	{
		switch(active_ptr->active_action)
		{
			case ACTIVE_RANDOMIZE_MAP:
				mapRandomize();
				mapGetCurrent()->map_changed = 1;	
				break;

			case ACTIVE_STAIRS_DOWN:
				state->current_level++;
				entityGetPlayer()->transform.level++;

				Map *maps = memoryGetMaps();
				if(!maps[state->current_level].created)
				{
					gameLoadNextLevel();	
				}

				break;

			case ACTIVE_STAIRS_UP:
				state->current_level--;
				entityGetPlayer()->transform.level--;

				break;

			default:
				printf("active.c: Tried bad Active!\n");
				break;
		};
	}
	input->use.key_press = 0;
}

void activeCreateRandomize(Vector2f position, int level)
{
	int index = entityMarkCreate();
	Entity *entity_active = entityGet(index);
	entity_active->has_active = 1;
	entity_active->has_transform = 1;
	entity_active->has_animation = 1;
	entity_active->animation.texture_id = 1;
	Active *active_ptr = &entity_active->active;	
	Transform *transform_ptr = &entity_active->transform;
	active_ptr->active_action = ACTIVE_RANDOMIZE_MAP;
	Map *map_ptr = mapGetCurrent();

	transform_ptr->position = position; 
	transform_ptr->level = level;

	transform_ptr->collider.w = 64;
	transform_ptr->collider.h = 64;

	transform_ptr->render.w = 64;
	transform_ptr->render.h = 64;
}

void activeCreateStairsUp(Vector2f position, int level)
{
	int index = entityMarkCreate();
	Entity *entity_active = entityGet(index);
	entity_active->has_active = 1;
	entity_active->has_transform = 1;
	entity_active->has_animation = 1;
	entity_active->animation.texture_id = 4;
	entity_active->animation.clip_col = 2;
	entity_active->animation.clip_row = 15;
	Active *active_ptr = &entity_active->active;	
	Transform *transform_ptr = &entity_active->transform;
	active_ptr->active_action = ACTIVE_STAIRS_UP;
	Map *map_ptr = mapGetCurrent();

	transform_ptr->position = position; 
	transform_ptr->level = level;

	transform_ptr->collider.w = 64;
	transform_ptr->collider.h = 64;

	transform_ptr->render.w = 64;
	transform_ptr->render.h = 64;
}

void activeCreateStairsDown(Vector2f position, int level)
{
	int index = entityMarkCreate();
	Entity *entity_active = entityGet(index);
	entity_active->has_active = 1;
	entity_active->has_transform = 1;
	entity_active->has_animation = 1;
	entity_active->animation.texture_id = 4;
	entity_active->animation.clip_col = 5;
	entity_active->animation.clip_row = 15;
	Active *active_ptr = &entity_active->active;	
	Transform *transform_ptr = &entity_active->transform;
	active_ptr->active_action = ACTIVE_STAIRS_DOWN;
	Map *map_ptr = mapGetCurrent();

	transform_ptr->position = position; 
	transform_ptr->level = level;

	transform_ptr->collider.w = 64;
	transform_ptr->collider.h = 64;

	transform_ptr->render.w = 64;
	transform_ptr->render.h = 64;
}

