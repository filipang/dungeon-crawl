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
} Player;

// NOTE(filip): This information should be saved to disk when saving the game
// TODO(filip): Establish procedure for iterating game elements without issues
typedef struct PersistentGameState
{
	int item_count;
	int active_count;
	int creature_count;
	int map_count;

	Player player;

	int current_level;

	Transform camera_transform;

	int player_action;
	double game_time;
	double game_delta_time;

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

	int open_inventory;
} TransientGameState;

void gameLoadFirstLevel();
void gameLoadNextLevel();

void gameInitializeState();

void gameProcessCamera();
void gameProcessFrame();

void gameCheckDeath();

#endif
