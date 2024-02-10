#pragma once
#include <SDL.h>
#include "waddle_entity.h"
typedef struct {
	float speed;
	SDL_FPoint velocity;
} quad_controller;

void update_quad_controller(float delta_time, const Uint8* key_state, entity* entity);