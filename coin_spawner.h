#pragma once
#include "waddle.h"

typedef struct {
	float time_to_spawn;
	float spawn_timer;
} coin_spawner;

void update_coin_spawner(waddle* waddle);
int spawn_coin(waddle* waddle);
void coin_on_collision_enter_callback(entity* src_entity, entity* dest_entity);