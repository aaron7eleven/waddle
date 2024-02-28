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
	const char* name;
	SDL_Point start_frame; // Top left position of frame in texture
	SDL_Point end_frame; // Top left position of frame in texture
	int number_of_frames;
	SDL_Point frame_diff;
	float time_between_frames;
} waddle_animation;

#ifdef __cplusplus
}
#endif