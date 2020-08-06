#include "mesh.h"


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
