#pragma once
#include "waddle.h"

typedef struct {
	int coins_collected;
	int coins_spawned;
	int coins_to_spawn;
} game_manager;

void update_game_manager(waddle* waddle);
void on_coin_hit(game_manager* game_manager);
void on_coin_spawn(game_manager* game_manager);
void reset_game(entity* game_overseer);
