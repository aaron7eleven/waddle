#pragma once
#include <SDL.h>
typedef struct {
	float speed;
	float velocity;
} quad_controller;

void update(float delta_time, const Uint8* key_state, void* data);

void update_quad_controller(float delta_time, const Uint8* key_state);