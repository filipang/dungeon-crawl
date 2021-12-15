/*******************************************************************************
* 
* FILENAME : map.h
*
* DESCRIPTION : Header file containing map structs and function headers
*
* AUTHOR : filipang           
* 
* START DATE :    11/11/2021
*
*******************************************************************************/

#ifndef MAP_H
#define MAP_H

#define TILE_GRASS 0
#define TILE_WALL  1

typedef struct Map
{
	int created;
	int id;

	Vector2i size;
	double tile_len;
	unsigned char data[30][30];		
	int map_changed;
} Map;

int  mapCreate();
void mapDelete(int id);
Map* mapGet(int id);

Map* mapGetCurrent();
int  mapGetRandomTile();
int  mapCheckCollision(Transform *transform, Map* map_ptr);

void mapRandomize();
void mapLoadTest();

Vector2i mapCoordsToGrid(Vector2f coords);
Vector2f mapGridToCoords(Vector2i grid);

void mapCacheToTexture();
void mapDrawCurrent();

#endif
