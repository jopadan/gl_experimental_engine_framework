#include "filesystem.h"

filesystem_t* files_create()
{
	filesystem_t* files = calloc(0,sizeof(filesystem_t));

	return files;
}

bool files_halt(filesystem_t* files)
{
	if(!files)
		return false;

	return true;
}

bool files_update(filesystem_t* files)
{
	if(!files)
		return false;
	return true;
}
