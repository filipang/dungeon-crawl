/*******************************************************************************
* 
* FILENAME : animation.c
*
* DESCRIPTION : Source file containing animation functions
*
* AUTHOR : filipang           
* 
* START DATE :    25/12/2021 (Merry Christmas)
*
*******************************************************************************/

SDL_Rect animationGetRect(int row, int col, int texture_id)
{
	//TODO(filip): HANDLE CASE FOR ANIMATION CLIPS GOING OUT OF BOUNDS
	SDL_Rect rect;
	if(texture_id == 0)
	{
		rect.x = col * 64;
		rect.y = row * 64;
		rect.w = 32;
		rect.h = 50;
	}
	else if(texture_id == 2 || texture_id == 1)
	{
		rect.y = row * 64;
		rect.x = col * 64;
		rect.w = 64;
		rect.h = 64;
	}
	else if(texture_id == 3)
	{
		rect.y = (col/4) * 220;
		rect.x = (col%4) * 220;
		rect.w = 220;
		rect.h = 220;
	}
	else if(texture_id == 4)
	{
		rect.y = row * 32;
		rect.x = col * 32;
		rect.w = 32;
		rect.h = 32;
	}
	else if(texture_id == 5)
	{
		if(col == 0)
		{
			rect.y = 20;
			rect.x = 1;
			rect.w = 126;
			rect.h = 80;
		}
		else if(col == 1)
		{
			rect.y = 0;
			rect.x = 1;
			rect.w = 126;
			rect.h = 100;
		}
	}
	else if(texture_id == 6)
	{
		rect.y = 21;
		rect.x = 21;
		rect.w = 52; 
		rect.h = 53;
	}
	return rect;
}

