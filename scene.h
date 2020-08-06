#ifndef _SCENE_H
#define _SCENE_H

#include "system_types.h"
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

scene_t* scene_create(char* name);
bool scene_destroy(scene_t* scene);
bool scene_clear(scene_t* scene);
void scene_test_screen();
bool scene_setup(scene_t* scene);
bool scene_draw(scene_t* scene);

#endif
