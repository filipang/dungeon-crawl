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

int creatureCreate()
{
	Creature* creature = creatureGet(transformCreate(OBJECT_TYPE_CREATURE));

	if(creature)
	{
		creature->forward_direction = vector2fDown();
		return creature->id;
	}
	else
	{
		return -1;
	}
}

void creatureDelete(int id)
{
	transformDelete(id, OBJECT_TYPE_CREATURE);
}

Creature *creatureGet(int id)
{
	return (Creature *)transformGet(id, OBJECT_TYPE_CREATURE);
}

void creatureCreatePlayer(Vector2f position)
{

	PersistentGameState *state = memoryGetPersistentGameState();
	int creature_id = creatureCreate();
	state->player.creature_id = creature_id;
	Creature *creature_ptr = creatureGet(creature_id);

	Transform *transform = (Transform *)creature_ptr;

	transform->position = position;

	transform->render   = vector2f(32.0, 50.0);
	transform->collider = vector2f(24.0, 46.0);
	transform->trigger  = vector2f(64.0, 100.0);

	creature_ptr->type = CREATURE_PLAYER;
	creature_ptr->level = state->current_level;
	
	creature_ptr->max_health = 10;
	creature_ptr->health = 10;
	creature_ptr->damage = 3;
	creature_ptr->movement_speed = 180.0;	
	creature_ptr->vision_range = 400;
}

void creatureCreateEnemy(Vector2f position)
{
	PersistentGameState *state = memoryGetPersistentGameState();
	int creature_id = creatureCreate();
	Creature *creature_ptr = creatureGet(creature_id);
	Transform *transform = (Transform *)creature_ptr;
	Map *map_ptr = mapGetCurrent();

	transform->position = position;

	transform->render   = vector2f(32.0, 50.0);
	transform->collider = vector2f(24.0, 46.0);
	transform->trigger  = vector2f(64.0, 100.0);

	creature_ptr->type = CREATURE_ENEMY;
	creature_ptr->level = state->current_level;

	creature_ptr->max_health = 10;
	creature_ptr->health = 10;
	creature_ptr->damage = 2;
	creature_ptr->movement_speed = 160.0;	
	creature_ptr->vision_range = 200;
}

void creatureProcessPlayer()
{
	PersistentGameState *state = memoryGetPersistentGameState();
	TransientGameState *ui_state = memoryGetTransientGameState();
	InputState *input = memoryGetInputState();
	Creature *player_creature = creatureGet(state->player.creature_id);

	// NOTE(filip): This is for keyboard arrow movement
	Vector2f move_input =  
	{
		!!input->move_right.key_hold - !!input->move_left.key_hold,
		!!input->move_down.key_hold - !!input->move_up.key_hold
	};

	if(!player_creature->animation_lock)
	{
		if(move_input.x != 0 || move_input.y != 0)
		{
			player_creature->animation_state = ANIMATION_STATE_WALK;
			player_creature->forward_direction = vector2fNormalize(move_input);
			Vector2f delta = vector2fMultiply
			(
				player_creature->forward_direction, 
				player_creature->movement_speed * state->game_delta_time
			);
										
			transformTryMove((Transform *)player_creature, delta);
		}
		else
		{
			player_creature->animation_state = ANIMATION_STATE_IDLE;
		}

	}

	#define MAX_DISTANCE 999999
	float min_distance = MAX_DISTANCE;
	int min_id = -1;
	int min_type = -1;
	int skipped_actives = 0;
	Active *active_ptr;
	for(int i = 0; i < state->active_count + skipped_actives; i++)
	{
		active_ptr = activeGet(i);
		if(active_ptr)
		{
			float distance = 
				vector2fDistance(active_ptr->position, 
								 player_creature->position);

			if(active_ptr->level == state->current_level &&
			   distance < min_distance &&
			   distance < 100)
			{
				min_id = active_ptr->id;
				min_type = active_ptr->object_type;
				min_distance = distance;
			}
		}
		else
		{
			skipped_actives++;
		}
	}

	Item *item_ptr;
	int skipped_items = 0;
	for(int i = 0; i < state->item_count + skipped_items; i++)
	{
		item_ptr = itemGet(i);
		if(item_ptr)
		{
			float distance = 
				vector2fDistance(item_ptr->position, 
								 player_creature->position);

			if(item_ptr->level == state->current_level &&
			   item_ptr->state == ITEM_STATE_GROUND &&
			   distance < min_distance && 
			   distance < 100)
			{
				min_id = item_ptr->id;
				min_type = item_ptr->object_type;
				min_distance = distance;
			}
		}
		else
		{
			skipped_items++;
		}
	}

	ui_state->highlight_type = min_type;
	ui_state->highlight_id = min_id;
	
	if(input->attack.key_press && !player_creature->animation_lock)
	{
		creatureStartAttack(player_creature);
	}

	if(input->use.key_press && !player_creature->animation_lock)
	{
		if(ui_state->highlight_type == OBJECT_TYPE_ACTIVE)
		{
			activeStart(ui_state->highlight_id);
		}
		else if(ui_state->highlight_type == OBJECT_TYPE_ITEM)
		{
			int e = itemPickUp(ui_state->highlight_id);
			if(e == -1)
			{
				printf("Inventory full!\n");
			}
		}
	}	

	if(player_creature->animation_state != ANIMATION_STATE_IDLE)
		state->player_action = 1;
	else
		state->player_action = 0;		
}

Creature *creatureGetPlayer()
{
	PersistentGameState *state = memoryGetPersistentGameState();
	return creatureGet(state->player.creature_id);
}

void creatureProcessEnemy(int id)
{
	PersistentGameState *state = memoryGetPersistentGameState();
	Creature *player_creature = creatureGet(state->player.creature_id);
	Creature *enemy_creature = creatureGet(id);

	if(!player_creature)
	{
		printf("creature.c: Enemy %d exception: Player seems to be dead.\n", id);
		return;
	}	
	Vector2f position_delta = 
		vector2fMinus(player_creature->position, enemy_creature->position);

	Vector2f move_delta;

	if(vector2fMagnitude(position_delta) < enemy_creature->vision_range)
	{

		enemy_creature->forward_direction = vector2fNormalize(position_delta);

		move_delta = vector2fMultiply
		(
			enemy_creature->forward_direction,
			enemy_creature->movement_speed * state->game_delta_time
		);

		transformTryMove
		(
			(Transform *)enemy_creature,
			move_delta
		);
	}
	else
	{
		move_delta = vector2fZero();
	}

	if(move_delta.x != 0 || move_delta.y != 0)
	{
		enemy_creature->animation_state = ANIMATION_STATE_WALK;
	}
	else
	{
		enemy_creature->animation_state = ANIMATION_STATE_IDLE;
	}
}

void creatureProcess(int id)
{
	Creature *creature_ptr = creatureGet(id);
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
}

void creatureProcessList()
{
	PersistentGameState *state = memoryGetPersistentGameState();
	Creature *creature_ptr;
	int creatures_skipped = 0;
	
	for(int i = 0; i < state->creature_count + creatures_skipped; i++)
	{
		creature_ptr = creatureGet(i);
		if(transformMemoryOutOfBounds(i, OBJECT_TYPE_CREATURE))
		{
			break;	
		}
		if(creature_ptr)
		{
			if(creature_ptr->level == state->current_level)
			{
				creatureProcess(i);
			}
		}
		else
		{
			creatures_skipped++;
		}
	}
}

int creatureCheckCollision(Transform *transform)
{
	PersistentGameState *state = memoryGetPersistentGameState();
	Creature *creatures = memoryGetCreatures();
	int collision = 0;

	int creatures_skipped = 0;
	for(int i = 0; i < state->creature_count + creatures_skipped; i++)
	{
		Creature *creature_ptr = creatureGet(i);
		if(creature_ptr)
		{
			if(creature_ptr->id != transform->id  &&
			   transformCheckCollision(transform, (Transform *)creature_ptr))
			{
				if(transform->object_type == OBJECT_TYPE_CREATURE)
				{
					//creatureDamage((Creature *)transform, creature_ptr);
				}
				collision = 1;
			}
		}
		else
		{
			creatures_skipped++;
		}
	}

	return collision;
}

int creatureDrawHealthbar(Creature *creature)
{
	GraphicsState *sdl_state = memoryGetGraphicsState();

	Vector2f screenPos = 
		transformGetScreenRenderCenter((Transform *) creature);

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

void creatureStartAttack(Creature *attacker)
{
	creatureSetState(attacker, ANIMATION_STATE_ATTACK);
}

void creatureEndAttack(Creature *attacker)
{
	PersistentGameState *state = memoryGetPersistentGameState();
	Creature *creatures = memoryGetCreatures();

	int creatures_skipped = 0;
	Transform attack_hitbox;
	Vector2f hitbox_position = attacker->position;
	
	// NOTE(filip): Hardcoded attack collision
	Vector2f hitbox_collider = 
	{
		200,
		200
	};
	
	hitbox_position = transformGetRenderCenter((Transform *)attacker);

	attack_hitbox.level = attacker->level;
	attack_hitbox.position = hitbox_position;
	attack_hitbox.collider = hitbox_collider;	
	attack_hitbox.render = vector2fZero();
	attack_hitbox.trigger = vector2fZero();
	
	graphicsDebugDrawTransform(&attack_hitbox);

	// Check all creatures for attack hitbox collision
	for(int i = 0; i < state->creature_count + creatures_skipped; i++)
	{
		Creature *creature_ptr = creatureGet(i);
		if(creature_ptr)
		{
			if(attacker->id != creature_ptr->id &&
			   transformCheckCollision(&attack_hitbox, 
				   		  (Transform *)creature_ptr))
			{
				creatureDamage(attacker, creature_ptr);		
			}
		}
		else
		{
			creatures_skipped ++;
		}
	}

}

void creatureDamage(Creature* attacker, Creature* target)
{
	PersistentGameState *state = memoryGetPersistentGameState();
	target->health = target->health - creatureGet(attacker->id)->damage;
	if(target->health <= 0)
	{
		creatureDelete(target->id);
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
	
	int clip_index;
	switch(creature_ptr->animation_state)
	{
		case ANIMATION_STATE_WALK:

			creature_ptr->animation_timer += state->game_delta_time;
			creature_ptr->animation_lock = 0;
			
			clip_index = 
				floor(creature_ptr->animation_timer / (1.0/ANIMATION_FPS)); 	

			clip_index = clip_index % 8 + 1;

			creature_ptr->clip_col = clip_index;
			creature_ptr->clip_row = 
				0 * 4 + 
				vectorGetFacingDirection(creature_ptr->forward_direction);

			break;

		case ANIMATION_STATE_IDLE:
	
			creature_ptr->animation_timer += state->game_delta_time;
			creature_ptr->animation_lock = 0;
			
			clip_index = 
				floor(creature_ptr->animation_timer / (1.0/(ANIMATION_FPS/4))); 	

			clip_index = clip_index % 2 + 1;

			creature_ptr->clip_col = clip_index;
			creature_ptr->clip_row = 
				0 * 4 + 
				vectorGetFacingDirection(creature_ptr->forward_direction);
			break;

		case ANIMATION_STATE_ATTACK:

			clip_index = 7;
			creature_ptr->animation_timer += state->game_delta_time;
			creature_ptr->animation_lock = 1;

			if(creature_ptr->animation_timer >= 0.4)
			{
				creature_ptr->animation_state = ANIMATION_STATE_IDLE;
				creature_ptr->animation_lock = 0;
				creatureEndAttack(creature_ptr);
			}
			creature_ptr->clip_col = clip_index;
			creature_ptr->clip_row = 
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
}
