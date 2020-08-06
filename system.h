#ifndef _SYSTEM_H
#define _SYSTEM_H

#include "system_types.h"
#include "filesystem.h"
#include "timer.h"
#include "input.h"
#include "video.h"
#include "font.h"
#include "sound.h"
//#include "music.h"

#define DEFAULT_WIDTH 1024
#define DEFAULT_HEIGHT 768
#define DEFAULT_BPP 32
#define DEFAULT_FREQ 44100
#define DEFAULT_RATE 16
#define DEFAULT_AUDIODEV 0

typedef struct system_s
{
	bool running;
	filesystem_t* files;
	input_t* input;
	video_t* video;
	sound_t* sound;
	music_t* music;
} system_t;

system_t* system_create();
void error_callback(int error_code, const char* description);
system_t* system_init();
bool system_halt(system_t* system);
bool system_update(system_t* system);

#endif
