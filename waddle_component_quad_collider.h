#pragma once
#include <SDL.h>
#include "waddle_collider_type.h"

typedef struct {
	waddle_collider_type type;
	SDL_FRect rect;
	SDL_FPoint delta;
	SDL_FPoint scale;
} quad_collider;