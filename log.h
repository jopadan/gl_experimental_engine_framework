#ifndef _LOG_H
#define _LOG_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>


#define LOG_BUFFER_LENGTH 2048
enum log_secion_e { LOG_TIMER, LOG_FILES, LOG_INPUT, LOG_VIDEO, LOG_SOUND, LOG_MUSIC, LOG_SECTION_END };

typedef struct log_s
{
	FILE* stream;
	int8_t* buffer[LOG_SECTION_END][LOG_BUFFER_LENGTH];
} log_t;

log_t* log_create()
{
	log_t* log = calloc(1,sizeof(log_t));
	log->stream = stderr;
	return log;
}

bool log_update(log_t* log)
{
	
}

bool log_flush(log_t* log)
{
}

bool log_queue(log_t* log, int section, char* msg)
{
	
}

bool log_destroy(log_t* log)
{
	if(log == NULL)
		return false;
	if(log->stream)
		fclose(log->stream);
	
	free(log);
	return true;
}
#endif
