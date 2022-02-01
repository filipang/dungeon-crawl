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

typedef struct Transform
{
	int level;			
	Vector2f position;	
	Vector2f render;	  
	Vector2f collider;	
	Vector2f trigger;		 
	float angle;
} Transform;

struct  Entity* transformGetEntity(Transform *transform);
int		transformCheckCollision(Transform *t1, Transform *t2);
int 	transformCheckRectCollision(Vector2f position, Vector2f size, int level, Transform *t2);
int		transformCheckCollisions(Transform *transform);
int 	transformCheckRectCollisions(Vector2f position, Vector2f size, int level);
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
