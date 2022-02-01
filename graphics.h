/*******************************************************************************
* 
* FILENAME : graphics.h
*
* DESCRIPTION : Header file containing graphics structs and function headers
*
* AUTHOR : filipang           
* 
* START DATE :    5/11/2021
*
*******************************************************************************/

#include "kiss_sdl/kiss_sdl.h"

#ifndef GRAPHICS_H
#define GRAPHICS_H

#define CLIP_GROUND			  5
#define CLIP_WALL   		  7
#define CLIP_PLAYER 		  7 
#define CLIP_ENEMY			  4
#define CLIP_ACTIVE_RANDOMIZE 10
#define CLIP_ACTIVE_UP		  9
#define CLIP_ACTIVE_DOWN	  8

#define ANIMATION_FPS 15

typedef struct GraphicsClip
{
	int texture_id;
	int clip_count;
	int active_clip;
	SDL_Rect base_clip;
} GraphicsClip;

#define GRAPHICS_MAX_MAP_COUNT 200
#define GRAPHICS_TEXTURE_SHEET_COUNT 20
typedef struct GraphicsState
{
	Vector2i screen_size;
	SDL_Surface* screenSurface;
	SDL_Renderer* renderer;
	SDL_Texture* textures[GRAPHICS_TEXTURE_SHEET_COUNT];
	SDL_Texture* map_elements[GRAPHICS_MAX_MAP_COUNT]; //Main dungeon branch	
	SDL_Texture* debug_frame_buffer;
	SDL_Event event;
	double game_scale;
	double ui_scale;
	kiss_array objects;
	kiss_window window;
	kiss_label label;
	kiss_label kill_count_label;
	kiss_button button_save;
	kiss_button button_load;
	kiss_window  item_box;
	kiss_label 	 item_description;
} GraphicsState;

void graphicsLoadTextureBMP(char *path, int slot, GraphicsState *sdl_state);
void graphicsLoadTexturePNG(char *path, int slot, GraphicsState *sdl_state);
int  graphicsInitialize();
void graphicsClose(GraphicsState *sdl_state);
int  graphicsGetClipFromTile(int tile);
void graphicsUpdateCreatureAnimation(Creature *creature_ptr);
int  graphicsActiveGetClip(int type);
void graphicsDrawEntity(Entity *entity_ptr);
void graphicsScreenDrawEntity(Entity *entity_ptr, Vector2f position);
void graphicsProcessFrame(); 
void graphicsDebugDrawTransform(Transform *transform);
void graphicsDebugDrawFrameBuffer();

#endif
