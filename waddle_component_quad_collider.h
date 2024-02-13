#pragma once
#include <SDL.h>
#include "waddle_colliders.h"

typedef struct {
	SDL_FRect rect;
	collider_type type;
	SDL_FPoint delta;
} quad_collider;