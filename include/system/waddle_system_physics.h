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
#include "entity/waddle_entity.h"

WADDLE_API void update_physics_system(entity* entities[], int entity_count);
WADDLE_API void update_colliders(entity* entities[], int entity_count);
WADDLE_API void update_quad_collider(entity* entity);
WADDLE_API void check_collisions(entity* entities[], int entity_count);
WADDLE_API void collision_response(entity* a, entity* b);
WADDLE_API int check_collision(entity* a, entity* b);

#ifdef __cplusplus
}
#endif