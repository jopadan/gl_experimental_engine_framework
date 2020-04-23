#ifndef _INPUT_H
#define _INPUT_H

#include "system_types.h"

#define MAX_JOYSTICKS (GLFW_JOYSTICK_LAST + 1)
#define MAX_GAMEPAD_BUTTONS (GLFW_GAMEPAD_BUTTON_LAST + 1)
#define MAX_GAMEPAD_AXIS (GLFW_GAMEPAD_AXIS_LAST + 1)
#define MAX_MOUSE_BUTTONS (GLFW_MOUSE_BUTTON_LAST + 1)

typedef struct joystick_s
{
	int id;
	int present;
	const char_t* name;
	const char_t* guid;
	
	int num_axes;
	const float* axes;

	int num_buttons;
	const uint8_t* buttons;

	int num_hats;
	const uint8_t* hats;

	bool gamepad;
	const char_t* gamepad_name;
	GLFWgamepadstate* gamepad_state;

	void* userpointer;
	GLFWjoystickfun callback;
} joystick_t;

typedef struct keyboard_s
{
} keyboard_t;
typedef struct mouse_s
{
} mouse_t;

typedef struct input_s
{
	int num_keyboards;
	keyboard_t* keyboards;

	int num_mice;
	mouse_t* mice;

	int num_joysticks;
	joystick_t joysticks[MAX_JOYSTICKS];
} input_t;

input_t* input_create()
{
	input_t* input = calloc(1, sizeof(input_t));
	return input;
}
bool input_halt(input_t* input)
{
	if(!input)
		return false;
	free(input);
	return true;
}

bool joystick_update(joystick_t* joystick)
{
	joystick->present = glfwJoystickPresent(joystick->id);
	if(joystick->present == GLFW_FALSE)
		return false;

	joystick->name = glfwGetJoystickName(joystick->id);
	joystick->guid = glfwGetJoystickGUID(joystick->id);

	// check if joystick is a gamepad
	joystick->gamepad = glfwJoystickIsGamepad(joystick->id);
	if(joystick->gamepad == GLFW_TRUE)
	{
		joystick->gamepad_name = glfwGetGamepadName(joystick->id);
		if(glfwGetGamepadState(joystick->id, joystick->gamepad_state) != GLFW_TRUE)
		{
			return false;
		}

	}

	// get joystick state
	joystick->hats = glfwGetJoystickHats(joystick->id, &joystick->num_hats);
	joystick->buttons = glfwGetJoystickButtons(joystick->id, &joystick->num_buttons);
	joystick->axes = glfwGetJoystickAxes(joystick->id, &joystick->num_axes);
	return true;
}

bool input_update(input_t* input)
{
	// update each joystick
	joystick_t* joy = input->joysticks;
	joystick_t* joy_last = &input->joysticks[input->num_joysticks - 1];

	do {
		if(!joystick_update(joy++))
			return false;
	} while(joy_last  - joy >= 0);

	return true;
}

#endif
