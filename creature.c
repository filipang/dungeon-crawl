/*******************************************************************************
* 
* FILENAME : creature.c
*
* DESCRIPTION : Source file containing creature functions
*
* AUTHOR : filipang           
* 
* START DATE :    11/11/2021
*
*******************************************************************************/

Entity *creatureGetEntity(Creature *creature)
{
	return (Entity *)((void *)creature - struct_offset(Entity, creature));	
}

void creatureCreatePlayer(Vector2f position, int level)
{

	PersistentGameState *state = memoryGetPersistentGameState();
	int creature_id = entityMarkCreate();
	Entity *entity_player = entityGet(creature_id);
	entity_player->has_creature = 1;
	entity_player->has_animation = 1;
	entity_player->animation.texture_id = 0;
	entity_player->has_transform = 1;
	state->player.creature_id = creature_id;
	Creature *creature_ptr = &entity_player->creature;
	Transform *transform = &entity_player->transform;

	transform->position = position;

	transform->render   = vector2f(32.0, 50.0);
	transform->collider = vector2f(24.0, 46.0);
	transform->trigger  = vector2f(64.0, 100.0);

	creature_ptr->type = CREATURE_PLAYER;
	transform->level = level;
	
	creature_ptr->max_health = 10;
	creature_ptr->health = 10;
	creature_ptr->damage = 3;
	creature_ptr->movement_speed = 200.0;	
	creature_ptr->vision_range = 400;
	creature_ptr->attack_duration = 0.3;
	
	for(int i = 0; i < 15; i++)
	{
		state->player.equipped_items[i] = -1;
	}

	Vector2f hitbox_collider = {50, 50};

	creature_ptr->attack_hitbox_range = 50;	
	creature_ptr->attack_hitbox_size = hitbox_collider;
}

void creatureCreateEnemy(Vector2f position, int level)
{
	PersistentGameState *state = memoryGetPersistentGameState();
	int creature_id = entityMarkCreate();
	Entity *entity_enemy = entityGet(creature_id);
	entity_enemy->has_creature = 1;
	entity_enemy->has_animation = 1;
	entity_enemy->animation.texture_id = 0;

	entity_enemy->has_transform = 1;
	Creature *creature_ptr = &entity_enemy->creature;
	Transform *transform = &entity_enemy->transform;
	Map *map_ptr = mapGetCurrent();

	transform->position = position;

	transform->render   = vector2f(32.0, 50.0);
	transform->collider = vector2f(24.0, 46.0);
	transform->trigger  = vector2f(64.0, 100.0);

	creature_ptr->type = CREATURE_ENEMY;
	transform->level = level;

	creature_ptr->max_health = 10;
	creature_ptr->health = 10;
	creature_ptr->damage = 1;
	creature_ptr->movement_speed = 220.0;	
	creature_ptr->vision_range = 400;
	creature_ptr->attack_duration = 0.3;
	
	Vector2f hitbox_collider = {50, 50};

	creature_ptr->attack_hitbox_range = 50;	
	creature_ptr->attack_hitbox_size = hitbox_collider;
}

void creatureProcessPlayer()
{
	PersistentGameState *state = memoryGetPersistentGameState();
	TransientGameState *ui_state = memoryGetTransientGameState();
	InputState *input = memoryGetInputState();
	Entity *entity_player = entityGet(state->player.creature_id);
	Creature *creature_ptr = &entity_player->creature;
	Transform *transform_ptr = &entity_player->transform;

	// NOTE(filip): This is for keyboard arrow movement
	Vector2f move_input =  
	{
		!!input->move_right.key_hold - !!input->move_left.key_hold,
		!!input->move_down.key_hold - !!input->move_up.key_hold
	};

	if(!creature_ptr->animation_lock)
	{
		if(move_input.x != 0 || move_input.y != 0)
		{
			creature_ptr->animation_state = ANIMATION_STATE_WALK;
			creature_ptr->forward_direction = vector2fNormalize(move_input);
			Vector2f delta = vector2fMultiply
			(
				creature_ptr->forward_direction, 
				creature_ptr->movement_speed * state->game_delta_time
			);
										
			transformTryMove(transform_ptr, delta);
		}
		else
		{
			creature_ptr->animation_state = ANIMATION_STATE_IDLE;
		}

	}

	#define MAX_DISTANCE 999999
	float min_distance = MAX_DISTANCE;
	int min_id = -1;
	int min_type = -1;
	int skipped_entities = 0;
	Entity *entity_ptr;
	for(int i = 0; i < state->entity_count + skipped_entities; i++)
	{
		entity_ptr = entityGet(i);
		if(entity_ptr && entity_ptr->created)
		{
			if(entity_ptr->has_transform)
			{
				float distance = 
					vector2fDistance(entity_ptr->transform.position, 
									 transform_ptr->position);

				if(entity_ptr->transform.level == state->current_level &&
				   distance < min_distance &&
				   distance < 100 &&
				   (entity_ptr->has_active || entity_ptr->has_item))
				{
					min_id = entity_ptr->id;
					min_distance = distance;
				}
			}
		}
		else
		{
			skipped_entities++;
		}
	}

	ui_state->highlight_id = min_id;
	Entity *entity_highlight = entityGet(min_id);	
	int attack = 0;

	if(!creature_ptr->animation_lock)
	{
		Vector2f attack_direction = vector2fZero();
		if(input->attack_up.key_press)
		{
			attack_direction = vector2fPlus(attack_direction, vector2f(0, -1));
			attack = 1;
		}
		if(input->attack_down.key_press)
		{
			attack_direction = vector2fPlus(attack_direction, vector2f(0, 1));
			attack = 1;
		}
		if(input->attack_left.key_press)
		{
			attack_direction = vector2fPlus(attack_direction, vector2f(-1, 0));
			attack = 1;
		}
		if(input->attack_right.key_press)
		{
			attack_direction = vector2fPlus(attack_direction, vector2f(1, 0));
			attack = 1;
		}
		if(attack)
		{
			creature_ptr->forward_direction = vector2fNormalize(attack_direction);
			creatureStartAttack(creature_ptr);
		}
	}

	if(min_id != -1 && input->use.key_press && !creature_ptr->animation_lock)
	{
		if(entity_highlight->has_active)
		{
			activeStart(ui_state->highlight_id);
		}
		else if(entity_highlight->has_item)
		{
			int e = itemPickUp(ui_state->highlight_id);
			if(e == -1)
			{
				printf("Inventory full!\n");
			}
			else
			{
				ui_state->highlight_id = -1;
			}
		}
	}	

	if(creature_ptr->animation_state != ANIMATION_STATE_IDLE)
		state->player_action = 1;
	else
		state->player_action = 0;		
}

void creatureProcessEnemy(int id)
{
	PersistentGameState *state = memoryGetPersistentGameState();
	Entity *player_entity = entityGet(state->player.creature_id);
	Creature *player_creature = &player_entity->creature;
	Transform *player_transform = &player_entity->transform;
	Entity *enemy_entity = entityGet(id);
	Creature *enemy_creature = &enemy_entity->creature;
	Transform *enemy_transform = &enemy_entity->transform;

	if(!player_creature)
	{
		printf("creature.c: Enemy %d exception: Player seems to be dead.\n", id);
		return;
	}	
	Vector2f position_delta = 
		vector2fMinus(player_transform->position, enemy_transform->position);

	Vector2f move_delta = vector2fZero();
	float distance_to_player = vector2fMagnitude(position_delta); 

	if(!enemy_creature->animation_lock)
	{
		if(distance_to_player < enemy_creature->vision_range)
		{
			if(enemy_creature->animation_state != ANIMATION_STATE_ATTACK &&
			   distance_to_player < 50)
			{
				creatureStartAttack(enemy_creature);
			}
			else
			{
				enemy_creature->forward_direction =
					vector2fNormalize(position_delta);

				move_delta = vector2fMultiply
				(
					enemy_creature->forward_direction,
					enemy_creature->movement_speed * state->game_delta_time
				);

				transformTryMove
				(
					enemy_transform,
					move_delta
				);
			}
		}
	}

}

void creatureProcess(int id)
{
	GraphicsState *sdl_state = memoryGetGraphicsState();
	Entity *entity_ptr = entityGet(id);
	Creature *creature_ptr = &entity_ptr->creature;
	switch(creature_ptr->type)
	{
		case CREATURE_PLAYER:
			creatureProcessPlayer();
			break;
		case CREATURE_ENEMY:
			creatureProcessEnemy(id);
			break;
		default:
			printf("Unknown creature type %d\n", creature_ptr->type);
			break;
	};

	creatureUpdateAnimation(creature_ptr);

	if(creature_ptr->animation_state == ANIMATION_STATE_ATTACK)
	{
		Vector2f hitbox_position = vector2fPlus(entity_ptr->transform.position, 
								   vector2fMultiply(creature_ptr->forward_direction, 
													creature_ptr->attack_hitbox_range));
		
		SDL_SetRenderDrawColor(sdl_state->renderer, 255, 100, 50, 255);
		SDL_FRect rect;
		rect.x = hitbox_position.x;
		rect.y = hitbox_position.y;
		rect.w = creature_ptr->attack_hitbox_size.w;
		rect.h = creature_ptr->attack_hitbox_size.h;
		rect.x -= rect.w/2;
		rect.y -= rect.h/2;
		rect = graphicsApplyCamera(rect);

		graphicsDebugDrawRect(rect.x, rect.y, rect.w, rect.h);
	}
}

void creatureDrawHealthbar(Creature *creature)
{
	GraphicsState *sdl_state = memoryGetGraphicsState();

	Vector2f screenPos = 
		transformGetScreenRenderCenter(&(creatureGetEntity(creature)->transform));

	SDL_FRect r1;

	// Draw Healthbar box
	SDL_SetRenderDrawColor( sdl_state->renderer, 0, 0, 0, 255 );

	r1.w = 40;
	r1.h = 8;
    r1.x = screenPos.x - r1.w/2;
	r1.y = screenPos.y - 40 - r1.h/2;

	SDL_RenderFillRectF( sdl_state->renderer, &r1 );
	
	SDL_FRect r2;

	// Draw Healthbar 
	SDL_SetRenderDrawColor( sdl_state->renderer, 40, 245, 40, 255 );

	r2.w = (int) (38.0 * (creature->health / creature->max_health));
	r2.h = 6;
    r2.x = screenPos.x - r1.w/2 + 1;
	r2.y = screenPos.y - 40 - r2.h/2;

	SDL_RenderFillRectF( sdl_state->renderer, &r2 );
}

void creatureDrawAttackCharge(Creature *creature)
{
	GraphicsState *sdl_state = memoryGetGraphicsState();

	Vector2f screenPos = 
		transformGetScreenRenderCenter(&(creatureGetEntity(creature)->transform));

	SDL_FRect r1;

	// Draw Healthbar box
	SDL_SetRenderDrawColor( sdl_state->renderer, 0, 0, 0, 255 );

	r1.w = 40;
	r1.h = 5;
    r1.x = screenPos.x - r1.w/2;
	r1.y = screenPos.y - 32 - r1.h/2;

	SDL_RenderFillRectF( sdl_state->renderer, &r1 );
	
	SDL_FRect r2;

	// Draw Healthbar 
	SDL_SetRenderDrawColor( sdl_state->renderer, 245, 40, 40, 255 );

	if(creature->animation_state == ANIMATION_STATE_ATTACK)
	{
		r2.w = (int) (38.0 * (creature->animation_timer / creature->attack_duration));
		r2.h = 3;
		r2.x = screenPos.x - r1.w/2 + 1;
		r2.y = screenPos.y - 32 - r2.h/2;

		SDL_RenderFillRectF( sdl_state->renderer, &r2 );
	}
}

void creatureStartAttack(Creature *attacker)
{
	creatureSetState(attacker, ANIMATION_STATE_ATTACK);
}

void creatureEndAttack(Creature *attacker)
{
	PersistentGameState *state = memoryGetPersistentGameState();
	GraphicsState *sdl_state = memoryGetGraphicsState();
	Entity *entity_attacker = creatureGetEntity(attacker);
	Transform *attacker_transform = &entity_attacker->transform;

	int entities_skipped = 0;


	Vector2f hitbox_position = vector2fPlus(attacker_transform->position, 
							   vector2fMultiply(attacker->forward_direction, 
								   		        attacker->attack_hitbox_range));
	
	SDL_SetRenderDrawColor(sdl_state->renderer, 255, 0, 0, 255);
	SDL_FRect rect;
	rect.x = hitbox_position.x;
	rect.y = hitbox_position.y;
	rect.w = attacker->attack_hitbox_size.w;
	rect.h = attacker->attack_hitbox_size.h;
	rect.x -= rect.w/2;
	rect.y -= rect.h/2;
	rect = graphicsApplyCamera(rect);

	graphicsDebugDrawRect(rect.x, rect.y, rect.w, rect.h);
	temporaryAnimationCreateMeleeSwing(hitbox_position, 
			  						   attacker_transform->level, 
									   vector2fGetAngle(attacker->forward_direction));

	// Check all creatures for attack hitbox collision
	for(int i = 0; i < state->entity_count + entities_skipped; i++)
	{
		Entity *entity_ptr = entityGet(i);
		if(entity_ptr)
		{
			if(entity_attacker->id != entity_ptr->id &&
			   transformCheckRectCollision(hitbox_position, 
				   						   attacker->attack_hitbox_size,
				  						   attacker_transform->level, 
				   		   				   &entity_ptr->transform) &&
			   entity_ptr->has_creature)
			{
				creatureDamage(attacker, &entity_ptr->creature);		
				audioPlaySound(2, 0);
				entityKnockback(entity_ptr, entity_attacker->creature.damage * 30, 
								0.3, entity_attacker->creature.forward_direction);
			}
		}
		else
		{
			entities_skipped ++;
		}
	}
	audioPlaySound(0, 0);

}

void creatureDamage(Creature* attacker, Creature* target)
{
	PersistentGameState *state = memoryGetPersistentGameState();
	target->health = target->health - attacker->damage;
	if(target->health <= 0)
	{
		entityMarkDelete(creatureGetEntity(target)->id);
		Vector2f splatter_position = creatureGetEntity(target)->transform.position;
		splatter_position = vector2fPlus(splatter_position, 
							vector2fMultiply(attacker->forward_direction, 25));
		temporaryAnimationCreateBloodSplatter(splatter_position,
											  creatureGetEntity(target)->transform.level,
											  vector2fGetAngle(attacker->forward_direction) - 20);
		state->kill_count++;
	}
}

void creatureSetState(Creature *creature_ptr, int state)
{
	creature_ptr->animation_state = state;
	creature_ptr->animation_timer = 0;
}

void creatureUpdateAnimation(Creature *creature_ptr)
{
	PersistentGameState *state = memoryGetPersistentGameState();
	Entity *creature_entity = creatureGetEntity(creature_ptr);
	Animation *animation_ptr = &creature_entity->animation;
	int clip_index;
	switch(creature_ptr->animation_state)
	{
		case ANIMATION_STATE_WALK:

			creature_ptr->animation_timer += state->game_delta_time;
			creature_ptr->animation_lock = 0;
			
			clip_index = 
				floor(creature_ptr->animation_timer / (1.0/ANIMATION_FPS)); 	

			clip_index = clip_index % 8 + 1;

			animation_ptr->clip_col = clip_index;
			animation_ptr->clip_row = 
				0 * 4 + 
				vectorGetFacingDirection(creature_ptr->forward_direction);

			break;

		case ANIMATION_STATE_IDLE:
	
			creature_ptr->animation_timer += state->game_delta_time;
			creature_ptr->animation_lock = 0;
			
			clip_index = 
				floor(creature_ptr->animation_timer / (1.0/(ANIMATION_FPS/4))); 	

			clip_index = clip_index % 2 + 1;

			animation_ptr->clip_col = clip_index;
			animation_ptr->clip_row = 
				0 * 4 + 
				vectorGetFacingDirection(creature_ptr->forward_direction);
			break;

		case ANIMATION_STATE_ATTACK:

			clip_index = 7;
			creature_ptr->animation_timer += state->game_delta_time;
			creature_ptr->animation_lock = 1;

			if(creature_ptr->animation_timer >= creature_ptr->attack_duration)
			{
				creature_ptr->animation_state = ANIMATION_STATE_IDLE;
				creature_ptr->animation_lock = 0;
				creatureEndAttack(creature_ptr);
			}
			animation_ptr->clip_col = clip_index;
			animation_ptr->clip_row = 
				0 * 4 + 
				vectorGetFacingDirection(creature_ptr->forward_direction);
			break;
	}

}

void creatureRefreshStats(Creature *creature_ptr)
{
	#define REFRESH_STAT(stat) \
	creature_ptr->stat = creature_ptr->base_##stat * \
						 creature_ptr->modifier_##stat;

	REFRESH_STAT(max_health);
	REFRESH_STAT(damage);
	REFRESH_STAT(movement_speed);
	REFRESH_STAT(vision_range);
	REFRESH_STAT(stealth);
	REFRESH_STAT(encumbrance);
}

/*
void creatureDrawList()
{
	PersistentGameState *state = memoryGetPersistentGameState();
	Creature *creatures = memoryGetCreatures();
	Creature *creature_ptr;
	int creature_count = 0, creature_id = 0;

	int creatures_skipped = 0;
	for(int i = 0; i < state->creature_count + creatures_skipped; i++)
	{
		creature_ptr = creatureGet(i);
		if(creature_ptr)
		{
			if(creature_ptr->level == state->current_level)
			{
				graphicsDrawTransform((Transform *)creature_ptr);
				creatureDrawHealthbar(creature_ptr);
			}
		}
		else
		{
			creatures_skipped++;
		}
	}
}*/
