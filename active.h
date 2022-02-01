/*******************************************************************************
* 
* FILENAME : active.h
*
* DESCRIPTION : Header file containing active function headers and structs
*
* AUTHOR : filipang           
* 
* START DATE :    12/11/2021
*
*******************************************************************************/

#ifndef ACTIVE_H
#define ACTIVE_H

#define ACTIVE_RANDOMIZE_MAP 0
#define ACTIVE_STAIRS_DOWN	 1
#define ACTIVE_STAIRS_UP	 2

typedef struct Active
{
	int active_action;
} Active;


struct Entity *activeGetEntity(Active *active);
void activeStart(int id);
void activeCreateRandomize(Vector2f position, int level);
void activeCreateStairsUp(Vector2f position, int level);
void activeCreateStairsDown(Vector2f position, int level);

#endif 
