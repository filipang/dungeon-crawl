/*******************************************************************************
* 
* FILENAME : input.h
*
* DESCRIPTION : Header file containing input structs and function headers
*
* AUTHOR : filipang           
* 
* START DATE :    5/11/2021
*
*******************************************************************************/

#ifndef INPUT_H
#define INPUT_H

typedef struct ButtonState
{
	int key_press;
	int key_release;
	int key_hold;
	int key_should_hold;
} ButtonState;

#define BUTTON_COUNT 13 
typedef struct InputState 
{
    union
    {
		// NOTE(filip): MAKE SURE TO UPDATE BUTTON_COUNT WHEN ADDING OR
		// 				REMOVING BUTTONS
        ButtonState buttons[BUTTON_COUNT];
        struct
		{
            ButtonState move_up;
            ButtonState move_down;
            ButtonState move_left;
			ButtonState move_right;
			ButtonState use;
			ButtonState attack_up;
			ButtonState attack_down;
			ButtonState attack_left;
			ButtonState attack_right;
			ButtonState inventory;
			ButtonState left_click;
			ButtonState right_click;
			ButtonState debug;
        };
    };
	Vector2i mouse_position;
} InputState; 

void inputProcessState();
void inputProcessEvent();

#endif
