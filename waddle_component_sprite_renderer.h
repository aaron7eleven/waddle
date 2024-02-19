#pragma once
#include <SDL.h>

typedef struct {
	SDL_FPoint size;
	SDL_Color color;
	const char* file;
	SDL_Texture* texture;
} waddle_sprite_renderer;

int waddle_load_sprite(SDL_Renderer* renderer, waddle_sprite_renderer* sprite_renderer);

