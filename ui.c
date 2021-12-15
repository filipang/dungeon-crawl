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
			item_ptr = itemGet(state->player.inventory[i][j]);
			if(item_ptr)
			{
				if(item_ptr->state == ITEM_STATE_INVENTORY)
				{
					if(ui_state->highlight_type != OBJECT_TYPE_ITEM ||
					   ui_state->highlight_id != item_ptr->id)
					{
						Vector2f s_position = 
							itemGetScreenPositionInventory(vector2i(j, i));

						graphicsScreenDrawTransform((Transform *)item_ptr, 
													s_position);
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

void uiProcessInventory()
{
	TransientGameState *ui_state = memoryGetTransientGameState();
	InputState *input = memoryGetInputState();
	ui_state->open_inventory = (ui_state->open_inventory + 
						        input->inventory.key_press) % 2;
}

void uiDrawItemInfoBox()
{
	PersistentGameState *state = memoryGetPersistentGameState();
	TransientGameState *ui_state = memoryGetTransientGameState();
	GraphicsState *sdl_state = memoryGetGraphicsState();

	Item *item_ptr;
	if(ui_state->highlight_type != OBJECT_TYPE_ITEM)
	{
		sdl_state->item_box.visible = 0;
		return;
	}
	item_ptr = itemGet(ui_state->highlight_id);

	sdl_state->item_box.visible = 1;

	if(item_ptr->state == ITEM_STATE_INVENTORY)
	{	
		Vector2f vec = itemGetScreenPositionInventory(vector2i(0,0));
		sdl_state->item_box.rect.x = vec.x;
		sdl_state->item_box.rect.y = vec.y;
		sdl_state->item_description.rect.x = vec.x;
		sdl_state->item_description.rect.y = vec.y;
	}
	
	if(item_ptr->state == ITEM_STATE_GROUND)
	{
		
		Vector2f vec = transformGetScreenRenderCenter((Transform *)item_ptr);
		sdl_state->item_box.rect.x = vec.x;
		sdl_state->item_box.rect.y = vec.y;
		sdl_state->item_description.rect.x = vec.x;
		sdl_state->item_description.rect.y = vec.y;
	}
	
	strcpy(sdl_state->item_description.text, item_ptr->description);
	kiss_window_draw(&sdl_state->item_box, sdl_state->renderer);
	kiss_label_draw(&sdl_state->item_description, sdl_state->renderer);
}
