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
#include <SDL_ttf.h>

typedef struct {
	// setup
	const char* file;
	int point_size;
	TTF_Font* font;
	
	// usage
	const char* text;
	SDL_FPoint rect;
	SDL_Color color;
} waddle_ui_text;

#ifdef __cplusplus
}
#endif