#pragma once

#ifdef WADDLE_EXPORTS
#define WADDLE_API __declspec(dllexport)
#else
#define WADDLE_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include "SDL_mixer.h"

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

WADDLE_API int waddle_load_audio(waddle_audio_player* audio_player);
WADDLE_API void play(waddle_audio_player* audio_player);
int volume_clamp(int volume);

#ifdef __cplusplus
}
#endif