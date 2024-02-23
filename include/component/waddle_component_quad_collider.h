#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <SDL.h>
#include "entity/waddle_entity.h"

typedef void (*waddle_on_collision_enter_callback)(entity* src_entity, entity* dest_entity);

typedef enum {
	STATIC,
	DYNAMIC
} waddle_collider_type;

typedef struct {
	waddle_collider_type type;
	SDL_FRect rect;
	SDL_FPoint delta;
	SDL_FPoint scale;
	waddle_on_collision_enter_callback on_collision_enter_callback;
} waddle_quad_collider;

#ifdef __cplusplus
}
#endif
