#ifndef _GLOBALS_H
#define _GLOBALS_H
#include "system_types.h"

#include <GLFW/glfw3.h>
#include <drawtext.h>
#include "miniaudio.h"

#define MAX_JOYSTICKS (GLFW_JOYSTICK_LAST + 1)
#define MAX_GAMEPAD_BUTTONS (GLFW_GAMEPAD_BUTTON_LAST + 1)
#define MAX_GAMEPAD_AXIS (GLFW_GAMEPAD_AXIS_LAST + 1)
#define MAX_MOUSE_BUTTONS (GLFW_MOUSE_BUTTON_LAST + 1)
#define DEFAULT_WIDTH 1024
#define DEFAULT_HEIGHT 768
#define DEFAULT_BPP 32
#define DEFAULT_FREQ 44100
#define DEFAULT_RATE 16
#define DEFAULT_AUDIODEV 0

#define MAX_SFX_CHANNELS 128
#define MAX_MIDI_CHANNELS 512
#define MAX_MUSIC_TRACKS 1024
typedef struct channel_s
{
	uint8_t* data;
} channel_t;

typedef struct sound_output_device_s
{
	uint8_t* data;
} sound_output_device_t;

typedef struct sound_miniaudio_s
{
	ma_decoder_config decoder_config;
	ma_context context;

	ma_device_info* playback_info;
	ma_device_config* playback_config;
	ma_uint32 playback_count;

	ma_device_info* capture_info;
	ma_device_config* capture_config;
	ma_uint32 capture_count;
	
} sound_miniaudio_t;

typedef struct time_system_s
{
	double t_now;
	double t_last;
	double dt;
	double fps;
	uint64_t tick_now;
	uint64_t tick_last;
	uint64_t freq;
} time_system_t;

typedef struct dtx_font font_t;
typedef struct dtx_box font_box_t;

typedef struct text_s
{
	string_t data;
	font_t* font;
	font_box_t dim;
	color_t color;
	GLfloat scale;
} text_t;


typedef struct monitor_s
{
	GLFWmonitor* monitor;
	int num_modes;
	const GLFWvidmode* modes;
	const GLFWvidmode* mode;
} monitor_t;

typedef struct camera_s
{
	vec3 pos;
	vec3 up;
	vec3 look_at;
	versor orientation;
	float fov;
} camera_t;

typedef struct primitive_type_s
{
	GLenum face;
	GLenum mode;
} primitive_type_t;

typedef struct geometry_s
{
	primitive_type_t primitive_type;
	size_t num_vertices;
//	octree_t* octree;
//	sphere_t bounding_sphere;
//	cube_t bounding_box;
} geometry_t;

typedef struct cube_s
{
	versor orient;
	vec4 pos;
	GLfloat radius;
	vec4 vertices[16];
	vec4 faces[6];
} cube_t;

typedef struct sphere_s
{
	versor orient;
	GLfloat redius;
} sphere_t;
typedef struct mesh_s
{
	primitive_type_t primitive_type;
	cube_t bounding_box;
	sphere_t bounding_sphere;

	size_t num_vertices;
	size_t num_faces;
	size_t num_indices;

	vec4* vertices;
	vec4* texcoords;
	vec4* vertex_normals;
	vec4* face_normals;
	vec4* faces;
	vec4* edge_flags;
	vec4* indices;
	vec4* color;
} mesh_t;
typedef struct scene_s
{
	char* name;
	size_t num_cameras;
	camera_t** cameras;
	size_t num_meshes;
	mesh_t** meshes;
	color_t clear_color;
} scene_t;

typedef struct font_system_s
{
	size_t num_fonts;
	size_t num_font_files;
	size_t num_texts;

	font_t** fonts;
	char** font_files;
	text_t** texts;

	struct dtx_font* current_font;
} font_system_t;

typedef struct video_s
{
	int num_monitors;

	GLFWmonitor** monitors;
	int* num_modes;
	const GLFWvidmode** modes;
	const GLFWvidmode** mode;

	monitor_t primary;
	GLFWwindow* primary_window;

	size_t num_scenes;
	scene_t** scenes;
	scene_t* current_scene;
} video_t;

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

typedef struct sound_s
{

//sound_dev_t device;
	channel_t channels[MAX_SFX_CHANNELS];
	
} sound_t;

typedef struct streamed_music_track_s
{
	string_t name;
	uint32_t id;
	bool playing;
	bool looped;
	int16_t channel;
	string_t filename;
	uint8_t* data;
} streamed_music_track_t;

typedef struct streamed_music_s
{
	sound_output_device_t* output;
	streamed_music_track_t* tracks;
} streamed_music_t;

typedef struct tracked_music_module_s
{
	string_t name;
	uint32_t id;
	string_t comment;
	string_t filename;
	uint8_t* data;
} tracked_music_module_t;

typedef struct tracked_music_s
{
	sound_output_device_t output;
	tracked_music_module_t* module;
} tracked_music_t;

typedef struct midi_music_track_s
{
	string_t name;
	uint32_t id;
	string_t comment;
	string_t filename;
	uint8_t* data;
} midi_music_track_t;

typedef struct midi_music_s
{
	sound_output_device_t output;
	midi_music_track_t* track;
} midi_music_t;

typedef struct disc_music_track_s
{
	string_t name;
	uint32_t id;
	string_t comment;
	string_t filename;
	uint8_t* data;
} disc_music_track_t;

typedef struct disc_music_s
{
	sound_output_device_t output;
	disc_music_track_t* track;
} disc_music_t;

typedef struct music_s
{
		streamed_music_t streamed;
		tracked_music_t tracked;
		midi_music_t midi;
		disc_music_t disc;
} music_t;

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


typedef struct system_s
{
	bool running;
	time_system_t* timer;
	filesystem_t* files;
	input_t* input;
	video_t* video;
	font_system_t* font;
	sound_t* sound;
	music_t* music;
} system_t;

system_t* main_system = NULL;

#include "time.h"
#include "filesystem.h"
#include "sound.h"
#include "scene.h"
#include "video.h"
#include "font.h"
#include "system.h"

#endif
