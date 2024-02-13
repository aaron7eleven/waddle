#pragma once
#include <SDL.h>
#include "waddle_entity.h"
void update_physics_system(entity* entities[], int entity_count);
void update_colliders(entity* entities[], int entity_count);
void update_quad_collider(entity* entity);
void check_collisions(entity* entities[], int entity_count);
void collision_response(entity* a, entity* b);
int check_collision(entity* a, entity* b);