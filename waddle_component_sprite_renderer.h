#pragma once
#include <SDL.h>

typedef struct {
	SDL_FPoint size;
	SDL_Color color;
	const char* file;
	SDL_Texture* texture;
} sprite_renderer;

