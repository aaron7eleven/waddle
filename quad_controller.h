#pragma once
#include <SDL.h>
#include "waddle.h"
typedef struct {
	float speed;
} quad_controller;

//void update_quad_controller(float delta_time, const Uint8* key_state, entity* entity);
void update_quad_controller(waddle* waddle);