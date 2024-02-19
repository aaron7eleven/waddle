#include "waddle_component_sprite_renderer.h"

int waddle_load_sprite(SDL_Renderer* renderer, sprite_renderer* sprite_renderer) {
	sprite_renderer->texture = IMG_LoadTexture(renderer, sprite_renderer->file);
	if (sprite_renderer->texture == NULL) {
		printf("ERROR: Failed to load asset: %s", sprite_renderer->file);
		return 1;
	}
	return 0;
}