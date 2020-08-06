#ifndef _FONT_H
#define _FONT_H

#include "system_types.h"
#include "timer.h"
#include "filesystem.h"
#include "mesh.h"

#define FONT_SZ 16
#define SCALE_FACTOR 8

typedef struct dtx_font font_t;
typedef struct dtx_box font_box_t;

typedef struct text_s
{
	string_t data;
	font_t* font;
	font_box_t dim;
	color_t color;
	GLfloat scale;
} text_t;

typedef struct font_system_s
{
	size_t num_fonts;
	size_t num_font_files;
	size_t num_texts;

	font_t** fonts;
	char** font_files;
	text_t** texts;

	struct dtx_font* current_font;
	GLFWwindow* current_window;
	GLFWmonitor* current_monitor;
	GLFWvidmode* current_mode;
	time_system_t* current_timer;
} font_system_t;

bool font_system_add_font(font_system_t* font_system, char* font_filename);
bool font_system_add_text(font_system_t* font_system, text_t* text);
bool text_destroy(text_t* text);
font_system_t* font_system_create(time_system_t* timer);
bool font_system_destroy(font_system_t* font_system);
bool font_system_halt(font_system_t* font_system);
bool font_system_update(font_system_t* font_system);

#endif
