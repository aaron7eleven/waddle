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
	SDL_Point texture_size;
	SDL_Rect clip_rect;
	SDL_Color color;
	const char* file;
	SDL_Texture* texture;
	int render_order; // TBD
} waddle_clip_sprite_renderer;


#ifdef __cplusplus
}
#endif