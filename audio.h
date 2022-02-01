/*******************************************************************************
* 
* FILENAME : audio.h
*
* DESCRIPTION : Header file containing audio structs and function headers
*
* AUTHOR : filipang           
* 
* START DATE :    29/12/2021
*
*******************************************************************************/

#define AUDIO_SAMPLES_PER_SECOND 44100

typedef struct AudioState
{
	Mix_Chunk *chunks[20];
} AudioState;

int audioInitialize();
void audioOffsetChunk(Mix_Chunk *chunk, int ms);
void audioPlaySound(int id, int loops);
