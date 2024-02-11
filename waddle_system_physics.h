#pragma once
#include <SDL.h>
#include "waddle_entity.h"
void update_physics_system(entity* entities[], int entity_count);
void update_colliders(entity* entities[], int entity_count);
void check_collisions(entity* entities[], int entity_count);
int check_collision(entity* a, entity* b);