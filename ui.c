/*******************************************************************************
* 
* FILENAME : graphics.c
*
* DESCRIPTION : Source file containing graphics functions
*
* AUTHOR : filipang           
* 
* START DATE :    5/11/2021
*
*******************************************************************************/

void uiButtonEvent(kiss_button *button, SDL_Event *e, 
				  int *draw, int *quit)
{
	GraphicsState *sdl_state = memoryGetGraphicsState();
	if (kiss_button_event(button, e, draw))
	{ 
		if(button == &sdl_state->button_save)
			memorySavePersistent();
		else if (button == &sdl_state->button_load)
			memoryLoadPersistent();
	}
}

void uiProcessEvent()
{
	
	GraphicsState *sdl_state = memoryGetGraphicsState();
	PersistentGameState *state = memoryGetPersistentGameState();

	snprintf(sdl_state->label.text, 
			 KISS_MAX_LABEL, 
			 "%.0f FPS", 
			 1/state->true_delta_time);

	int draw, quit;
	kiss_window_event(&sdl_state->window, &sdl_state->event, &draw);
	uiButtonEvent(&sdl_state->button_save, &sdl_state->event, &draw, &quit);
	uiButtonEvent(&sdl_state->button_load, &sdl_state->event, &draw, &quit);
	
}

void uiDrawFPS()
{
	TransientGameState *ui_state = memoryGetTransientGameState();
	GraphicsState *sdl_state = memoryGetGraphicsState();

	kiss_label_draw(&sdl_state->label, sdl_state->renderer);
}

void uiDrawKillCount()
{
	TransientGameState *ui_state = memoryGetTransientGameState();
	PersistentGameState *state = memoryGetPersistentGameState();
	GraphicsState *sdl_state = memoryGetGraphicsState();
	snprintf(sdl_state->kill_count_label.text, 99, "Kill count: %d", state->kill_count);
	kiss_label_draw(&sdl_state->kill_count_label, sdl_state->renderer);
}

void uiDrawLoadSave()
{
	TransientGameState *ui_state = memoryGetTransientGameState();
	GraphicsState *sdl_state = memoryGetGraphicsState();

	kiss_button_draw(&sdl_state->button_save, sdl_state->renderer);
	kiss_button_draw(&sdl_state->button_load, sdl_state->renderer);
}

void uiDraw()
{
	uiDrawFPS();
	uiDrawKillCount();
	uiDrawLoadSave();
}

void uiDrawInventory()
{

	PersistentGameState *state = memoryGetPersistentGameState();
	TransientGameState *ui_state = memoryGetTransientGameState();
	GraphicsState *sdl_state = memoryGetGraphicsState();

	if(ui_state->open_inventory == 0)
		return;

	Item *item_ptr;

    SDL_SetRenderDrawColor(sdl_state->renderer, 125, 150, 125, 255);		
	Vector2f s_position = 
		itemGetScreenPositionInventory(vector2i(0, 0));
	SDL_Rect inv_bg;
	inv_bg.x = s_position.x;
	inv_bg.y = s_position.y;
	inv_bg.w = ITEM_INVENTORY_MAX_X * 30;
	inv_bg.h = ITEM_INVENTORY_MAX_Y * 30;
	SDL_RenderFillRect(sdl_state->renderer, &inv_bg);
	int skipped_items = 0;
	for(int i = 0; i < ITEM_INVENTORY_MAX_Y; i++)
	{
		for(int j = 0; j < ITEM_INVENTORY_MAX_X; j++)
		{
			int item_id = state->player.inventory[i][j];
			Entity *entity_item = entityGet(item_id);
			item_ptr = &(entity_item->item);
			if(entity_item)
			{
				if(item_ptr->state == ITEM_STATE_INVENTORY)
				{
					if(ui_state->highlight_id != item_id)
					{
						Vector2f s_position = 
							itemGetScreenPositionInventory(vector2i(j, i));

						graphicsScreenDrawEntity(entity_item, s_position);
					}
				}
			}
			else
			{
				skipped_items++;
			}
		}
	}
}

int uiCheckFPointOnRectCollision(Vector2f point, SDL_FRect rect)
{
	if(point.x > rect.x && 
	   point.x < rect.x + rect.w && 
	   point.y > rect.y &&
	   point.y < rect.y + rect.y)
	{
		return 1;
	}
	return 0;
}

int uiCheckPointOnRectCollision(Vector2i point, SDL_FRect rect)
{
	if(point.x > rect.x && 
	   point.x < rect.x + rect.w && 
	   point.y > rect.y &&
	   point.y < rect.y + rect.y)
	{
		return 1;
	}
	return 0;
}

SDL_FRect uiGetInventoryContainerScreenCorner()
{
	SDL_FRect rect;
	rect.x = 600;
	rect.y = 300;
	rect.w = ITEM_INVENTORY_MAX_X * 30;
	rect.h = ITEM_INVENTORY_MAX_Y * 30;
	return rect;
}

SDL_FRect uiGetInventoryContainerScreenCenter()
{
	SDL_FRect rect;
	rect.w = ITEM_INVENTORY_MAX_X * 30;
	rect.h = ITEM_INVENTORY_MAX_Y * 30;
	rect.x = 600 + rect.w / 2;
	rect.y = 300 + rect.h / 2;
	return rect;
}

Entity* uiGetHoveredInventoryItem()
{
	TransientGameState *ui_state = memoryGetTransientGameState();
	PersistentGameState *state = memoryGetPersistentGameState();
	InputState *input = memoryGetInputState();
	SDL_FRect inventory_rect = uiGetInventoryContainerScreenCorner();
	Vector2i inventory_corner = vector2i(inventory_rect.x, inventory_rect.y);
	int col = 
		uiCheckPointOnRectCollision(input->mouse_position, inventory_rect);	

	if(col)
	{
		Vector2i local_inventory_position = 
			vector2iMinus(input->mouse_position, inventory_corner);

		Vector2i inventory_coords = 
			vector2iDivide(local_inventory_position, 30);

		Entity* item_entity = entityGet(state->player.inventory[inventory_coords.y]
										   				   	   [inventory_coords.x]);

		return item_entity;
	}
	return NULL;
}

Vector2f uiGetHoveredItemScreenPosition()
{
	TransientGameState *ui_state = memoryGetTransientGameState();
	PersistentGameState *state = memoryGetPersistentGameState();
	InputState *input = memoryGetInputState();
	SDL_FRect inventory_rect = uiGetInventoryContainerScreenCorner();
	Vector2i inventory_corner = vector2i(inventory_rect.x, inventory_rect.y);
	int col = 
		uiCheckPointOnRectCollision(input->mouse_position, inventory_rect);	

	if(col)
	{
		Vector2i local_inventory_position = 
			vector2iMinus(input->mouse_position, inventory_corner);

		Vector2i inventory_coords = 
			vector2iDivide(local_inventory_position, 30);

		Vector2f inventory_position = 
			vector2fMultiply(vector2iRoundTo2f(inventory_coords), 30);
		
		Vector2f screen_position = 
			vector2fPlus(inventory_position, 
						 vector2iRoundTo2f(inventory_corner));

		return screen_position;                        
	}
	return vector2fZero();
}

void uiProcessInventory()
{
	TransientGameState *ui_state = memoryGetTransientGameState();
	PersistentGameState *state = memoryGetPersistentGameState();
	InputState *input = memoryGetInputState();
	ui_state->open_inventory = (ui_state->open_inventory + 
						        input->inventory.key_press) % 2;
	SDL_FRect inventory_rect = uiGetInventoryContainerScreenCenter();

	if(ui_state->open_inventory)
	{
		Entity *item_entity = uiGetHoveredInventoryItem();
		if(item_entity)
		{
			if(input->left_click.key_press)
			{
				itemUse(item_entity->id);
			}
			ui_state->highlight_id = item_entity->id;
		}
	}
}

void uiDrawItemInfoBox()
{
	PersistentGameState *state = memoryGetPersistentGameState();
	TransientGameState *ui_state = memoryGetTransientGameState();
	GraphicsState *sdl_state = memoryGetGraphicsState();
	InputState *input = memoryGetInputState();

	Entity *entity_ptr = entityGet(ui_state->highlight_id);
    if(!entity_ptr)
	{
		sdl_state->item_box.visible = 0;
		return;	
	}
	Item *item_ptr = &entity_ptr->item;
	if(!entity_ptr->has_item)
	{
		sdl_state->item_box.visible = 0;
		return;
	}
	sdl_state->item_box.visible = 1;

	if(item_ptr->state == ITEM_STATE_INVENTORY)
	{	
		//Vector2f vec = uiGetHoveredItemScreenPosition();
		Vector2f vec = vector2iRoundTo2f(input->mouse_position);
		sdl_state->item_box.rect.x = vec.x;
		sdl_state->item_box.rect.y = vec.y;
		sdl_state->item_description.rect.x = vec.x;
		sdl_state->item_description.rect.y = vec.y;
	}
	
	if(item_ptr->state == ITEM_STATE_GROUND)
	{
		Vector2f vec = transformGetScreenRenderCenter(&entity_ptr->transform);
		sdl_state->item_box.rect.x = vec.x;
		sdl_state->item_box.rect.y = vec.y;
		sdl_state->item_description.rect.x = vec.x;
		sdl_state->item_description.rect.y = vec.y;
	}
	
	strcpy(sdl_state->item_description.text, item_ptr->description);
	kiss_window_draw(&sdl_state->item_box, sdl_state->renderer);
	kiss_label_draw(&sdl_state->item_description, sdl_state->renderer);
}

// NOTE(filip): There can be a fixed amount of fading texts on the screen at 
// 				any point.
void uiCreateFadingText()
{

}
