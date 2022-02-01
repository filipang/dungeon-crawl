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
	int state_memory_size; 
	int entities_memory_offset;
	int entities_max_memory_size;
	int maps_memory_offset;
	int maps_max_memory_size;
	// TRANSIENT MEMORY
	// NOTE(filip): This memory chunk is transient (WE ALLOW POINTERS)
	void *transient_memory;
	int   transient_memory_size;
	int input_memory_offset; 
	int input_memory_size;     
	int ui_state_memory_offset;
	int ui_state_memory_size;   
	int sdl_state_memory_offset;
	int sdl_state_memory_size; 
	int audio_state_memory_offset;
	int audio_state_memory_size; 
} MemoryArena;

void memoryAllocGame();
void memorySavePersistent();
void memoryLoadPersistent();
void *memoryGetState();
void *memoryGetEntities();
void *memoryGetMaps();
void *memoryGetInputState();
void *memoryGetPersistentGameState();
void *memoryGetTransientGameState();
void *memoryGetGraphicsState();

#endif
