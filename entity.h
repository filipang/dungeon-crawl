/*******************************************************************************
* 
* FILENAME : entity.h
*
* DESCRIPTION : Header file containing entity function headers and structs
*
* AUTHOR : filipang           
* 
* START DATE :    24/12/2021
*
*******************************************************************************/

typedef struct Knockback
{
	float remaining;
	float power;
	Vector2f direction;
} Knockback;

typedef struct Entity
{
	int created;
	int id;
	int mark_delete;
	int mark_create;
	unsigned char has_transform;
	unsigned char has_animation;
	unsigned char has_creature;
	unsigned char has_item;
	unsigned char has_active;
	unsigned char has_temporary_animation;
	unsigned char has_knockback;
	Transform transform;
	Animation animation;
	Creature  creature;
	Item 	  item;
	Active    active;
	TemporaryAnimation temporary_animation;
	Knockback knockback;
} Entity;

void entityCreate(int id);
int entityMarkCreate();
void entityDelete(int id);
void entityMarkDelete(int id);
Entity* entityGet(int id);
Entity* entityGetPlayer();
void entityProcessList();
void entityDeleteMarkedEntities();
void entityCreateMarkedEntities();
void entityDrawList();
Entity entityZero();
void entityKnockback(Entity *entity, float remaining, float power, Vector2f direction);
Entity entityProcessKnockback(int id);
