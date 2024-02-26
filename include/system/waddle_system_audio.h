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
#include "component/waddle_component_audio_player.h"

WADDLE_API void play(waddle_audio_player* audio_player);
int volume_clamp(int volume);

#ifdef __cplusplus
}
#endif