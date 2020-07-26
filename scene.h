#ifndef _SCENE_H
#define _SCENE_H

#include "vector.h"
#include "mesh.h"


typedef struct scene_s
{
	char* name;
	size_t num_cameras;
	camera_t** cameras;
	size_t num_meshes;
	mesh_t** meshes;
	color_t clear_color;
} scene_t;

scene_t* scene_create(char* name)
{
	scene_t* scene = calloc(1, sizeof(scene_t));
	if(!scene)
		return NULL;

	scene->name = strdup(name);
	color_zero(scene->clear_color);
	return scene;
}

bool scene_destroy(scene_t* scene)
{
	if(!scene)
		return false;
	if(scene->cameras)
	{
		for(size_t i =0; i < scene->num_cameras; i++)
		{
			camera_destroy(scene->cameras[i]);
		}
		free(scene->cameras);
		scene->cameras = NULL;
	}

	if(scene->meshes)
	{
		for(size_t i =0; i < scene->num_meshes; i++)
		{
			mesh_destroy(scene->meshes[i]);
		}
		free(scene->meshes);
		scene->meshes = NULL;
	}

	free(scene);
	scene = NULL;
	return true;
}

bool scene_clear(scene_t* scene)
{
	if(!scene)
		return false;
	glMatrixMode(GL_PROJECTION_MATRIX);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW_MATRIX);
	glLoadIdentity();
	glClearColor(scene->clear_color.red, scene->clear_color.green, scene->clear_color.blue, scene->clear_color.alpha);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	return true;
}

void scene_test_screen()
{
	glFrontFace(GL_CCW);

	/* front face */
	glBegin(GL_QUADS);
	glColor3f(0.5f, 0.0f, 0.4f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glColor3f(0.5f, 0.2f, 0.4f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glColor3f(0.1f, 0.5f, 0.1f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glColor3f(0.3f, 0.2f, 0.5f);
	/* bottom right */
	glVertex3f(0.5f, -0.5f, -0.5f);
	glEnd();
}

bool scene_setup(scene_t* scene)
{
	if(!scene)
		return false;

	if(!scene_clear(scene))
		return false;


	return true;
}

bool scene_draw(scene_t* scene)
{
	if(!scene)
		return false;

	if(!scene_clear(scene))
		return false;

	scene_test_screen();
	return true;
}
#endif
