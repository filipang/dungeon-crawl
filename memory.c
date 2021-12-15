/*******************************************************************************
* 
* FILENAME : memory.c
*
* DESCRIPTION : Source file containing memory functions
*
* AUTHOR : filipang           
* 
* START DATE :    5/11/2021
*
*******************************************************************************/

void memoryAllocGame()
{
	// INITIALIZE SINGLETON STRUCT global_memory
	global_memory = calloc(sizeof(MemoryArena), 1);

	// PERSISTENT MEMORY

	int index = 0;

	global_memory->state_memory_offset = index;
	index += sizeof(PersistentGameState);

	global_memory->items_memory_offset = index;
	global_memory->items_max_memory_size = MIB(2);
	index += MIB(2);

	global_memory->actives_memory_offset = index;
	global_memory->actives_max_memory_size = MIB(2);
	index += MIB(2);

	global_memory->creatures_memory_offset = index;
	global_memory->creatures_max_memory_size = MIB(2);	
	index += MIB(2);

	global_memory->maps_memory_offset = index;
	global_memory->maps_max_memory_size = MIB(2);	
	index += MIB(2);

	global_memory->persistent_memory_size = index;
	global_memory->persistent_memory = calloc(index, 1);

	// TRANSIENT MEMORY
	
	index = 0;

	global_memory->input_memory_offset = index;
	global_memory->input_memory_size = sizeof(InputState);
	index += sizeof(InputState);

	global_memory->ui_state_memory_offset = index;
	global_memory->ui_state_memory_size = sizeof(TransientGameState);	
	index += sizeof(TransientGameState);	

	global_memory->sdl_state_memory_offset = index;
	global_memory->sdl_state_memory_size = sizeof(GraphicsState);	
	index += sizeof(GraphicsState);	

	global_memory->transient_memory_size = index;
	global_memory->transient_memory = calloc(index, 1);
}

void *memoryGetPersistentGameState()
{
	return (void *)global_memory->persistent_memory + 
				   global_memory->state_memory_offset;
}

void *memoryGetCreatures()
{
	return (void *)global_memory->persistent_memory + 
				   global_memory->creatures_memory_offset;
}

void *memoryGetItems()
{
	return (void *)global_memory->persistent_memory + 
				   global_memory->items_memory_offset;
}

void *memoryGetActives()
{
	return (void *)global_memory->persistent_memory + 
				   global_memory->actives_memory_offset;
}

void *memoryGetMaps()
{
	return (void *)global_memory->persistent_memory + 
				   global_memory->maps_memory_offset;
}

void *memoryGetInputState()
{
	return (void *)global_memory->transient_memory + 
				   global_memory->input_memory_offset;
}

void *memoryGetTransientGameState()
{
	return (void *)global_memory->transient_memory + 
				   global_memory->ui_state_memory_offset;
}

void *memoryGetGraphicsState()
{
	return (void *)global_memory->transient_memory + 
				   global_memory->sdl_state_memory_offset;
}

void memorySavePersistent()
{
	printf("memory.c: Saving persistent...\n");

	utilsWriteFile("save.data", 
			 	   global_memory->persistent_memory, 
				   global_memory->persistent_memory_size);

	printf("memory.c: Writing persistent memory (%d B) " 
		   "into file \"save.data\" (%d B)\n",
		   global_memory->persistent_memory_size,
		   global_memory->persistent_memory_size);
}

void memoryLoadPersistent()
{
	printf("memory.c: Loading persistent...\n");

	int size;
	utilsLoadFile("save.data", global_memory->persistent_memory, &size);

	printf("memory.c: Read file \"save.data\" (%d B) "
		   "into persistent memory (%d B)\n",
		   size,
		   global_memory->persistent_memory_size);
}
