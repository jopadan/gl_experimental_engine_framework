#ifndef _MESH_H
#define _MESH_H

#include "system_types.h"
#include "vector.h"
#include "color.h"

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

bool camera_destroy(camera_t* camera);
mesh_t* mesh_create(camera_t* orientation, primitive_type_t* type);
bool mesh_destroy(mesh_t* geometry);
cube_t* cube_create(GLfloat radius);

#endif
