#ifndef _VIDEO_H
#define _VIDEO_H

#include "system_types.h"
#include "scene.h"
#include "font.h"
#include "timer.h"

#define DEFAULT_WIDTH 1024
#define DEFAULT_HEIGHT 768

typedef struct monitor_s
{
	GLFWmonitor* monitor;
	int num_modes;
	const GLFWvidmode* modes;
	const GLFWvidmode* mode;
} monitor_t;


typedef struct video_s
{
	int num_monitors;

	GLFWmonitor** monitors;
	int* num_modes;
	const GLFWvidmode** modes;
	const GLFWvidmode** mode;

	monitor_t primary;
	GLFWwindow* primary_window;

	size_t num_scenes;
	scene_t** scenes;
 	scene_t* current_scene;

	time_system_t* timer;
	font_system_t* font;
} video_t;


bool video_destroy(video_t* video);
bool video_clear(video_t* video);
bool video_flip(video_t* video);
bool video_halt(video_t* video);
bool video_update(video_t* video);
video_t* video_create(int width, int height, const char* title);

#endif
