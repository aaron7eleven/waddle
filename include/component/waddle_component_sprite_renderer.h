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
	SDL_Point size;
	SDL_Color color;
	const char* file;
	SDL_Texture* texture;
	int render_order; // TBD
} waddle_sprite_renderer;


#ifdef __cplusplus
}
#endif