#include "color.h"

void color_zero(color_t color)
{
	glm_vec4_zero(color.versor);
}

void color_one(color_t color)
{
	glm_vec4_one(color.versor);
}

void color_clamp(color_t color)
{
	glm_vec4_clamp(color.versor, 0.0f, 1.0f);
}

color_t color_create(float red, float green, float blue, float alpha)
{
	color_t color;
	color.versor[0] = red;
	color.versor[1] = green;
	color.versor[2] = blue;
	color.versor[3] = alpha;

	glm_vec4_clamp(color.versor, 0.0f, 1.0f);

	return color;
}

