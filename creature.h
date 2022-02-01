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
	int   animation_attack_id;
	Vector2f forward_direction;
	float attack_range;
	float attack_duration;
	Vector2f attack_hitbox_size;
	float attack_hitbox_range;
} Creature;

void creatureCreatePlayer(Vector2f position, int level);
void creatureCreateEnemy(Vector2f position, int level);
void creatureDamage(Creature* attacker, Creature* target);
void creatureStartAttack(Creature* attacker);
void creatureEndAttack(Creature* attacker);
int creatureCheckCollision(struct Entity *entity);
void creatureDrawHealthbar(Creature *creature);
void creatureDrawAttackCharge(Creature *creature);
void creatureProcessPlayer();
void creatureProcessEnemy(int id);
void creatureProcess(int id);
void creatureProcessList();
void creatureSetState(Creature *creature_ptr, int state);
void creatureUpdateAnimation(Creature *creature_ptr);
#endif
