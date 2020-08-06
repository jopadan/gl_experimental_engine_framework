#ifndef _COLOR_H
#define _COLOR_H

#include "system_types.h"

typedef struct color4f_s
{
	union {
		GLclampf v[4];
		vec4 versor;
		struct {
			GLclampf red;
			GLclampf green;
			GLclampf blue;
			GLclampf alpha;
		};
		struct {
			GLclampf r;
			GLclampf g;
			GLclampf b;
			GLclampf a;
		};
	};
} color4f;

typedef color4f color_t;

void color_zero(color_t color);
void color_one(color_t color);
void color_clamp(color_t color);
color_t color_create(float red, float green, float blue, float alpha);

#endif
