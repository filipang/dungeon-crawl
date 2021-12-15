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
	printf("input.c: %d %d\n", input->mouse_position.x, input->mouse_position.y);
}

void inputProcessEvent()
{
	InputState *input = memoryGetInputState();
	GraphicsState *sdl_state = memoryGetGraphicsState();
	int type = sdl_state->event.type;
	ButtonState *button = NULL;
	
	//Select surfaces based on key press
	switch( sdl_state->event.key.keysym.sym )
	{
		// NOTE(filip): key frame counters can overflow, maybe add a for loop 
		// 				that caps key frame counters
		case SDLK_UP:
		button = &input->move_up;
		break;

		case SDLK_DOWN:
		button = &input->move_down;
		break;

		case SDLK_LEFT:
		button = &input->move_left;
		break;

		case SDLK_RIGHT:
		button = &input->move_right;
		break;

		case SDLK_e:
		button = &input->use;
		break;

		case SDLK_SPACE:
		button = &input->attack;
		break;

		case SDLK_i:
		button = &input->inventory;
		break;

		default:
		return;
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

