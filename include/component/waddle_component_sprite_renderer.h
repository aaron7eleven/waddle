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
	SDL_FPoint size;
	SDL_Color color;
	const char* file;
	SDL_Texture* texture;
	int render_order; // TBD
} waddle_sprite_renderer;

WADDLE_API int waddle_load_sprite(SDL_Renderer* renderer, waddle_sprite_renderer* sprite_renderer);

#ifdef __cplusplus
}
#endif