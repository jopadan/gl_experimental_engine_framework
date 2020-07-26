#ifndef _SYSTEM_H
#define _SYSTEM_H

#include <GLFW/glfw3.h>

#include "timer.h"
#include "input.h"
#include "video.h"
#include "sound.h"
//#include "music.h"
#include "filesystem.h"

#define DEFAULT_WIDTH 1024
#define DEFAULT_HEIGHT 768
#define DEFAULT_BPP 32
#define DEFAULT_FREQ 44100
#define DEFAULT_RATE 16
#define DEFAULT_AUDIODEV 0

typedef struct system_s
{
	bool running;
	time_system_t* timer;
	filesystem_t* files;
	input_t* input;
	video_t* video;
	sound_t* sound;
	music_t* music;
} system_t;

system_t* system_create()
{
	system_t* system = calloc(1, sizeof(system_t));
	system->timer = time_system_create();
	system->files = files_create();
	system->input = input_create();
	system->video = video_create(DEFAULT_WIDTH, DEFAULT_HEIGHT, "test");
	system->sound = sound_create();
	system->music = music_create();
	return system;
}

void error_callback(int error_code, const char* description)
{
	fprintf(stderr, "%s\n", description);
}

system_t* system_init()
{
	glfwSetErrorCallback(error_callback);
	if(glfwInit() != GLFW_TRUE)
		return NULL;
	return system_create();
}

bool system_halt(system_t* system)
{
	if(system)
	{
		if(!music_halt(system->music) || 
		   !sound_halt(system->sound) ||
		   !video_halt(system->video) ||
		   !input_halt(system->input) ||
		   !files_halt(system->files) ||
		   !time_system_halt(system->timer))
			return false;
		system->running = false;
		free(system);
	}
	glfwTerminate();
	return true;
}

bool system_update(system_t* system)
{
	glfwPollEvents();
	if(!time_system_update(system->timer) ||
	   !files_update(system->files) ||
	   !input_update(system->input) ||
	   !video_update(system->video) ||
	   !sound_update(system->sound) ||
	   !music_update(system->music)
	 )
	   	return false;

	return true;
}

#endif
