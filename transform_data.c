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
			return getItems();	
			break;

		case OBJECT_TYPE_CREATURE:
			return getCreatures();	
			break;

		case OBJECT_TYPE_ACTIVE:
			return activeGets();
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
			return sizeof(creature);	
			break;

		case OBJECT_TYPE_ACTIVE:
			return sizeof(Active);
			break;

		default:
			return 0; 
			break;

	}
}

int* transformGetListSize(int object_type)
{
	game_state *state = getState();
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

int transformCreate(int object_type)
{
	game_state *state = getState();
	Transform *transforms = transformGetList(object_type);
	Transform *transform_ptr;
	int i = 0;
	while(i * transformGetSize(object_type) < transformGetListMaxMemory(object_type))
	{
		transform_ptr = 
			transforms + i * transformGetSize(object_type);
		if(transform_ptr->created == 0) 
		{
			transform_ptr->created = 1;
			transform_ptr->id = i;	
			(*(transformGetListSize(object_type)))++;
			return i;
		}
		i++;
	}
	printf("NOT ENOUGH MEMORY TO CREATE TRANSFORM!\n");

}

void transformDelete(int id, int object_type)
{
	game_state *state = getState();

	Transform *transforms = transformGetList(object_type);

	Transform *transform_ptr = 
		transforms + id * transformGetSize(object_type);

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
	game_state *state = getState();

	Transform *transforms = transformGetList(object_type);

	Transform *transform_ptr = 
		transforms + id * transformGetSize(object_type);

	if(transform_ptr->created == 1)
	{
		return transform_ptr;
	}
	printf("TRIED TO GET NON-EXISTING TRANSFORM WITH ID %d\n", id);
	return NULL;
}

int transformCheckCollision(Transform *t1, Transform *t2)
{
	if(t1->position.x < t2->position.x + t2->collider.w &&
       t1->position.x + t1->collider.w > t2->position.x &&
       t1->position.y < t2->position.y + t2->collider.h &&
       t1->collider.h + t1->position.y > t2->position.y)
	{
		return 1;
	}
	return 0;
}

void transformMoveDirection(vector2f delta, 
							float magnitude, 
							Transform *transform)
{
	game_state *state = getState();
	Transform possible_transform = *transform;

	if(abs(delta.x) > 0.01 || abs(delta.y) > 0.01)
	{
		if(abs(delta.x) < 0.01 && delta.y > 0.01)
		{
			possible_transform.position.y += magnitude; 
		}
		else if(abs(delta.x) < 0.01 && delta.y < 0.01)
		{
			possible_transform.position.y -= magnitude; 
		}
		else
		{
			float dir = atan(delta.y/delta.x);

			if(delta.x >= 0 && delta.y >= 0)
			{
				possible_transform.position.x += cos((double)dir) *
												 magnitude;	

				possible_transform.position.y += sin((double)dir) * 
												 magnitude;
			}
			else if(delta.x <= 0 && delta.y >= 0)
			{
				possible_transform.position.x -= cos((double)dir) * 
												 magnitude;

				possible_transform.position.y -= sin((double)dir) * 
												 magnitude;
			}
			else if(delta.x >= 0 && delta.y <= 0)
			{
				possible_transform.position.x += cos((double)dir) * 
												 magnitude;

				possible_transform.position.y += sin((double)dir) * 
												 magnitude;
			}
			else if(delta.x <= 0 && delta.y <= 0)
			{
				possible_transform.position.x -= cos((double)dir) * 
												 magnitude;

				possible_transform.position.y -= sin((double)dir) * 
												 magnitude;
			}
		}
	}

	// NOTE(filip): This checks collision on the two axis seperately 
	// 				so movement doesn't completely stop when colliding
	
	Transform possible_transform_x = possible_transform;
	possible_transform_x.position.y = transform->position.y;

	if(!checkMapCollision(&possible_transform_x, getCurrentMap()) &&
	   !checkCreatureCollision(&possible_transform_x))
	{
		*(transform) = possible_transform_x;
	}
	else
	{
	}

	Transform possible_transform_y = possible_transform;
	possible_transform_y.position.x = transform->position.x;

	if(!checkMapCollision(&possible_transform_y, getCurrentMap()) &&
	   !checkCreatureCollision(&possible_transform_y))
	{
		*(transform) = possible_transform_y;
	}
	else
	{
	}
	
}

