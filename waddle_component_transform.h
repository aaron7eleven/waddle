#pragma once
#include <SDL.h>

typedef struct {
	SDL_FPoint position;
	SDL_FPoint rotation;
	SDL_FPoint scale;
} transform;