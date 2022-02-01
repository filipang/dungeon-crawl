/*******************************************************************************
* 
* FILENAME : entity.c
*
* DESCRIPTION : Source file containing entity functions
*
* AUTHOR : filipang           
* 
* START DATE :    24/12/2021
*
*******************************************************************************/

void entityCreate(int id)
{
	PersistentGameState *state = memoryGetPersistentGameState();
	Entity *entities = memoryGetEntities();
	entities[id].created = 1;
	entities[id].mark_create = 0;
	state->entity_count++;
}

int entityMarkCreate()
{
	PersistentGameState *state = memoryGetPersistentGameState();
	Entity *entities = memoryGetEntities();
	Entity *entity_ptr;
	int i = 0;
	while(i * sizeof(Entity) < global_memory->entities_max_memory_size)
	{
		entity_ptr = &entities[i];
		if(entity_ptr->created == 0 && entity_ptr->mark_create == 0) 
		{
			*entity_ptr = entityZero();
			entity_ptr->mark_create = 1;
			state->entity_mark_create_count++;
			entity_ptr->id = i;	
			return i;
		}
		i++;
	}
	printf("entity.c: NOT ENOUGH MEMORY TO CREATE ENTITY!\n");
	return -1;

}

void entityDelete(int id)
{
	PersistentGameState *state = memoryGetPersistentGameState();

	Entity *entities = memoryGetEntities();

	if(entities[id].created == 1)
	{
		entities[id].created = 0;
		entities[id].mark_delete = 0;
		entities[id].mark_create = 0;
		state->entity_count--;
	}
	else
	{
		printf("entity.c: TRIED TO DELETE NON-EXISTING ENTITY\n");
	}
}

void entityMarkDelete(int id)
{
	PersistentGameState *state = memoryGetPersistentGameState();

	Entity *entities = memoryGetEntities();

	if(entities[id].created == 1)
	{
		entities[id].mark_delete = 1;
		state->entity_mark_delete_count++;
	}
	else
	{
		printf("entity.c: TRIED TO DELETE NON-EXISTING ENTITY\n");
	}
}

//NOTE(filip): Potential branchless optimisation
Entity* entityGet(int id)
{
	if(id < 0 || id * sizeof(Entity) >= global_memory->entities_max_memory_size)
		return NULL;
	PersistentGameState *state = memoryGetPersistentGameState();

	Entity *entities = memoryGetEntities();

	if(entities[id].created || entities[id].mark_create)
	{
		return &entities[id];
	}
	return NULL;
} 

void entityProcessList()
{
	entityCreateMarkedEntities();

	PersistentGameState *state = memoryGetPersistentGameState();
	Entity *entities = memoryGetEntities();
	Entity *entity_ptr;
	int skipped_entities = 0;
	for(int i = 0; i < state->entity_count + skipped_entities; i++)
	{
		entity_ptr = entityGet(i);
		if(entity_ptr && entity_ptr->created)
		{
			if(entity_ptr->has_creature &&
			   entity_ptr->has_transform &&
			   entity_ptr->transform.level == state->current_level)
			{
				creatureProcess(i);
			}
			if(entity_ptr->has_temporary_animation)
			{
				temporaryAnimationProcess(i);
			}
			if(entity_ptr->has_item)
			{
				//itemProcess(i);
			}
			if(entity_ptr->has_active)
			{
				//activeProcess(i);
			}
			if(entity_ptr->has_knockback)
			{
				entityProcessKnockback(entity_ptr->id);
			}
		}
		else
		{
			skipped_entities++;
		}
	}

	entityDeleteMarkedEntities();
}

void entityCreateMarkedEntities()
{
	PersistentGameState *state = memoryGetPersistentGameState();
	Entity *entities = memoryGetEntities();
	int skipped_entities = 0;
	int entity_count = state->entity_mark_create_count;
	for(int i = 0; i < entity_count + skipped_entities; i++)
	{
		if(entities[i].mark_create)
		{
			entityCreate(i);	
		}
		else
		{
			skipped_entities++;
		}
	}
	state->entity_mark_create_count = 0;
}

void entityDeleteMarkedEntities()
{
	PersistentGameState *state = memoryGetPersistentGameState();
	Entity *entities = memoryGetEntities();
	Entity *entity_ptr;
	int skipped_entities = 0;
	int entity_count = state->entity_mark_delete_count;
	for(int i = 0; i < entity_count + skipped_entities; i++)
	{
		entity_ptr = entityGet(i);
		if(entity_ptr && entity_ptr->mark_delete)
		{
			entityDelete(i);
		}
		else
		{
			skipped_entities++;
		}
	}
	state->entity_mark_delete_count = 0;
}

void entityDrawList()
{
	PersistentGameState *state = memoryGetPersistentGameState();
	Entity *entities = memoryGetEntities();
	Entity *entity_ptr;
	int skipped_entities = 0;
	for(int i = 0; i < state->entity_count + skipped_entities; i++)
	{
		entity_ptr = entityGet(i);
		if(entity_ptr)
		{
			if(entity_ptr->has_creature && 
			   entity_ptr->transform.level == state->current_level)
			{
				graphicsDrawEntity(entity_ptr);
				creatureDrawHealthbar(&entity_ptr->creature);
				creatureDrawAttackCharge(&entity_ptr->creature);
			}
			if(entity_ptr->has_item)
			{
				if(entity_ptr->has_transform &&
				   entity_ptr->transform.level == state->current_level)
				{
					graphicsDrawEntity(entity_ptr);
				}
			}
			if(entity_ptr->has_active &&
			   entity_ptr->transform.level == state->current_level)
			{
				graphicsDrawEntity(entity_ptr);
			}
			if(entity_ptr->has_temporary_animation &&
			   entity_ptr->transform.level == state->current_level)
			{
				graphicsDrawEntity(entity_ptr);
			}
		}
		else
		{
			skipped_entities++;
		}
	}
}

Entity *entityGetPlayer()
{
	PersistentGameState *state = memoryGetPersistentGameState();
	return entityGet(state->player.creature_id);
}

Entity entityZero()
{
	Entity zero = {0};
	return zero;
}

void entityKnockback(Entity *entity, float remaining, 
					 float power, Vector2f direction)
{
	if(entity->has_creature)
	{
		entity->has_knockback = 1;
		entity->creature.animation_lock = 1;
		entity->knockback.remaining = remaining;
		entity->knockback.power = power;
		entity->knockback.direction = direction;
	}
}

Entity entityProcessKnockback(int id)
{
	Entity *entity = entityGet(id);
	Knockback *knockback = &entity->knockback;
	if(entity->has_creature)
	{
		float movement = knockback->power*knockback->remaining;	
		transformTryMove(&entity->transform, vector2fMultiply(knockback->direction,
															  movement));
		knockback->remaining -= movement;
	}
	if(knockback->remaining <= 0.05)
	{
		entity->creature.animation_lock = 0;
		entity->has_knockback = 0;
	}
}
