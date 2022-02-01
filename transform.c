/*******************************************************************************
* 
* FILENAME : transform.c
*
* DESCRIPTION : Source file containing transform functions
*
* AUTHOR : filipang           
* 
* START DATE :    12/11/2021
*
*******************************************************************************/

Entity* transformGetEntity(Transform *transform)
{
	return (Entity *)((void*)transform - struct_offset(Entity, transform));
}

int transformCheckCollision(Transform *t1, Transform *t2)
{
	if(t1->position.x - t1->collider.x/2 < t2->position.x + t2->collider.w/2 &&
       t1->position.x + t1->collider.w/2 > t2->position.x - t2->collider.w/2 &&
       t1->position.y - t1->collider.h/2 < t2->position.y + t2->collider.h/2 &&
       t1->position.y + t1->collider.h/2 > t2->position.y - t2->collider.h/2 &&
	   t1->level == t2->level)
	{
		return 1;
	}
	return 0;
}

int transformCheckRectCollision(Vector2f position, Vector2f size, int level,
							 	Transform *t2)
{
	if(position.x - size.w/2 < t2->position.x + t2->collider.w/2 &&
       position.x + size.w/2 > t2->position.x - t2->collider.w/2 &&
       position.y - size.h/2 < t2->position.y + t2->collider.h/2 &&
       position.y + size.h/2 > t2->position.y - t2->collider.h/2 &&
	   level == t2->level)
	{
		return 1;
	}
	return 0;
}

int transformCheckCollisions(Transform *transform)
{
	PersistentGameState *state = memoryGetPersistentGameState();

	Entity *entities = memoryGetEntities();
	int collision = 0;

	int entities_skipped = 0;
	for(int i = 0; i < state->entity_count + entities_skipped; i++)
	{
		Entity *entity_other = entityGet(i);
		Transform *transform_other = &entity_other->transform;
		if(entity_other)
		{
			if(transform != transform_other &&
			   transformCheckCollision(transform, transform_other) &&
			   entity_other->has_creature)
			{
				collision = 1;
			}
		}
		else
		{
			entities_skipped++;
		}
	}

	return collision;
}

int transformCheckRectCollisions(Vector2f position, Vector2f size, int level)
{
	PersistentGameState *state = memoryGetPersistentGameState();

	Entity *entities = memoryGetEntities();
	int collision = 0;

	int entities_skipped = 0;
	for(int i = 0; i < state->entity_count + entities_skipped; i++)
	{
		Entity *entity_other = entityGet(i);
		Transform *transform_other = &entity_other->transform;
		if(entity_other)
		{
			if(transformCheckRectCollision(position, size, level, 
				   						   transform_other) &&
			   entity_other->has_creature)
			{
				collision = 1;
			}
		}
		else
		{
			entities_skipped++;
		}
	}

	return collision;
}

void transformMove(Transform *transform, Vector2f delta)
{
	transform->position.x += delta.x; 
	transform->position.y += delta.y; 
}

void transformTryMove(Transform *transform, Vector2f delta)
{
	PersistentGameState *state = memoryGetPersistentGameState();
	Entity *entity = transformGetEntity(transform);
	Transform possible_transform = *transform;

	// NOTE(filip): This checks collision on the two axis seperately 
	// 				so movement doesn't completely stop when colliding
	
	transform->position.x += delta.x;

	if(mapCheckCollision(transform, mapGetCurrent()) || 
	   transformCheckCollisions(transform))
	{
		transform->position.x -= delta.x;
	}

	transform->position.y += delta.y;

	if(mapCheckCollision(transform, mapGetCurrent()) || 
	   transformCheckCollisions(transform))
	{
		transform->position.y -= delta.y;
	}
}

Vector2f transformGetRenderCorner(Transform *transform)
{
	Vector2f a = vector2fMinus
				 (
				 	transform->position,
				 	vector2fDivide(transform->render, 2)
				 );

	return a;
}

Vector2f transformGetColliderCorner(Transform *transform)
{
	Vector2f a = vector2fMinus
				 (
				 	transform->position,
					vector2fDivide(transform->collider, 2)
				 );
	
	return a;
}

Vector2f transformGetTriggerCorner(Transform *transform)
{
	Vector2f a = vector2fMinus
				 (
				 	transform->position,
					vector2fDivide(transform->trigger, 2)
				 );
	
	return a;
}

Vector2f transformGetRenderCenter(Transform *transform)
{
	return transform->position;
}

Vector2f transformGetColliderCenter(Transform *transform)
{
				 	
	return transform->position;
}

Vector2f transformGetTriggerCenter(Transform *transform)
{
				 	
	return transform->position;
}

Vector2f transformGetScreenRenderCorner(Transform *transform) 
{
	PersistentGameState *state = memoryGetPersistentGameState();

	Transform *camera = &state->camera_transform; 

	Vector2f vec2 = vector2fMinus
					(
						transformGetRenderCorner(transform),
						camera->position
					);

	vec2.x += camera->render.w/2;
	vec2.y += camera->render.h/2;
	
	return vec2;
}

Vector2f transformGetScreenRenderCenter(Transform *transform) 
{
	PersistentGameState *state = memoryGetPersistentGameState();

	Transform *camera = &state->camera_transform; 

	Vector2f vec2 = vector2fMinus
					(
						transformGetRenderCorner(transform),
						camera->position
					);

	vec2.x += camera->render.w/2 + transform->render.w/2;
	vec2.y += camera->render.h/2 + transform->render.h/2;
	
	return vec2;
}

Vector2f transformGetScreenColliderCorner(Transform *transform) 
{
	PersistentGameState *state = memoryGetPersistentGameState();

	Transform *camera = &state->camera_transform; 

	Vector2f vec2 = vector2fMinus
					(
						transformGetColliderCorner(transform),
						camera->position
					);

	vec2.x += camera->collider.w/2;
	vec2.y += camera->collider.h/2;
	
	return vec2;
}

Vector2f transformGetScreenColliderCenter(Transform *transform) 
{
	PersistentGameState *state = memoryGetPersistentGameState();

	Transform *camera = &state->camera_transform; 

	Vector2f vec2 = vector2fMinus
					(
						transformGetColliderCorner(transform),
						camera->position
					);

	vec2.x += camera->render.w/2 + transform->collider.w/2;
	vec2.y += camera->render.h/2 + transform->collider.h/2;
	
	return vec2;
}

Vector2f transformGetScreenTriggerCorner(Transform *transform) 
{
	PersistentGameState *state = memoryGetPersistentGameState();

	Transform *camera = &state->camera_transform; 

	Vector2f vec2 = vector2fMinus
					( 
						transformGetTriggerCorner(transform),
						camera->position
					);

	vec2.x += camera->render.w/2;
	vec2.y += camera->render.h/2;
	
	return vec2;
}

Vector2f transformGetScreenTriggerCenter(Transform *transform) 
{
	PersistentGameState *state = memoryGetPersistentGameState();

	Transform *camera = &state->camera_transform; 

	Vector2f vec2 = vector2fMinus
					(    
						transformGetTriggerCorner(transform),
						camera->position
					);

	vec2.x += camera->render.w/2 + transform->trigger.w/2;
	vec2.y += camera->render.h/2 + transform->trigger.h/2;
	
	return vec2;
}
