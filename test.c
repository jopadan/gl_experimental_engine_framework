#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

#include "vector.h"

int main(int argc, char** argv)
{
	vec4f a = { 1.0f, 0.5f, 0.0f, 1.0f };
	vec4f b = { 0.0f, 1.0f, 0.0f, 1.0f };
	vec4f c = { 0.0f, 0.0f, 0.0f, 1.0f };
	glm_vec3_cross(a.simd, b.simd, c.simd);
	printf("%f %f %f %f\n", c.simd[0], c.simd[1], c.simd[2], c.simd[3]);
	exit(EXIT_SUCCESS);
	return 0;
}
