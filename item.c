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

struct Entity *itemGetEntity(Item *item)
{
	return (Entity *)((void *)item - struct_offset(Entity, item));	
}

void itemCreateTest(Vector2f position, int level)
{
	PersistentGameState *state = memoryGetPersistentGameState();
	int index = entityMarkCreate();

	Entity *entity_ptr = entityGet(index);	
	entity_ptr->has_transform = 1;
	entity_ptr->has_item = 1;
	entity_ptr->has_animation = 1;
	entity_ptr->animation.clip_col = 4;
	entity_ptr->animation.clip_row = 4;
	entity_ptr->animation.texture_id = 4;
	Item *item_ptr = &entity_ptr->item;
	Transform *transform_ptr = &entity_ptr->transform;
	
	strcpy(item_ptr->description, 
		   "This is a \ngeneric item. \nIt doesn't do \nanything.");

	transform_ptr->level = level;

	Map *map_ptr = mapGetCurrent();

	transform_ptr->position = position; 

	transform_ptr->render = vector2f(32, 32);
}

void itemCreateHealthPotion(Vector2f position, int level)
{
	PersistentGameState *state = memoryGetPersistentGameState();
	int index = entityMarkCreate();

	Entity *entity_ptr = entityGet(index);	
	entity_ptr->has_transform = 1;
	entity_ptr->has_item = 1;
	entity_ptr->has_animation = 1;
	entity_ptr->animation.clip_col = 0;
	entity_ptr->animation.clip_row = 11;
	entity_ptr->animation.texture_id = 4;
	Item *item_ptr = &entity_ptr->item;
	item_ptr->item_type = ITEM_TYPE_POTION;
	item_ptr->effect = ITEM_EFFECT_POTION_HEAL;
	Transform *transform_ptr = &entity_ptr->transform;
	
	strcpy(item_ptr->description, 
		   "This is a \nhealth potion. \nIt will heal \n20% max hp.");

	transform_ptr->level = level;

	Map *map_ptr = mapGetCurrent();

	transform_ptr->position = position; 

	transform_ptr->render = vector2f(32, 32);
}

void itemCreateDamageScroll(Vector2f position, int level)
{
	PersistentGameState *state = memoryGetPersistentGameState();
	int index = entityMarkCreate();

	Entity *entity_ptr = entityGet(index);	
	entity_ptr->has_transform = 1;
	entity_ptr->has_item = 1;
	entity_ptr->has_animation = 1;
	entity_ptr->animation.clip_col = 1;
	entity_ptr->animation.clip_row = 12;
	entity_ptr->animation.texture_id = 4;
	Item *item_ptr = &entity_ptr->item;
	item_ptr->item_type = ITEM_TYPE_SCROLL;
	item_ptr->effect = ITEM_EFFECT_SCROLL_DAMAGE;
	Transform *transform_ptr = &entity_ptr->transform;
	
	strcpy(item_ptr->description, 
		   "This is a \ndamage scroll. \nIt will grant \n+1 damage.");

	transform_ptr->level = level;

	Map *map_ptr = mapGetCurrent();

	transform_ptr->position = position; 

	transform_ptr->render = vector2f(32, 32);
}

int itemPickUp(int id)
{
	PersistentGameState *state = memoryGetPersistentGameState();
	TransientGameState *ui_state = memoryGetTransientGameState();
	Entity *item_entity = entityGet(id);
	Item *item_ptr = &item_entity->item;

	for(int i = 0; i < ITEM_INVENTORY_MAX_Y; i ++)
	{
		for(int j = 0; j < ITEM_INVENTORY_MAX_X; j ++)
		{
			if(state->player.inventory[i][j] == -1)
			{
				state->player.inventory[i][j] = ui_state->highlight_id;
				item_ptr->state = ITEM_STATE_INVENTORY;
				item_entity->has_transform = 0;
				return 0;
			}
		}
	}
	return -1;
}

void itemEffect(void *creature_v, int effect)
{
	Creature *creature = (Creature *) creature_v;
	switch(effect)
	{
		case ITEM_EFFECT_POTION_HEAL:
			creature->health = 
				(creature->health + creature->max_health * 0.2);
			if(creature->health > creature->max_health)
				creature->health = creature->max_health;
			break;
		case ITEM_EFFECT_SCROLL_DAMAGE:
			creature->damage += 1; 
			if(creature->health > creature->max_health)
				creature->health = creature->max_health;
			break;
	}
}

void itemUse(int id)
{
	PersistentGameState *state = memoryGetPersistentGameState();
	TransientGameState *ui_state = memoryGetTransientGameState();
	Entity *item_entity = entityGet(id);
	Item *item_ptr = &item_entity->item;

	switch(item_ptr->item_type)
	{
		case ITEM_TYPE_ARMOR:
			state->player.equipped_armor = item_entity->id;
			gameUpdatePlayerStats();
			break;
		case ITEM_TYPE_WEAPON:
		case ITEM_TYPE_RING:
		case ITEM_TYPE_AMULET:
		case ITEM_TYPE_BOOTS:
		case ITEM_TYPE_HELMET:
			break;
		case ITEM_TYPE_POTION:
		case ITEM_TYPE_SCROLL:
			itemEffect(&(entityGetPlayer()->creature), item_ptr->effect);
			entityMarkDelete(item_entity->id);
			for(int i = 0; i < ITEM_INVENTORY_MAX_Y; i++)
			{
				for(int j = 0; j < ITEM_INVENTORY_MAX_X; j++)
				{
					if(state->player.inventory[i][j]==item_entity->id)
					{
						state->player.inventory[i][j] = -1;
						break;
					}
				}
			}
			break;
	}
}

Vector2f itemGetScreenPositionInventory(Vector2i inv_coords)
{
	Vector2f inv_coords_f = vector2iRoundTo2f(inv_coords);
	Vector2f position = vector2fMultiply(inv_coords_f, 30);
	SDL_FRect rect = uiGetInventoryContainerScreenCorner();
	Vector2f inventory_position = vector2f(rect.x, rect.y);
	position = vector2fPlus(position, inventory_position);
}

