/*******************************************************************************
* 
* FILENAME : game.h
*
* DESCRIPTION : Header file containing main game loop
*
* AUTHOR : filipang           
* 
* START DATE :    5/11/2021
*
*******************************************************************************/

#ifndef GAME_H
#define GAME_H

typedef struct Player
{
	int creature_id; 
	int inventory[10][5];
	union
	{
		#define EQUIPPED_ITEM_COUNT 15
		int equipped_items[EQUIPPED_ITEM_COUNT];
		struct
		{	
			int equipped_helmet;
			int equipped_armor;
			int equipped_boots;
			int equipped_weapon;
			int equipped_amulet;
			int equipped_rings[10];
		};
	};
} Player;

// NOTE(filip): This information should be saved to disk when saving the game
// TODO(filip): Establish procedure for iterating game elements without issues
typedef struct PersistentGameState
{
	int entity_count;
	int entity_mark_delete_count;
	int entity_mark_create_count;
	int map_count;
	Player player;
	int current_level;
	int kill_count;
	Transform camera_transform;
	int player_action;
	double game_time;
	double game_delta_time;
	double game_speed;
	double true_time;
	double true_delta_time;
} PersistentGameState;

// NOTE(filip): This information is ignored when saving the game (transient)
typedef struct TransientGameState
{
	int 	 menu_active;
	int		 highlight_type; //This can either select an Active or an Item
	int 	 highlight_id;
	Vector2i highlight_inventorty_position;
	int 	 open_inventory;
	int      draw_debug;
} TransientGameState;

void gameStartTime();
void gameStopTime();
void gameLoadFirstLevel();
void gameLoadNextLevel();
void gameInitializeState();
void gameProcessCamera();
void gameProcessFrame();
void gameCheckDeath();
void gameUpdatePlayerStats();

#endif
