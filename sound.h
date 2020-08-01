#ifndef _SOUND_H
#define _SOUND_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "system_types.h"

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"


sound_miniaudio_t* sound_miniaudio_create()
{
	sound_miniaudio_t* ma = calloc(1, sizeof(sound_miniaudio_t));
	ma_result result = -1;

	if(ma_context_init(NULL, 0, NULL, &ma->context) != MA_SUCCESS) {
		free(ma);
		return NULL;
	}

	ma_context_get_devices(&ma->context, &ma->playback_info, &ma->playback_count, &ma->capture_info, &ma->capture_count);
	if(result != MA_SUCCESS) {
		free(ma);
		return NULL;
	}

	for(ma_uint32 i = 0; i < ma->playback_count; ++i)
	{
		printf("    %u: %s\n", i, ma->playback_info[i].name);
	}

	for(ma_uint32 i = 0; i < ma->capture_count; ++i)
	{
		printf("    %u: %s\n", i, ma->capture_info[i].name);
	}
}

bool sound_miniaudio_destroy(sound_miniaudio_t* ma)
{
	if(!ma)
		return false;
	if(ma->playback_count > 0)
	{
		for(ma_uint32 i = 0; i < ma->playback_count; ++i)
		{
			
		}
	}
	free(ma);
	return true;
}

sound_t* sound_create()
{
	sound_t* sound = calloc(1,sizeof(sound_t));
	return sound;
}

music_t* music_create()
{
	music_t* music = calloc(1, sizeof(music_t));
	return music;
}
bool sound_halt(sound_t* sound)
{
	if(!sound)
		return false;
	free(sound);
	return true;
}
bool music_halt(music_t* music)
{
	if(!music)
		return false;
	free(music);
	return true;
}

bool sound_update(sound_t* sound)
{
	return true;
};
bool music_update(music_t* music)
{
	return true;
};
#endif
