#ifndef _SCENE_H
#define _SCENE_H

#include "vector.h"

typedef struct camera_s
{
	vec3 pos;
	vec3 up;
	vec3 look_at;
	versor orientation;
	float fov;
} camera_t;

bool camera_destroy(camera_t* camera)
{
	if(!camera)
		return false;
	free(camera);
	camera = NULL;
	return true; 
}

typedef struct geometry_s
{
	size_t num_vertices;
	vec4* vertices;
	vec4* texcoords;
	vec4* vertex_normals;
	vec4* face_normals;
	vec4* faces;

//	octree_t* octree;
//	sphere_t bounding_sphere;
//	quad_t bounding_box;
} geometry_t;

bool geometry_destroy(geometry_t* geometry)
{
	if(!geometry)
		return false;
	
	if(geometry->vertices)
		free(geometry->vertices);
	if(geometry->texcoords)
		free(geometry->texcoords);
	if(geometry->vertex_normals)
		free(geometry->vertex_normals);
	if(geometry->face_normals)
		free(geometry->face_normals);
	if(geometry->faces)
		free(geometry->faces);
	if(geometry = NULL)
		free(geometry);
	return true;
}
typedef struct scene_s
{
	char* name;
	size_t num_cameras;
	camera_t** cameras;
	size_t num_geometries;
	geometry_t** geometries;
} scene_t;

scene_t* scene_create(char* name)
{
	scene_t* scene = calloc(1, sizeof(scene_t));
	if(!scene)
		return NULL;

	scene->name = strdup(name);

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

	if(scene->geometries)
	{
		for(size_t i =0; i < scene->num_geometries; i++)
		{
			geometry_destroy(scene->geometries[i]);
		}
		free(scene->geometries);
		scene->geometries = NULL;
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	return true;
}

void scene_test_screen()
{
	glBegin(GL_QUADS);
	glColor3f(0.5f, 0.0f, 0.4f);
	glVertex2f(-0.5f, -0.5f);
	glColor3f(0.5f, 0.2f, 0.4f);
	glVertex2f(-0.5f, 0.5f);
	glColor3f(0.1f, 0.5f, 0.1f);
	glVertex2f(0.5f, 0.5f);
	glColor3f(0.3f, 0.2f, 0.5f);
	glVertex2f(0.5f, -0.5f);
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
