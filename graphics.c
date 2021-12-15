/*******************************************************************************
* 
* FILENAME : graphics.c
*
* DESCRIPTION : Source file containing graphics functions
*
* AUTHOR : filipang           
* 
* START DATE :    5/11/2021
*
*******************************************************************************/

//Screen dimension constants
const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 500;

void graphicsLoadTextureBMP(char *path, int slot, GraphicsState *sdl_state)
{
	//Load image at specified path
	SDL_Surface* loadedSurface = SDL_LoadBMP( path );
	
	//Create texture from surface pixels*/
	sdl_state->textures[slot] = 
		SDL_CreateTextureFromSurface(sdl_state->renderer, loadedSurface);

	//Check for error
	if( sdl_state->textures[slot] == NULL )
	{
		printf( "Unable to create texture! SDL Error: %s\n", 
				SDL_GetError() );
	}

	//Get rid of old loaded surface
	SDL_FreeSurface( loadedSurface );
}

void graphicsLoadTexturePNG(char *path, int slot, GraphicsState *sdl_state)
{
	IMG_Init( IMG_INIT_PNG );
	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path );
	
	//Create texture from surface pixels*/
	sdl_state->textures[slot] = 
		SDL_CreateTextureFromSurface(sdl_state->renderer, loadedSurface);

	//Check for error
	if( sdl_state->textures[slot] == NULL )
	{
		printf( "Unable to create texture! SDL Error: %s\n", 
				SDL_GetError() );
	}

	//Get rid of old loaded surface
	SDL_FreeSurface( loadedSurface );
}

void graphicsClose(GraphicsState *sdl_state)
{
	PersistentGameState *state = memoryGetPersistentGameState();
    //Deallocate surface
    SDL_DestroyTexture(sdl_state->textures[0]);
    SDL_DestroyTexture(sdl_state->textures[1]);

	for(int i; i < state->map_count; i++)
	{
		SDL_DestroyTexture(sdl_state->map_elements[i]);
	}
    //Destroy window
    //SDL_DestroyWindow(sdl_state->window);
    //sdl_state->window = NULL;
	printf("graphics.c: SDL exitted: %s\n", SDL_GetError());
	kiss_clean(&sdl_state->objects);
    //Quit SDL subsystems
    //SDL_Quit();
}

void graphicsCreateClipRects(GraphicsState *sdl_state)
{
	for(int i = 0; i < 12; i++)
	{
		for(int j = 0; j < 12; j++)
		{
			sdl_state->clips[i][j].x = 64 * j;
			sdl_state->clips[i][j].y = 64 * i;
			sdl_state->clips[i][j].w = 32;
			sdl_state->clips[i][j].h = 50;
		}
	}
}

int graphicsInitialize()
{
	GraphicsState *sdl_state = memoryGetGraphicsState();
	kiss_array_new(&sdl_state->objects);
	//renderer = 
	sdl_state->renderer = 
		kiss_init("Dungeon Crawl", &sdl_state->objects, 
				  SCREEN_WIDTH, SCREEN_HEIGHT);

	graphicsLoadTextureBMP("tex.bmp", 1, sdl_state);
	graphicsLoadTexturePNG("tex.png", 0, sdl_state);
	graphicsCreateClipRects(sdl_state);

	char message[KISS_MAX_LENGTH];
	int draw, quit;
	quit = 0;
	draw = 1;

	if (!sdl_state->renderer) return 0;

	sdl_state->screen_size.w = kiss_screen_width;
	sdl_state->screen_size.h = kiss_screen_height;
	kiss_window_new(&sdl_state->window, NULL, 0, 0, 0, 
					kiss_screen_width,
					kiss_screen_height);

	strcpy(message, "Frame counter");

	kiss_label_new(&sdl_state->label, &sdl_state->window, message,
				    sdl_state->window.rect.w - 40 - strlen(message) *
					kiss_textfont.advance / 2,
					20);

	sdl_state->label.textcolor.r = 255;

	kiss_button_new(&sdl_state->button_save, &sdl_state->window, "Save",
					sdl_state->window.rect.w - 70 -  kiss_normal.w / 2, 
					50);

	kiss_button_new(&sdl_state->button_load, &sdl_state->window, "Load",
					sdl_state->window.rect.w - 70 -  kiss_normal.w / 2, 
					80);

	sdl_state->window.visible = 1;
	sdl_state->debug_frame_buffer = 
			  SDL_CreateTexture(sdl_state->renderer,
								SDL_PIXELFORMAT_RGBA32, 
								SDL_TEXTUREACCESS_TARGET, 
								sdl_state->screen_size.w, 
								sdl_state->screen_size.h);

	kiss_window_new(&sdl_state->item_box, NULL, 0, 0, 0,
					150, 150);

	SDL_Color color = {115, 140, 115, 255};
	sdl_state->item_box.bg = color;

	kiss_label_new(&sdl_state->item_description, &sdl_state->item_box, "",
				   0, 0);
	sdl_state->item_box.visible = 0;

	return 1;
}

int graphicsGetClipFromTile(int tile)
{
	int clip;
	switch(tile)
	{
		case TILE_GRASS:
			clip = CLIP_GROUND;
			break;
		case TILE_WALL:
			clip = CLIP_WALL;
		   	break;
		default: 
			clip = CLIP_GROUND;
			break;
	}
	return clip;
}

SDL_FRect graphicsApplyCamera(SDL_FRect rect)
{
	PersistentGameState *state = memoryGetPersistentGameState();
	Transform *camera_transform = &state->camera_transform;

	rect.x += -camera_transform->position.x +
	   		  camera_transform->render.w/2;

	rect.y += -camera_transform->position.y + 
	   		  camera_transform->render.h/2;

	return rect;
}

SDL_FRect graphicsTransformToScreen(Transform *transform)
{

	SDL_FRect rect;

	rect.w = transform->render.w;

	rect.h = transform->render.h;

	rect.x = transform->position.x - 
			 rect.w/2;

	rect.y = transform->position.y - 
			 rect.h/2;
	return rect;
}

void graphicsDrawTransform(Transform *transform)
{			
	graphicsDebugDrawTransform(transform);

	GraphicsState *sdl_state = memoryGetGraphicsState();
	PersistentGameState *state = memoryGetPersistentGameState();
	TransientGameState *ui_state = memoryGetTransientGameState();


	SDL_SetRenderTarget( sdl_state->renderer,  NULL);

	SDL_FRect dest = graphicsTransformToScreen(transform);

	dest = graphicsApplyCamera(dest);

	SDL_RenderCopyF(sdl_state->renderer, 
					sdl_state->textures[0], 
					&sdl_state->clips[transform->clip_row]
									 [transform->clip_col], 
					&dest);
}

void graphicsScreenDrawTransform(Transform *transform, Vector2f position)
{			
	GraphicsState *sdl_state = memoryGetGraphicsState();
	PersistentGameState *state = memoryGetPersistentGameState();
	TransientGameState *ui_state = memoryGetTransientGameState();


	SDL_SetRenderTarget( sdl_state->renderer,  NULL);

	SDL_FRect dest;
	dest.x = position.x;
	dest.y = position.y;
	dest.w = transform->render.w;
	dest.h = transform->render.h;

	SDL_RenderCopyF(sdl_state->renderer, 
					sdl_state->textures[0], 
					&sdl_state->clips[transform->clip_row]
									 [transform->clip_col], 
					&dest);
}

int activeGetClip(int type)
{
	switch(type)
	{
		case ACTIVE_RANDOMIZE_MAP:
			return CLIP_ACTIVE_RANDOMIZE;
		case ACTIVE_STAIRS_UP:
			return CLIP_ACTIVE_UP;
		case ACTIVE_STAIRS_DOWN:
			return CLIP_ACTIVE_DOWN;
		default:
			return CLIP_WALL;
	};
}

void graphicsDebugDrawRect(float x, float y, float w, float h)
{
	GraphicsState *sdl_state = memoryGetGraphicsState();

	SDL_RenderDrawLineF(sdl_state->renderer, 
						x, y, x + w, y);	

	SDL_RenderDrawLineF(sdl_state->renderer, 
						x, y, x, y + h);	

	SDL_RenderDrawLineF(sdl_state->renderer, 
						x + w, y + h, x, y + h);

	SDL_RenderDrawLineF(sdl_state->renderer, 
						x + w, y + h, x + w, y);
}

void graphicsDebugDrawTransform(Transform *transform)
{
	GraphicsState *sdl_state = memoryGetGraphicsState();
	SDL_SetRenderTarget(sdl_state->renderer, 
					 	sdl_state->debug_frame_buffer);	
	Vector2f position = transformGetScreenRenderCorner(transform);

    SDL_SetRenderDrawColor(sdl_state->renderer, 255, 0, 255, 255);		

	graphicsDebugDrawRect(position.x, position.y, 
						  transform->render.w, transform->render.h);

	position = transformGetScreenColliderCorner(transform);

    SDL_SetRenderDrawColor(sdl_state->renderer, 0, 255, 0, 255);		

	graphicsDebugDrawRect(position.x, position.y, 
						  transform->collider.w, transform->collider.h);

	/*
	position = transformGetScreenTriggerCorner(transform);

    SDL_SetRenderDrawColor(sdl_state->renderer, 255, 255, 0, 255);		

	graphicsDebugDrawRect(position.x, position.y, 
						  transform->trigger.w, transform->trigger.h);
	*/

	// So we don't draw to the debug buffer by accident
	SDL_SetRenderTarget(sdl_state->renderer, 
					 	NULL);	
}

void graphicsDrawCircle(SDL_Renderer * renderer, 
						int centreX, 
						int centreY, 
						int radius)
{
   const int32_t diameter = (radius * 2);

   int x = (radius - 1);
   int y = 0;
   int tx = 1;
   int ty = 1;
   int error = (tx - diameter);

   while (x >= y)
   {
      //  Each of the following renders an octant of the circle
      SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
      SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
      SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
      SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
      SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
      SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
      SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
      SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

      if (error <= 0)
      {
         ++y;
         error += ty;
         ty += 2;
      }

      if (error > 0)
      {
         --x;
         tx += 2;
         error += (tx - diameter);
      }
   }
}

void graphicsDebugDrawFrameBuffer()
{
	GraphicsState *sdl_state = memoryGetGraphicsState();

	SDL_SetRenderDrawBlendMode(sdl_state->renderer, SDL_BLENDMODE_BLEND);
	
	SDL_SetTextureBlendMode(sdl_state->debug_frame_buffer, SDL_BLENDMODE_BLEND);

	SDL_SetRenderTarget(sdl_state->renderer, NULL);	
	
	SDL_RenderCopy(sdl_state->renderer,
				   sdl_state->debug_frame_buffer,
				   NULL, NULL);
}

void graphicsDebugClearFrameBuffer()
{	
	GraphicsState *sdl_state = memoryGetGraphicsState();

	SDL_SetRenderTarget(sdl_state->renderer, sdl_state->debug_frame_buffer);	

    SDL_SetRenderDrawColor(sdl_state->renderer, 0, 0, 0, 0);

	SDL_RenderClear(sdl_state->renderer);
	
	SDL_SetRenderTarget(sdl_state->renderer, NULL);	
}

void graphicsProcessFrame() 
{
	GraphicsState *sdl_state = memoryGetGraphicsState();
	TransientGameState *ui_state = memoryGetTransientGameState();

	//Clear screen
	SDL_RenderClear( sdl_state->renderer );
	
	mapDrawCurrent();

	activeDrawList();

	creatureDrawList();

	itemDrawList();

	uiDraw();

	uiDrawItemInfoBox();

	uiDrawInventory();

	graphicsDebugDrawFrameBuffer();
	graphicsDebugClearFrameBuffer();

	//Update screen
	SDL_RenderPresent( sdl_state->renderer );
}
