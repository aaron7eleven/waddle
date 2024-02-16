#pragma once
#include "waddle.h"

typedef struct {
	float time_to_spawn;
	float spawn_timer;
	int coins_spawned;
} coin_spawner;

void update_coin_spawner(waddle* waddle);
//entity* spawn_coin(waddle* waddle);