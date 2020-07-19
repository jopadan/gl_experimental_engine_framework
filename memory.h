#ifndef _MEMORY_H
#define _MEMORY_H

#include "system_types.h"
#include "filesystem.h"
#include "texture.h"


typedef struct pool_s
{
	texture_t* textures;
	font_t* fonts;
	model_t* models;
	level_t* levels;
} pool_t;


typedef struct heap_s
{
} heap_t;

typedef struct stack_s
{
} stack_t;

typedef struct memory_s
{
	texture_t* texture;
	zone_t* zone;
	pool_t* pool;
	heap_t* heap;
	stack_t* stack;
} memory_t;

bool memory_create();
bool memory_resize(size_t size);
bool memory_halt();
bool memory_destroy();
bool memory_load_texture(memory_t* memory, const char* filename);
bool memory_load_font(memory_t* memory, const char* font);
#endif
