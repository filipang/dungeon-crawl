/*******************************************************************************
* 
* FILENAME : map.c
*
* DESCRIPTION : Source file containing map functions
*
* AUTHOR : filipang           
* 
* START DATE :    11/11/2021
*
*******************************************************************************/

int mapCreate()
{
	PersistentGameState *state = memoryGetPersistentGameState();
	Map *maps = memoryGetMaps();
	Map *map_ptr;
	int i = 0;
	while(i * sizeof(Map) < global_memory->maps_max_memory_size)
	{
		map_ptr = &maps[i];
		if(map_ptr->created == 0)
		{
			map_ptr->created = 1;
			map_ptr->id = i;	
			map_ptr->map_changed = 1;
			state->map_count++;
			return i;
		}
		i++;
	}
	printf("memory.c: NOT ENOUGH MEMORY TO CREATE MAP!\n");
	return -1;
}

void mapDelete(int id)
{
	PersistentGameState *state = memoryGetPersistentGameState();
	Map *maps = memoryGetMaps();
	Map *map_ptr = &maps[id];
	if(map_ptr->created == 1)
	{
		map_ptr->created = 0;
		state->map_count--;
	}
	else
	{
		printf("memory.c: TRIED TO DELETE NON-EXISTING MAP\n");
	}
}

Map* mapGet(int id)
{
	if(id==-1)
		return NULL;
	PersistentGameState *state = memoryGetPersistentGameState();
	Map *maps = memoryGetMaps();
	Map *map_ptr = &maps[id];
	if(map_ptr->created == 1)
	{
		return map_ptr;
	}
	printf("memory.c: TRIED TO GET NON-EXISTING MAP\n");
	return NULL;
}

Map* mapGetCurrent()
{
	PersistentGameState *state = memoryGetPersistentGameState();
	return mapGet(state->current_level);
}

int mapGetRandomTile()
{
	return rand() % 10;
}

int mapCheckCollision(Transform *transform, Map* map_ptr)
{
	int collision = 0;
	Vector2f point;
	for(point.x = -transform->collider.w / 2; 
		point.x <= transform->collider.w / 2; 
		point.x += transform->collider.w / 4)
	{
		for(point.y = -transform->collider.h / 2; 
			point.y <= transform->collider.h / 2; 
			point.y += transform->collider.h / 4)
		{ 
			Vector2f position =  
			{
				transform->position.x + point.x,
				transform->position.y + point.y
			};
			
			Vector2i grid = mapCoordsToGrid(position); 

			if(map_ptr->data[grid.y][grid.x] == TILE_WALL)
			{
				collision = 1;
			}	
		}
	}	
	return collision;
}

void mapRandomize()
{
	Map *map_ptr = mapGetCurrent();
	srand(time(NULL));
	for(int i = 0; i < map_ptr->size.y; i++)
	{
		for(int j = 0; j < map_ptr->size.x; j++)
		{
			map_ptr->data[i][j] = mapGetRandomTile();
		}
	}
}

void mapLoadTest()
{
	int index = mapCreate();
	Map *map_ptr = mapGet(index);
	PersistentGameState *state = memoryGetPersistentGameState();
	Transform *transform;

	map_ptr->tile_len = 64.0;
	map_ptr->size.x = 20;
	map_ptr->size.y = 20;

	for(int i = 0; i < map_ptr->size.x; i++)
	{
		map_ptr->data[i][0] = TILE_WALL;
		map_ptr->data[i][map_ptr->size.x-1] = TILE_WALL;
	}

	for(int j = 0; j < map_ptr->size.y; j++)
	{
		map_ptr->data[0][j] = TILE_WALL;
		map_ptr->data[map_ptr->size.y-1][j] = TILE_WALL;
	}
				
	for(int i = 4; i < 9; i++)
	{
		map_ptr->data[i][5] = TILE_WALL;
	}
}

Vector2i mapCoordsToGrid(Vector2f coords)
{
	float tile_size = mapGetCurrent()->tile_len;
	Vector2i grid = 
	{
		round((coords.x - 0.5 * tile_size)/tile_size),
		round((coords.y - 0.5 * tile_size)/tile_size)
	};
	return grid;
}

Vector2f mapGridToCoords(Vector2i grid)
{
	float tile_size = mapGetCurrent()->tile_len;
	Vector2f coords = 
	{
		grid.x * tile_size + 0.5 * tile_size,
		grid.y * tile_size + 0.5 * tile_size	
	};
	return coords;
}

void mapCacheToTexture()
{
	Map* maps = memoryGetMaps();
	GraphicsState *sdl_state = memoryGetGraphicsState();
	PersistentGameState *state = memoryGetPersistentGameState();
	TransientGameState *ui_state = memoryGetTransientGameState();
	Map *map_ptr = &maps[state->current_level];

	sdl_state->map_elements[state->current_level] = 
		SDL_CreateTexture(sdl_state->renderer,
						  SDL_PIXELFORMAT_RGBA32, 
						  SDL_TEXTUREACCESS_TARGET, 
						  map_ptr->size.x * map_ptr->tile_len, 
						  map_ptr->size.y * map_ptr->tile_len);

	SDL_SetRenderTarget( sdl_state->renderer, 
						 sdl_state->map_elements[state->current_level]);	

	for(int i = 0; i < map_ptr->size.h; i++)
	{
		for(int j = 0; j < map_ptr->size.w; j++)
		{
			SDL_Rect tile;

			tile.x = j * map_ptr->tile_len;
			tile.y = i * map_ptr->tile_len;
			tile.w = map_ptr->tile_len;
			tile.h = map_ptr->tile_len ;

			printf("map.c: tile height: %d, tile length: %f\n", tile.h, map_ptr->tile_len);
			SDL_Rect source;
			
			source = animationGetRect(0, 0, 5);

			SDL_RenderCopy( sdl_state->renderer, sdl_state->textures[5], 
							&source, &tile);
		}
	}
}

void mapDrawCurrent()
{
	Map* maps = memoryGetMaps();
	GraphicsState *sdl_state = memoryGetGraphicsState();
	PersistentGameState *state = memoryGetPersistentGameState();
	TransientGameState *ui_state = memoryGetTransientGameState();
	Map *map_ptr = mapGetCurrent();
	
	//Bottom viewport
	if(map_ptr->map_changed || 
	   sdl_state->map_elements[state->current_level] == NULL)
	{
		map_ptr->map_changed = 0;
		mapCacheToTexture();
	}

	SDL_Rect map_rect;
 
	map_rect.w = round(state->camera_transform.render.w);
	map_rect.h = round(state->camera_transform.render.h);

	map_rect.x = round(state->camera_transform.position.x
			  		   - state->camera_transform.render.w/2);

	map_rect.y = round(state->camera_transform.position.y
					   - state->camera_transform.render.h/2);

	SDL_SetRenderTarget( sdl_state->renderer,  NULL);

	SDL_RenderCopy( sdl_state->renderer, 
					sdl_state->map_elements[state->current_level], 
					&map_rect, NULL);
	
}
