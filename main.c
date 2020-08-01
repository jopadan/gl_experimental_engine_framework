#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <errno.h>
#include <error.h>
#include <GLFW/glfw3.h>
#include "globals.h"


void window_close(GLFWwindow* window)
{
	fprintf(stderr, "%s\n", "fooo");
	return;
}

void key_press(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if(key == GLFW_KEY_ESCAPE)
		main_system->running = false;

	fprintf(stderr, "key: %d scancode: %d action: %d mods: %d\n", key, scancode, action, mods);
}

bool main_loop()
{
	main_system->running = true;
	while(main_system->running)
	{
		if(!system_update(main_system))
			return false;
	}
	return true;
}

int main(int argc, char** argv)
{
	int exit_status = EXIT_SUCCESS;
	if(!(main_system = system_init()))
		exit(EXIT_FAILURE);

	//glfwSetWindowCloseCallback(main_system->video->primary_window, window_close);
	glfwSetKeyCallback(main_system->video->primary_window, key_press);

	if(!main_loop())
	{
		system_halt(main_system);
		exit(EXIT_FAILURE);
	}

	exit(system_halt(main_system) ? EXIT_SUCCESS : EXIT_FAILURE);
	return 0;
}
