/*******************************************************************************
* 
* FILENAME : input.c
*
* DESCRIPTION : Source file containing input functions
*
* AUTHOR : filipang           
* 
* START DATE :    5/11/2021
*
*******************************************************************************/

void inputProcessState()
{
	InputState *input = memoryGetInputState();

	for(int i = 0; i < BUTTON_COUNT; i++)
	{
		ButtonState *button = &input->buttons[i];

		int was_held = button->key_hold;

		button->key_hold = button->key_should_hold;
		if(button->key_hold && !was_held)
		{
			button->key_press = 1;
		}
		else
		{
			button->key_press = 0;	
		}

		if(!button->key_hold && was_held)
		{
			button->key_release = 1;
		}
		else
		{	
			button->key_release = 0;
		}
	}
	SDL_GetMouseState(&input->mouse_position.x, &input->mouse_position.y);
}

void inputProcessEvent()
{
	InputState *input = memoryGetInputState();
	GraphicsState *sdl_state = memoryGetGraphicsState();
	int type = sdl_state->event.type;
	ButtonState *button = NULL;
	
	if(sdl_state->event.type == SDL_MOUSEBUTTONDOWN ||
	   sdl_state->event.type == SDL_MOUSEBUTTONUP)
	{
		switch( sdl_state->event.button.button )
		{
			case SDL_BUTTON_LEFT:
				button = &input->left_click;
				break;

			case SDL_BUTTON_RIGHT:
				button = &input->right_click;
				break;
		}
	}
	else if(sdl_state->event.type == SDL_KEYDOWN ||
			sdl_state->event.type == SDL_KEYUP)
	{
		switch( sdl_state->event.key.keysym.sym )
		{
			// NOTE(filip): MAKE SURE TO UPDATE BUTTON_COUNT WHEN ADDING OR
			// 				REMOVING BUTTONS
			case SDLK_UP:
			button = &input->attack_up;
			break;

			case SDLK_DOWN:
			button = &input->attack_down;
			break;

			case SDLK_LEFT:
			button = &input->attack_left;
			break;

			case SDLK_RIGHT:
			button = &input->attack_right;
			break;

			case SDLK_w:
			button = &input->move_up;
			break;

			case SDLK_s:
			button = &input->move_down;
			break;

			case SDLK_a:
			button = &input->move_left;
			break;

			case SDLK_d:
			button = &input->move_right;
			break;

			case SDLK_e:
			button = &input->use;
			break;

			case SDLK_i:
			button = &input->inventory;
			break;

			case SDLK_x:
			button = &input->debug;
			break;

			default:
			return;
		}
	}

	if(type == SDL_MOUSEBUTTONDOWN)
	{
		button->key_should_hold = 1;
	}
	if(type == SDL_MOUSEBUTTONUP)
	{
		button->key_should_hold = 0;
	}
	if(type == SDL_KEYDOWN)
	{
		button->key_should_hold = 1;
	}
	if(type == SDL_KEYUP)
	{
		button->key_should_hold = 0;
	}

}

