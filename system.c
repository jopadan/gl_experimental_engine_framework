#include "system.h"

system_t* system_create()
{
	system_t* system = calloc(1, sizeof(system_t));
	if(!(system->files = files_create()))
	{
		free(system);
		return NULL;
	}
	if(!(system->input = input_create()))
	{
		files_halt(system->files);
		free(system);
		return NULL;
	}
	if(!(system->video = video_create(DEFAULT_WIDTH, DEFAULT_HEIGHT, "test")))
	{
		input_halt(system->input);
		files_halt(system->files);
		free(system);
		return NULL;
	}

	if (!(system->sound = sound_create()))
	{
		video_halt(system->video);
		input_halt(system->input);
		files_halt(system->files);
		free(system);
		return NULL;
	}

	if (!(system->music = music_create()))
	{
		sound_halt(system->sound);
		video_halt(system->video);
		input_halt(system->input);
		files_halt(system->files);
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
		   !video_halt(system->video) ||
		   !input_halt(system->input) ||
		   !files_halt(system->files))
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
	if(!files_update(system->files) ||
	   !input_update(system->input) ||
	   !video_update(system->video) ||
	   !sound_update(system->sound) ||
	   !music_update(system->music)
	 )
	 	return false;

	return true;
}

