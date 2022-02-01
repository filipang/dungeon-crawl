/*******************************************************************************
* 
* FILENAME : audio.c
*
* DESCRIPTION : Source file containing audio functions
*
* AUTHOR : filipang           
* 
* START DATE :    29/12/2021
*
*******************************************************************************/

int audioInitialize()
{
	AudioState *audio_state = memoryGetAudioState();
	if(SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        return -1;
	}
	//Initialize SDL_mixer
	if( Mix_OpenAudio( AUDIO_SAMPLES_PER_SECOND, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
	{
		printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
		return -1;
	}

	//Load sound effects
    audio_state->chunks[0] = Mix_LoadWAV("test_woosh.wav");
	audio_state->chunks[1] = Mix_LoadWAV("music.wav");
	audio_state->chunks[2] = Mix_LoadWAV("apple.wav");
	
    if( audio_state->chunks[0] == NULL )
    {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		return -1;
    }

	audioOffsetChunk(audio_state->chunks[0], 1000);
	audioPlaySound(1, -1);
	return 1;
}

void audioOffsetChunk(Mix_Chunk *chunk, int ms)
{
	int skipped_samples = (int)((double)ms * 44.1);
	chunk->abuf += skipped_samples;
	chunk->alen -= skipped_samples;
}

void audioPlaySound(int id, int loops)
{
	AudioState *audio_state = memoryGetAudioState();
	Mix_PlayChannel( -1, audio_state->chunks[id], loops);	
}
