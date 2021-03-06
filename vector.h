#ifndef _VECTOR_H
#define _VECTOR_H

#include "system_types.h"

typedef struct vec4f
{
	union {
		vec4 versor;
		struct {
			float x;
			float y;
			float z;
			float w;
		};
	};
} vec4f;

typedef vec4f quat4f;
typedef vec4f vec3f;

#endif
