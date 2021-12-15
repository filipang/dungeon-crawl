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

void uiButtonEvent(kiss_button *button, SDL_Event *e, int *draw, int *quit);
void uiProcessEvent();

void uiDrawFPS();
void uiDrawLoadSave();

void uiDraw();
void uiDrawInventory();
void uiProcessInventory();

void uiDrawItemInfoBox();
