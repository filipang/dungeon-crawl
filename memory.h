/*******************************************************************************
* 
* FILENAME : memory.h
*
* DESCRIPTION : Header file containing memory functions
*
* AUTHOR : filipang           
* 
* START DATE :    5/11/2021
*
*******************************************************************************/

#ifndef MEMORY_H
#define MEMORY_H

typedef struct MemoryArena
{
	// PERSISTENT MEMORY
	// NOTE(filip): This memory chunk is serializable (NO SAVED ADDRESSES)
	void *persistent_memory;
	int   persistent_memory_size;

	// NOTE(filip): These values are serializable
	int state_memory_offset;
	int state_memory_size; //sizeof(PersistentGameState)

	int items_memory_offset;
	int items_max_memory_size;

	int actives_memory_offset;
	int actives_max_memory_size;

	int creatures_memory_offset;
	int creatures_max_memory_size;

	int maps_memory_offset;
	int maps_max_memory_size;

	// TRANSIENT MEMORY
	// NOTE(filip): This memory chunk is transient (WE ALLOW ADDRESSES)
	void *transient_memory;
	int   transient_memory_size;

	int input_memory_offset; 
	int input_memory_size; //sizeof(input_controller)

	int ui_state_memory_offset;
	int ui_state_memory_size; //sizeof(ui_game_state)

	int sdl_state_memory_offset;
	int sdl_state_memory_size; //sizeof(sdl_game_state)
} MemoryArena;

void memoryAllocGame();

void *memoryGetState();
void *memoryGetCreatures();
void *memoryGetItems();
void *memoryGetActives();
void *memoryGetMaps();
void *memoryGetInputState();
void *memoryGetPersistentGameState();
void *memoryGetTransientGameState();
void *memoryGetGraphicsState();

void memorySavePersistent();
void memoryLoadPersistent();

#endif
