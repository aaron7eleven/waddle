#pragma once
#include <SDL.h>
#include "waddle_collider_type.h"

typedef struct {
	SDL_FRect rect;
	waddle_collider_type type;
	SDL_FPoint delta;
} quad_collider;