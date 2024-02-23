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

WADDLE_API float distance_squared(float x1, float y1, float x2, float y2);
WADDLE_API float magnitude(float x, float y);
// WADDLE_API float magnitude(float x1, float y1, float x2, float y2);
WADDLE_API void normalize(SDL_FPoint* point);

#ifdef __cplusplus
}
#endif