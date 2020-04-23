#ifndef _SOUND_H
#define _SOUND_H
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

typedef struct sound_s
{
//sound_dev_t device;
	channel_t channels[MAX_SFX_CHANNELS];
	
} sound_t;

sound_t* sound_create()
{
	sound_t* sound = calloc(1,sizeof(sound_t));
	return sound;
}

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
music_t* music_create()
{
	music_t* music = calloc(1, sizeof(music_t));
	return music;
}
bool sound_halt(sound_t* sound)
{
	if(!sound)
		return false;
	free(sound);
	return true;
}
bool music_halt(music_t* music)
{
	if(!music)
		return false;
	free(music);
	return true;
}

bool sound_update(sound_t* sound)
{
	return true;
};
bool music_update(music_t* music)
{
	return true;
};
#endif
