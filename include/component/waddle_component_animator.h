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
#include "component/waddle_component_animation.h"

typedef struct {
	waddle_animation* animations[16];
	int animation_count;
	int max_animation_count;

	waddle_animation* current_animation;
	SDL_Point current_frame;
	int current_frame_count;
	float frame_timer;
} waddle_animator;

#ifdef __cplusplus
}
#endif