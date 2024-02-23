#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <SDL.h>

typedef struct {
	SDL_FPoint size;
	SDL_Color color;
} waddle_quad_renderer;

#ifdef __cplusplus
}
#endif