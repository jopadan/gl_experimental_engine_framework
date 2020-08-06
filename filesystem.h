#ifndef _FILESYSTEM_H
#define _FILESYSTEM_H

#include "system_types.h"

typedef struct file_s
{
	char* name;
	FILE* file;
	size_t length;
	uint8_t* data;
} file_t;


typedef struct filesystem_s
{
	size_t num_files;
	size_t length;
	file_t* files;
} filesystem_t;

filesystem_t* files_create();
bool files_halt(filesystem_t* files);
bool files_update(filesystem_t* files);

#endif
