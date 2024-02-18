#pragma once
#include "waddle.h"
#include "custom_component_type.h"

typedef struct {
	float time_to_spawn;
	float spawn_timer;
	int coins_spawned;
} coin_spawner;

void update_coin_spawner(waddle* waddle);
//entity* spawn_coin(waddle* waddle);