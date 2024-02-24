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
#include "entity/waddle_entity.h"

WADDLE_API void update_render_system(SDL_Renderer* renderer, entity* entity);
//WADDLE_API void (SDL_Renderer* renderer, entity* entity);

#ifdef __cplusplus
}
#endif