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

typedef struct {
	SDL_FPoint position;
	SDL_FPoint rotation;
	SDL_FPoint scale;
} waddle_transform;

#ifdef __cplusplus
}
#endif