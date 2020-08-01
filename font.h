#ifndef _FONT_H
#define _FONT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <wchar.h>
#include "color.h"
#include "vector.h"
#include "video.h"
#include <npth.h>
#include <drawtext.h>

#define FONT_SZ 24
#define SCALE_FACTOR 8


bool font_system_add_font(font_system_t* font_system, char* font_filename)
{
	if(!font_system)
		return false;
	if(!font_filename)
		return false;

	if(font_system->font_files && font_system->num_font_files > 0)
		font_system->font_files = reallocarray(font_system->font_files, ++font_system->num_font_files, sizeof(font_t*));
	else
		font_system->font_files = calloc(++font_system->num_font_files, sizeof(font_t*));

	if(font_system->fonts && font_system->num_fonts > 0)
		font_system->fonts = reallocarray(font_system->fonts, ++font_system->num_fonts, sizeof(font_t*));
	else
		font_system->fonts = calloc(++font_system->num_fonts, sizeof(font_t*));

	if(!font_system->fonts || !font_system->font_files)
	{
		font_system->num_font_files = 0;
		font_system->num_fonts = 0;
		return false;
	}

	font_system->font_files[font_system->num_font_files - 1] = strdup(font_filename);
	font_system->fonts[font_system->num_fonts - 1] = dtx_open_font(font_filename, 0);

	if(!font_system->fonts[font_system->num_fonts - 1])
	{
		--font_system->num_fonts;
		return false;
	}
	if(!font_system->font_files[font_system->num_font_files - 1])
	{
		--font_system->num_font_files;
		return false;
	}

	dtx_prepare_range(font_system->fonts[font_system->num_fonts - 1], FONT_SZ, 0, 256);
	return true;
}

bool font_system_add_text(font_system_t* font_system, text_t* text)
{
	if(!font_system || !text)
		return false;
	if(font_system->texts && font_system->num_texts > 0)
		font_system->texts = reallocarray(font_system->texts, ++font_system->num_texts, sizeof(text_t*));
	else
		font_system->texts = calloc(++font_system->num_texts, sizeof(text_t*));

	if(!font_system->texts)
	{
		font_system->num_texts = 0;
		return false;
	}

	font_system->texts[font_system->num_texts - 1] = text;

	return true;
}
bool text_destroy(text_t* text)
{
	if(!text)
		return false;
	if(text->data)
		free(text->data);
	return true;
}

font_system_t* font_system_create(video_t* video, time_system_t* timer)
{
	font_system_t* font_system = calloc(1,sizeof(font_system_t));
	if(!font_system_add_font(font_system, "serif.ttf"))
	{
		free(font_system);
		return NULL;
	}
	text_t* text = calloc(1, sizeof(text_t));
	text->data = calloc(16, sizeof(char));
	text->dim.x = 0.0f;
	text->dim.y = 0.0f;
	text->dim.width=video->primary.mode->width;
	text->dim.height=video->primary.mode->height;
	glm_vec4_one(text->color.versor);
	text->scale = 1.0f;

	if(!font_system_add_text(font_system, text))
	{
		free(text);
		return NULL;
	}

	font_system->current_font = font_system->fonts[font_system->num_fonts - 1];

	dtx_use_font(font_system->current_font, FONT_SZ * SCALE_FACTOR);

	return font_system;
}

bool font_system_destroy(font_system_t* font_system)
{
	if(!font_system)
		return false;

	for(size_t i = 0; i < font_system->num_fonts; i++)
	{
		if(font_system->fonts[i])
			dtx_close_font(font_system->fonts[i]);
	}
	free(font_system->fonts);
	for(size_t i = 0; i < font_system->num_texts; i++)
	{
		if(font_system->texts[i])
		{
			free(font_system->texts[i]->data);
			free(font_system->texts[i]);
		}
	}
	free(font_system->texts);
	free(font_system);
	return true;
}

bool font_system_halt(font_system_t* font_system)
{
	return font_system_destroy(font_system);
}

bool font_system_update(system_t* system)
{
	sprintf(system->font->texts[0]->data, "FPS: %.2f fps", system->timer->fps);

	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
	glTranslatef(-200, 150, 0);
	glColor3f(1, 1, 1);
	/* XXX call dtx_string to draw utf-8 text.
	 * any transformations and the current color apply
	 */
	dtx_string(system->font->texts[0]->data);
	glPopMatrix();
	//font_box_t pos = system->font->texts[0]->dim;
	return true;
}

#endif