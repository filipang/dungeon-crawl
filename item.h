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

#define ITEM_TYPE_ARMOR      0 
#define ITEM_TYPE_WEAPON     1
#define ITEM_TYPE_RING       2
#define ITEM_TYPE_AMULET     3
#define ITEM_TYPE_BOOTS      4
#define ITEM_TYPE_HELMET     5
#define ITEM_TYPE_POTION	 6
#define ITEM_TYPE_SCROLL	 7

#define ITEM_EFFECT_POTION_HEAL 0
#define ITEM_EFFECT_SCROLL_DAMAGE 1

typedef struct Item
{
	char name[30];
	char description[200];
	int  state;
	int  chest_id;
	int  effect;
	int  item_type;
} Item;

struct Entity *itemGetEntity(Item *item);
void itemCreateTest(Vector2f position, int level);
void  itemDrawList();
int   itemPickUp(int id);
void itemUse(int id);
void itemEffect(void *creature_v, int effect);
Vector2f itemGetScreenPositionInventory(Vector2i inv_coords);

#endif
