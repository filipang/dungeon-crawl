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

	int active_action;
} Active;

int 	activeCreate();
void 	activeDelete(int id);
Active* activeGet(int id);

void activeStart(int id);

void activeCreateRandomize(Vector2f position);
void activeCreateStairsUp(Vector2f position);
void activeCreateStairsDown(Vector2f position);

void activeDrawList();

#endif 
