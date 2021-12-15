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

int activeCreate()
{
	return transformCreate(OBJECT_TYPE_ACTIVE);
}

void activeDelete(int id)
{
	transformDelete(id, OBJECT_TYPE_ACTIVE);
}

Active* activeGet(int id)
{
	return (Active *)transformGet(id, OBJECT_TYPE_ACTIVE);
}

void activeStart(int id)
{
	Active *active_ptr = activeGet(id);
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
				creatureGetPlayer()->level++;

				Map *maps = memoryGetMaps();
				if(!maps[state->current_level].created)
				{
					gameLoadNextLevel();	
				}

				break;

			case ACTIVE_STAIRS_UP:
				state->current_level--;
				creatureGetPlayer()->level--;

				break;

			default:
				printf("active.c: Tried bad Active!\n");
				break;
		};
	}
	input->use.key_press = 0;
}

void activeCreateRandomize(Vector2f position)
{
	int index = transformCreate(OBJECT_TYPE_ACTIVE);

	Active *active_ptr = activeGet(index);	
	active_ptr->active_action = ACTIVE_RANDOMIZE_MAP;
	Map *map_ptr = mapGetCurrent();


	active_ptr->position = position; 

	active_ptr->collider.w = 64;
	active_ptr->collider.h = 64;

	active_ptr->render.w = 64;
	active_ptr->render.h = 64;
}

void activeCreateStairsUp(Vector2f position)
{
	PersistentGameState *state = memoryGetPersistentGameState();
	int index = activeCreate();
	Active *active_ptr = activeGet(index);	
	active_ptr->active_action = ACTIVE_STAIRS_UP;
	active_ptr->level = state->current_level;

	Map *map_ptr = mapGetCurrent();

	active_ptr->position = position; 

	active_ptr->collider.w = 64;
	active_ptr->collider.h = 64;

	active_ptr->render.w = 64;
	active_ptr->render.h = 64;
}

void activeCreateStairsDown(Vector2f position)
{
	PersistentGameState *state = memoryGetPersistentGameState();
	int index = activeCreate();
	Active *active_ptr = activeGet(index);	
	active_ptr->active_action = ACTIVE_STAIRS_DOWN;
	active_ptr->level = state->current_level;

	Map *map_ptr = mapGetCurrent();

	active_ptr->position = position; 

	active_ptr->collider.w = 64;
	active_ptr->collider.h = 64;

	active_ptr->render.w = 64;
	active_ptr->render.h = 64;
}

void activeDrawList()
{
	PersistentGameState *state = memoryGetPersistentGameState();
	TransientGameState *ui_state = memoryGetTransientGameState();
	Active *active_ptr;
	int active_count = 0, active_id = 0;

	int last_active = state->active_count;
	for(int i = 0; i < last_active; i++)
	{

		active_ptr = activeGet(i);
		if(active_ptr)
		{
			if(active_ptr->level == state->current_level)
			{
				if(ui_state->highlight_type != OBJECT_TYPE_ACTIVE ||
				   ui_state->highlight_id != active_ptr->id)
				graphicsDrawTransform((Transform *)active_ptr);
			}
		}
		else
		{
			last_active++;
		}
	}
}

