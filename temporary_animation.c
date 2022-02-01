/*******************************************************************************
* 
* FILENAME : temporary_animation.c
*
* DESCRIPTION : Source file containing temporary animation functions
*
* AUTHOR : filipang           
* 
* START DATE :    26/12/2021
*
*******************************************************************************/

Entity* temporaryAnimationGetEntity(TemporaryAnimation *temp_anim)
{
	return (Entity *)((void *)temp_anim - struct_offset(Entity, temporary_animation));
}

void temporaryAnimationCreateMeleeSwing(Vector2f position, int level, float angle)	
{
	int id = entityMarkCreate();	
	Entity *entity = entityGet(id);
	entity->has_transform = 1;
	entity->has_animation = 1;
	entity->animation.texture_id = 2;
	entity->has_temporary_animation = 1;
	entity->temporary_animation.countdown = 0.30f;
	entity->temporary_animation.countdown_start = 0.30f;
	entity->temporary_animation.timer = 0;
	entity->temporary_animation.type = TEMPORARY_ANIMATION_MELEE_SWING;

	entity->transform.position = position;
	entity->transform.level = level;
	entity->transform.render = vector2f(32.0, 50.0);
	entity->transform.angle = angle;
}

void temporaryAnimationCreateBloodSplatter(Vector2f position, int level, float angle)
{
	int id = entityMarkCreate();	
	Entity *entity = entityGet(id);
	entity->has_transform = 1;
	entity->has_animation = 1;
	entity->animation.texture_id = 3;
	entity->has_temporary_animation = 1;
	entity->temporary_animation.countdown = 4.0f;
	entity->temporary_animation.countdown_start = 4.0f;
	entity->temporary_animation.timer = 0;
	entity->temporary_animation.type = TEMPORARY_ANIMATION_BLOOD_SPLATTER;

	entity->transform.position = position;
	entity->transform.level = level;
	entity->transform.render = vector2f(150.0, 150.0);
	entity->transform.angle = angle;
}

void temporaryAnimationProcess(int id)
{
	PersistentGameState *state = memoryGetPersistentGameState();
	Entity *entity_temp_anim = entityGet(id);
	TemporaryAnimation *temp_anim = &entity_temp_anim->temporary_animation;
	if(temp_anim->type == TEMPORARY_ANIMATION_MELEE_SWING)
	{
		temp_anim->timer += state->game_delta_time;

		temp_anim->countdown = temp_anim->countdown - state->game_delta_time / (temp_anim->countdown * 5);

		if(temp_anim->countdown <= 0.0f)
		{
			entityMarkDelete(id);
		}
	}
	else if(temp_anim->type == TEMPORARY_ANIMATION_BLOOD_SPLATTER)
	{
		temp_anim->timer += state->game_delta_time;
		if(temp_anim->timer <= 0.15)
		{
			entity_temp_anim->animation.clip_col = 
				16 * temp_anim->timer;
		}
		else
		{
			temp_anim->countdown -= state->game_delta_time;
		}
		if(temp_anim->timer >= temp_anim->countdown_start + 0.15)
		{
			entityMarkDelete(id);
		}
	}
}
