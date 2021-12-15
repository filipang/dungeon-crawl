/*******************************************************************************
* 
* FILENAME : item.h
*
* DESCRIPTION : Header file containing item functions and structs
*
* AUTHOR : filipang           
* 
* START DATE :    11/11/2021
*
*******************************************************************************/

#ifndef ITEM_H
#define ITEM_H

#define ITEM_STATE_GROUND    0
#define ITEM_STATE_INVENTORY 1
#define ITEM_STATE_CHEST     2

#define ITEM_INVENTORY_MAX_X 5
#define ITEM_INVENTORY_MAX_Y 5

typedef struct Item
{
	union
	{
		Transform transform;
		struct
		{
			int created;
			int id;
			int object_type;
			int level;
			int frame_count;
			int clip_row;
			int clip_col;
			
			Vector2f position;
			Vector2f render;
			Vector2f collider;
			Vector2f trigger;
		};
	};

	char description[200];
	int  state;
	int  chest_id;
} Item;

int		itemCreate();
void	itemDelete(int id);
Item*	itemGet(int id);

void	itemDrawList();
int     itemPickUp(int id);

Vector2f itemGetInventoryContainerScreenCorner();
Vector2f itemGetScreenPositionInventory(Vector2i inv_coords);

#endif
