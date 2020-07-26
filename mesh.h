#ifndef _MESH_H
#define _MESH_H

#include "mesh.h"

typedef struct camera_s
{
	vec3 pos;
	vec3 up;
	vec3 look_at;
	versor orientation;
	float fov;
} camera_t;

typedef struct primitive_type_s
{
	GLenum face;
	GLenum mode;
} primitive_type_t;

typedef struct geometry_s
{
	primitive_type_t primitive_type;
	size_t num_vertices;
//	octree_t* octree;
//	sphere_t bounding_sphere;
//	cube_t bounding_box;
} geometry_t;

typedef struct cube_s
{
	versor orient;
	vec4 pos;
	GLfloat radius;
	vec4 vertices[16];
	vec4 faces[6];
} cube_t;

typedef struct sphere_s
{
	versor orient;
	GLfloat redius;
} sphere_t;
typedef struct mesh_s
{
	primitive_type_t primitive_type;
	cube_t bounding_box;
	sphere_t bounding_sphere;

	size_t num_vertices;
	size_t num_faces;
	size_t num_indices;

	vec4* vertices;
	vec4* texcoords;
	vec4* vertex_normals;
	vec4* face_normals;
	vec4* faces;
	vec4* edge_flags;
	vec4* indices;
	vec4* color;
} mesh_t;

bool camera_destroy(camera_t* camera)
{
	if(!camera)
		return false;
	free(camera);
	camera = NULL;
	return true; 
}

mesh_t* mesh_create(camera_t* orientation, primitive_type_t* type)
{
	mesh_t* geom = calloc(1,sizeof(mesh_t*));
	
	return geom;
}

bool mesh_destroy(mesh_t* geometry)
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
	if(geometry->edge_flags)
		free(geometry->edge_flags);
	if(geometry->indices)
		free(geometry->indices);
	if(geometry->color)
		free(geometry->color);
	if(geometry = NULL)
		free(geometry);
	return true;
}

cube_t* cube_create(GLfloat radius)
{
	cube_t* cube = calloc(1, sizeof(cube_t));
	glm_vec4_zero(cube->pos);
	cube->radius = radius;
	return cube;
}
#endif
