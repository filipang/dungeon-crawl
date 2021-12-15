/*******************************************************************************
* 
* FILENAME : transform.h
*
* DESCRIPTION : Header file containing transform function headers and structs
*
* AUTHOR : filipang           
* 
* START DATE :    12/11/2021
*
*******************************************************************************/

#ifndef TRANSFORM_H
#define TRANSFORM_H

#define OBJECT_TYPE_ITEM 	 1
#define OBJECT_TYPE_CREATURE 2
#define OBJECT_TYPE_ACTIVE	 3

typedef struct Transform
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
} Transform;

void*	transformGetList(int object_type);
int*	transformGetListSize(int object_type);
int		transformGetListMaxMemory(int object_type);
int 	transformGetTransformSize(int object_type);

int 	transformCreate(int object_type);
void 	transformDelete(int id, int object_type);
Transform* transformGet(int id, int object_type);

int		transformCheckCollision(Transform *t1, Transform *t2);
void	transformMove(Transform *transform, Vector2f delta);
void	transformTryMove(Transform *transform, Vector2f delta);

Vector2f transformGetRenderCenter(Transform *transform);
Vector2f transformGetRenderCorner(Transform *transform);

Vector2f transformGetColliderCenter(Transform *transform);
Vector2f transformGetColliderCorner(Transform *transform);

Vector2f transformGetTriggerCenter(Transform *transform);
Vector2f transformGetTriggerCorner(Transform *transform);

Vector2f transformGetScreenRenderCorner(Transform *transform);
Vector2f transformGetScreenRenderCenter(Transform *transform); 

Vector2f transformGetScreenColliderCorner(Transform *transform);
Vector2f transformGetScreenColliderCenter(Transform *transform); 

Vector2f transformGetScreenTriggerCorner(Transform *transform);
Vector2f transformGetScreenTriggerCenter(Transform *transform); 

#endif
