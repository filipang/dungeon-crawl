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

void* transformGetList(int object_type)
{
	switch(object_type)
	{
		case OBJECT_TYPE_ITEM:
			return memoryGetItems();	
			break;

		case OBJECT_TYPE_CREATURE:
			return memoryGetCreatures();	
			break;

		case OBJECT_TYPE_ACTIVE:
			return memoryGetActives();
			break;

		default:
			return NULL; 
			break;

	}
}

int* transformGetListSize(int object_type)
{
	PersistentGameState *state = memoryGetPersistentGameState();
	switch(object_type)
	{
		case OBJECT_TYPE_ITEM:
			return &state->item_count;	
			break;

		case OBJECT_TYPE_CREATURE:
			return &state->creature_count;	
			break;

		case OBJECT_TYPE_ACTIVE:
			return &state->active_count;
			break;

		default:
			return NULL; 
			break;

	}
}

int transformGetListMaxMemory(int object_type)
{
	switch(object_type)
	{
		case OBJECT_TYPE_ITEM:
			return global_memory->items_max_memory_size;	
			break;

		case OBJECT_TYPE_CREATURE:
			return global_memory->creatures_max_memory_size;	
			break;

		case OBJECT_TYPE_ACTIVE:
			return global_memory->actives_max_memory_size;	
			break;

		default:
			return 0; 
			break;

	}
}

int transformGetSize(int object_type)
{
	switch(object_type)
	{
		case OBJECT_TYPE_ITEM:
			return sizeof(Item);	
			break;

		case OBJECT_TYPE_CREATURE:
			return sizeof(Creature);	
			break;

		case OBJECT_TYPE_ACTIVE:
			return sizeof(Active);
			break;

		default:
			return 0; 
			break;

	}
}

int transformMemoryOutOfBounds(int id, int object_type)
{
	return id * transformGetSize(object_type) >= 
		   transformGetListMaxMemory(object_type);
}

// TODO(filip): optimize this
// TODO(filip):	test this thoroughly 
int transformCreate(int object_type)
{
	PersistentGameState *state = memoryGetPersistentGameState();
	Transform *transforms = transformGetList(object_type);
	Transform *transform_ptr;
	int i = 0;
	while(i * transformGetSize(object_type) < transformGetListMaxMemory(object_type))
	{
		transform_ptr = 
			(void *)transforms + i * transformGetSize(object_type);
		if(transform_ptr->created == 0) 
		{
			transform_ptr->created = 1;
			transform_ptr->id = i;	
			transform_ptr->object_type = object_type;
			(*(transformGetListSize(object_type)))++;
			return i;
		}
		i++;
	}
	printf("NOT ENOUGH MEMORY TO CREATE TRANSFORM!\n");
	return -1;

}

void transformDelete(int id, int object_type)
{
	PersistentGameState *state = memoryGetPersistentGameState();

	Transform *transforms = transformGetList(object_type);

	Transform *transform_ptr = 
		(void *)transforms + id * transformGetSize(object_type);

	if(transform_ptr->created == 1)
	{
		transform_ptr->created = 0;
		(*(transformGetListSize(object_type)))--;
	}
	else
	{
		printf("TRIED TO DELETE NON-EXISTING TRANSFORM\n");
	}
}

Transform* transformGet(int id, int object_type)
{
	if(id < 0)
		return NULL;
	PersistentGameState *state = memoryGetPersistentGameState();

	Transform *transforms = transformGetList(object_type);

	Transform *transform_ptr = 
		(void *)transforms + id * transformGetSize(object_type);

	if(transform_ptr->created == 1)
	{
		return transform_ptr;
	}
	return NULL;
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

void transformMove(Transform *transform, Vector2f delta)
{
	transform->position.x += delta.x; 
	transform->position.y += delta.y; 
}

void transformTryMove(Transform *transform, Vector2f delta)
{
	PersistentGameState *state = memoryGetPersistentGameState();
	Transform possible_transform = *transform;

	possible_transform.position.x += delta.x; 
	possible_transform.position.y += delta.y; 

	// NOTE(filip): This checks collision on the two axis seperately 
	// 				so movement doesn't completely stop when colliding
	
	Transform possible_transform_x = possible_transform;
	possible_transform_x.position.y = transform->position.y;

	if(!mapCheckCollision(&possible_transform_x, mapGetCurrent()) &&
	   !creatureCheckCollision(&possible_transform_x))
	{
		*(transform) = possible_transform_x;
	}

	Transform possible_transform_y = possible_transform;
	possible_transform_y.position.x = transform->position.x;

	if(!mapCheckCollision(&possible_transform_y, mapGetCurrent()) &&
	   !creatureCheckCollision(&possible_transform_y))
	{
		*(transform) = possible_transform_y;
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

	printf("%f");

	Vector2f vec2 = vector2fMinus
					(    
						transformGetTriggerCorner(transform),
						camera->position
					);

	vec2.x += camera->render.w/2 + transform->trigger.w/2;
	vec2.y += camera->render.h/2 + transform->trigger.h/2;
	
	return vec2;
}
