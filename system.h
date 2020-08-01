#ifndef _SYSTEM_H
#define _SYSTEM_H

#include <GLFW/glfw3.h>

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

system_t* system_create()
{
	system_t* system = calloc(1, sizeof(system_t));
	if(!(system->timer = time_system_create()))
	{
		free(system);
		return NULL;
	}
	if(!(system->files = files_create()))
	{
		time_system_halt(system->timer);
		free(system);
		return NULL;
	}
	if(!(system->input = input_create()))
	{
		files_halt(system->files);
		time_system_halt(system->timer);
		free(system);
		return NULL;
	}
	if(!(system->video = video_create(DEFAULT_WIDTH, DEFAULT_HEIGHT, "test")))
	{
		input_halt(system->input);
		files_halt(system->files);
		time_system_halt(system->timer);
		free(system);
		return NULL;
	}
	if (!(system->font = font_system_create(system->video, system->timer)))
	{
		video_halt(system->video);
		input_halt(system->input);
		files_halt(system->files);
		time_system_halt(system->timer);
		free(system);
		return NULL;
	}

	if (!(system->sound = sound_create()))
	{
		font_system_halt(system->font);
		video_halt(system->video);
		input_halt(system->input);
		files_halt(system->files);
		time_system_halt(system->timer);
		free(system);
		return NULL;
	}

	if (!(system->music = music_create()))
	{
		sound_halt(system->sound);
		font_system_halt(system->font);
		video_halt(system->video);
		input_halt(system->input);
		files_halt(system->files);
		time_system_halt(system->timer);
		free(system);
		return NULL;
	}

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
		   !font_system_halt(system->font)   ||
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
	   !video_update(system) ||
	   !font_system_update(system) ||
	   !sound_update(system->sound) ||
	   !music_update(system->music)
	 )
	 	return false;

	return true;
}

#endif
