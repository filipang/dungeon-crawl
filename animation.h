/*******************************************************************************
* 
* FILENAME : animation.h
*
* DESCRIPTION : Header file containing animation function headers and structs
*
* AUTHOR : filipang           
* 
* START DATE :    25/12/2021 (Merry Christmas)
*
*******************************************************************************/

typedef struct Animation {
	int frame_count;
	int clip_row;			
	int clip_col;		
	int texture_id;
} Animation;

SDL_Rect animationGetRect(int row, int col, int texture_id);

