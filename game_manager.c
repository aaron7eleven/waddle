#include "game_manager.h"
#include "coin_spawner.h"

void on_coin_hit(game_manager* game_manager) {
	game_manager->coins_collected++;
	printf("player hit coin. coins collected = %d\n", game_manager->coins_collected);
}

void on_coin_spawn(game_manager* game_manager) {
	game_manager->coins_spawned++;
	printf("coins spawned = %d\n", game_manager->coins_spawned);
}

void update_game_manager(waddle* waddle) {
	for (int entity_i = 0; entity_i < waddle->entity_count; entity_i++) {
		// stuff with entity
		game_manager* gm = (game_manager*)get_component(waddle->entities[entity_i], GAME_MANAGER);
		if (gm == NULL) {
			continue;
		}

		if (gm->coins_collected == gm->coins_to_spawn) {
			reset_game(waddle->entities[entity_i]);
		}
	}
}

void reset_game(entity* game_overseer) {
	game_manager* gm = (game_manager*)get_component(game_overseer, GAME_MANAGER);

	if (gm == NULL) {
		return;
	}

	gm->coins_collected = 0;
	gm->coins_spawned = 0;

	coin_spawner* cs = (coin_spawner*)get_component(game_overseer, COIN_SPAWNER);
	if (cs == NULL) {
		return;
	}
	cs->spawn_timer = 0.0f;
}
