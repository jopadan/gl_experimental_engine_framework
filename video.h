#ifndef _VIDEO_H
#define _VIDEO_H

#include "globals.h"
#include "font.h"
#include <GLFW/glfw3.h>

bool video_destroy(video_t* video)
{
	if(!video)
		return false;

	if(!scene_destroy(video->current_scene))
			return false;

	for(size_t i = 0 ; i < video->num_scenes; i++)
	{
		if(!video->scenes[i])
			continue;
		if(!scene_destroy(video->scenes[i]))
			return false;
	}


	if(video->num_monitors)
	{
		free(video->num_modes);
		free(video->modes);
		free(video->mode);
	}

	if(video->primary_window)
	{
		glfwDestroyWindow(video->primary_window);
		video->primary_window = NULL;
	}

	free(video);
	return true;
}

bool video_clear(video_t* video)
{
	if(!video)
		return false;

	GLFWwindow* window = glfwGetCurrentContext();
	if(!window)
	{
		window = video->primary_window;
		glfwMakeContextCurrent(window);
		if(!window) return false;
	}
	fprintf(stderr,"current_scene = %p\n", video->current_scene);

	if(!scene_setup(video->current_scene))
		return false;
	if(!scene_clear(video->current_scene))
		return false;

	return true;
}

bool video_flip(video_t* video)
{
	if(!video)
		return false;
	glfwSwapBuffers(video->primary_window);
	glfwPollEvents();
	return true;
}

bool video_halt(video_t* video)
{
	if(!video)
		return false;

	return video_destroy(video);
}
bool video_update(system_t* system)
{
	GLFWwindow* window = glfwGetCurrentContext();
	if(!window)
	{
		window = system->video->primary_window;
		glfwMakeContextCurrent(window);
		if(!window) return false;
	}

	if(!scene_setup(system->video->current_scene))
		return false;
	if(!scene_draw(system->video->current_scene))
		return false;

	if(system->font)
		if(!font_system_update(system))
			return false;

	if(!video_flip(system->video))
		return false;

	return true;
}


video_t* video_create(int width, int height, const char* title)
{
	video_t* video = calloc(1,sizeof(video_t));

	// get connected monitors
	video->monitors = glfwGetMonitors(&video->num_monitors);
	if(!video->monitors)
	{
		video_destroy(video);
		return NULL;
	}
	video->num_modes = calloc(video->num_monitors, sizeof(int));
	video->modes = calloc(video->num_monitors, sizeof(GLFWvidmode*));
	video->mode = calloc(video->num_monitors, sizeof(GLFWvidmode*));

	// for every monitor
	for(int i = 0; i < video->num_monitors; i++)
	{
		// get available video modes
		video->modes[i] = glfwGetVideoModes(video->monitors[i], &video->num_modes[i]);
		video->mode[i] = glfwGetVideoMode(video->monitors[i]);
	}

	// get primary monitor
	video->primary.monitor = glfwGetPrimaryMonitor();
	if(!video->primary.monitor)
	{
		video_destroy(video);
		return NULL;
	}

	// get primary monitor available video modes
	video->primary.modes = glfwGetVideoModes(video->primary.monitor, &video->primary.num_modes);
	if(!video->primary.modes)
	{
		video_destroy(video);
		return NULL;
	}

	// get primary monitor current video mode
	video->primary.mode = glfwGetVideoMode(video->primary.monitor);
	if(!video->primary.mode)
	{
		video_destroy(video);
		return NULL;
	}

	fprintf(stderr, "Using monitor: %s\n", glfwGetMonitorName(video->primary.monitor));
	// create window
	video->primary_window = glfwCreateWindow(
			width ? width : video->primary.mode->width, 
			height ? height : video->primary.mode->height, 
			title, NULL, NULL);
	if(!video->primary_window)
	{
		video_destroy(video);
		return NULL;
	}

	glfwMakeContextCurrent(video->primary_window);

	color_zero(video->current_scene->clear_color);

	video->current_scene = scene_create("test");

	video_clear(video);
	video_flip(video);

	return video;
}

#endif
