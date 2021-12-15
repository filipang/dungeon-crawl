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

#define BUTTON_COUNT 8
typedef struct InputState 
{
    union
    {
        ButtonState buttons[BUTTON_COUNT];
        struct
		{
            ButtonState move_up;
            ButtonState move_down;
            ButtonState move_left;
			ButtonState move_right;
			ButtonState use;
			ButtonState attack;
			ButtonState inventory;
			ButtonState click;
        };
    };
	Vector2i mouse_position;
} InputState; 

void inputProcessState();
void inputProcessEvent();

#endif
