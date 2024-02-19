#pragma once
#include <SDL.h>
#include "waddle_entity.h"
#include "waddle_collider_type.h"

typedef void (*waddle_on_collision_enter_callback)(entity* src_entity, entity* dest_entity);

typedef struct {
	waddle_collider_type type;
	SDL_FRect rect;
	SDL_FPoint delta;
	SDL_FPoint scale;
	waddle_on_collision_enter_callback on_collision_enter_callback;
} waddle_quad_collider;