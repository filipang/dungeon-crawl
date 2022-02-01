/*******************************************************************************
* 
* FILENAME : temporary_animation.h
*
* DESCRIPTION : Header file containing temporary animation function headers and 
* 				structs
*
* AUTHOR : filipang           
* 
* START DATE :    26/12/2021
*
*******************************************************************************/

#define TEMPORARY_ANIMATION_MELEE_SWING		0
#define TEMPORARY_ANIMATION_BLOOD_SPLATTER	1

typedef struct TemporaryAnimation{
	float countdown;	
	float countdown_start;
	float timer;
	int type;
} TemporaryAnimation;

struct Entity* temporaryAnimationGetEntity(TemporaryAnimation *temp_anim);
void temporaryAnimationCreateMeleeSwing(Vector2f position, int level, float angle);	
void temporaryAnimationProcess(int id);
