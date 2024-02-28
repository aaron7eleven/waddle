#pragma once

#ifdef WADDLE_EXPORTS
#define WADDLE_API __declspec(dllexport)
#else
#define WADDLE_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include "SDL.h"
#include "SDL_mixer.h"
#include "component/waddle_component_sprite_renderer.h"
#include "component/waddle_component_audio_player.h"
#include "component/waddle_component_ui_text.h"
#include "component/waddle_component_animated_sprite_renderer.h"

WADDLE_API int waddle_load_sprite(SDL_Renderer* renderer, waddle_sprite_renderer* sprite_renderer);
WADDLE_API int waddle_load_audio(waddle_audio_player* audio_player);
WADDLE_API int waddle_load_font(waddle_ui_text* ui_text);
WADDLE_API int waddle_load_animated_sprite(SDL_Renderer* renderer, waddle_animated_sprite_renderer* animated_sprite_renderer);

#ifdef __cplusplus
}
#endif