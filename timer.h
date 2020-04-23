#ifndef _TIMER_H
#define _TIMER_H

#include <GLFW/glfw3.h>

typedef struct timer_system_s
{
	double t_now;
	double t_last;
	double dt;
	double fps;
	uint64_t tick_now;
	uint64_t tick_last;
	uint64_t freq;
} timer_system_t;

timer_system_t* timer_create()
{
	timer_system_t* timer = calloc(1, sizeof(timer_system_t));
	timer->t_now = glfwGetTime();
	timer->t_last = 0;
	timer->dt = 0;
	timer->fps = 0;
	timer->tick_now = glfwGetTimerValue();
	timer->tick_last = 0;
	timer->freq = glfwGetTimerFrequency();
	return timer;
}

double timer_update(timer_system_t* timer)
{
	timer->t_last = timer->t_now;
	timer->t_now = glfwGetTime();
	timer->dt = timer->t_now - timer->t_last;
	timer->fps = 1.0 / timer->dt;
	timer->tick_last = timer->tick_now;
	timer->tick_now = glfwGetTimerValue();
	timer->freq = glfwGetTimerFrequency();
	return timer->dt;
}

bool timer_halt(timer_system_t* timer)
{
	if(!timer)
		return false;
	free(timer);
	return true;
}
#endif
