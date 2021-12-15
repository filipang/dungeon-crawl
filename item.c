/*******************************************************************************
* 
* FILENAME : item.c
*
* DESCRIPTION : Source file containing item functions
*
* AUTHOR : filipang           
* 
* START DATE :    11/11/2021
*
*******************************************************************************/

int itemCreate()
{
	return transformCreate(OBJECT_TYPE_ITEM);
}

void itemDelete(int id)
{
	transformDelete(id, OBJECT_TYPE_ITEM);
}

Item* itemGet(int id)
{
	return (Item *)transformGet(id, OBJECT_TYPE_ITEM);
}

void itemCreateTest(Vector2f position)
{
	PersistentGameState *state = memoryGetPersistentGameState();
	int index = itemCreate();

	Item *item_ptr = itemGet(index);	

	strcpy(item_ptr->description, 
		   "This is a \ngeneric item. \nIt doesn't do \nanything.");

	item_ptr->level = state->current_level;

	Map *map_ptr = mapGetCurrent();

	item_ptr->position = position; 

	item_ptr->render = vector2f(25, 25);
}

void itemDrawList()
{
	PersistentGameState *state = memoryGetPersistentGameState();
	TransientGameState *ui_state = memoryGetTransientGameState();
	Item *item_ptr;

	int skipped_items = 0;
	for(int i = 0; i < state->item_count + skipped_items; i++)
	{

		item_ptr = itemGet(i);
		if(item_ptr)
		{
			if(item_ptr->level == state->current_level && 
			   item_ptr->state == ITEM_STATE_GROUND)
			{
				if(ui_state->highlight_type != OBJECT_TYPE_ITEM ||
				   ui_state->highlight_id != item_ptr->id)
					graphicsDrawTransform((Transform *)item_ptr);
			}
		}
		else
		{
			skipped_items++;
		}
	}
}

int itemPickUp(int id)
{
	PersistentGameState *state = memoryGetPersistentGameState();
	TransientGameState *ui_state = memoryGetTransientGameState();
	Item *item_ptr = itemGet(id);
	for(int i = 0; i < ITEM_INVENTORY_MAX_Y; i ++)
	{
		for(int j = 0; j < ITEM_INVENTORY_MAX_X; j ++)
		{
			if(state->player.inventory[i][j] == -1)
			{
				state->player.inventory[i][j] = ui_state->highlight_id;
				item_ptr->state = ITEM_STATE_INVENTORY;
				return 0;
			}
		}
	}
	return -1;
}

Vector2f itemGetInventoryContainerScreenCorner()
{
	return vector2f(600, 300);
}

Vector2f itemGetScreenPositionInventory(Vector2i inv_coords)
{
	Vector2f inv_coords_f = vector2iRoundTo2f(inv_coords);
	Vector2f position = vector2fMultiply(inv_coords_f, 30);
	position = vector2fPlus(position, 
			   				itemGetInventoryContainerScreenCorner());
}

