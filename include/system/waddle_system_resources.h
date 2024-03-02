#pragma once

#ifdef WADDLE_EXPORTS
#define WADDLE_API __declspec(dllexport)
#else
#define WADDLE_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include <SDL.h>
#include "component/waddle_component_audio_player.h"
#include "component/waddle_component_ui_text.h"

WADDLE_API int waddle_load_assets();
WADDLE_API int waddle_load_audio(waddle_audio_player* audio_player);
WADDLE_API int waddle_load_font(waddle_ui_text* ui_text);
WADDLE_API int waddle_load_texture(SDL_Renderer* renderer, const char* file, SDL_Texture** texture);

#ifdef __cplusplus
}
#endif