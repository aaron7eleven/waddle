#pragma once

#ifdef WADDLE_EXPORTS
#define WADDLE_API __declspec(dllexport)
#else
#define WADDLE_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include <SDL_mixer.h>

typedef enum {
	WAV,
	MP3,
	OGG
} waddle_audio_file_type;

typedef struct {
	waddle_audio_file_type type;
	const char* path;
	Mix_Chunk* clip;
	int volume;
} waddle_audio_player;

#ifdef __cplusplus
}
#endif