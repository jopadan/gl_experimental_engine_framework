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

input_t* input_create();
bool input_halt(input_t* input);
bool joystick_update(joystick_t* joystick);
bool input_update(input_t* input);

#endif
