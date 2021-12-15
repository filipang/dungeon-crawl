/*******************************************************************************
* 
* FILENAME : creature.h
*
* DESCRIPTION : Header file containing creature functions and structs
*
* AUTHOR : filipang           
* 
* START DATE :    11/11/2021
*
*******************************************************************************/

#ifndef CREATURE_H
#define CREATURE_H

#define CREATURE_PLAYER 0
#define CREATURE_ENEMY 1

#define ANIMATION_STATE_IDLE 0
#define ANIMATION_STATE_WALK 1
#define ANIMATION_STATE_ATTACK 2

typedef struct Creature
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

	int type;

	float base_max_health;
	float base_damage;
	float base_movement_speed;
	float base_vision_range;
	float base_stealth;
	float base_encumbrance;

	float modifier_max_health;
	float modifier_damage;
	float modifier_movement_speed;
	float modifier_vision_range;
	float modifier_stealth;
	float modifier_encumbrance;

	float max_health;
	float damage;
	float movement_speed;
	float vision_range;
	float stealth;
	float encumbrance;

	float health;

	int   animation_state;
	int   animation_lock;
	float animation_timer;

	Vector2f forward_direction;
} Creature;

int 	  creatureCreate();
void 	  creatureDelete(int id);
Creature *creatureGet(int id);

void creatureCreatePlayer(Vector2f position);
Creature *creatureGetPlayer();
void creatureCreateEnemy(Vector2f position);

// Damages target creature using attacker stats
void creatureDamage(Creature* attacker, Creature* target);
// Starts the attack animation
void creatureStartAttack(Creature* attacker);
// Checks which creatures are colliding with the attack hitbox and attacks them
void creatureEndAttack(Creature* attacker);
// Checks if a given transform collides with any creature
int  creatureCheckCollision(Transform *transform);
// Draws a creature healthbar
int  creatureDrawHealthbar(Creature *creature);

void creatureProcessPlayer();
void creatureProcessEnemy(int id);
void creatureProcess(int id);
void creatureProcessList();

void creatureSetState(Creature *creature_ptr, int state);
void creatureUpdateAnimation(Creature *creature_ptr);
void creatureDrawList();
#endif
