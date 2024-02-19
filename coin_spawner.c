#include "coin_spawner.h"

void update_coin_spawner(waddle* waddle) {
	for (int entity_i = 0; entity_i < waddle->entity_count; entity_i++) {
		

		coin_spawner* cs = (coin_spawner*) get_component(waddle->entities[entity_i], COIN_SPAWNER);
		if (cs != NULL) {
			if (cs->coins_spawned >= 1) {
				printf("Spawned a coins...no more\n");
				break;
			}
			cs->spawn_timer += waddle->delta_time;
			if (cs->spawn_timer >= cs->time_to_spawn) {
				// spawn coin
				
				if (spawn_coin(waddle)) {
					cs->coins_spawned++;
					printf("spawned coin\n");
				}

				cs->spawn_timer -= cs->time_to_spawn;
			}
		}
	}
}

int spawn_coin(waddle* waddle) {
	// actually spawn coin
	entity* coin = create_entity(waddle);
	if (coin == NULL) {
		return 0;
	}
	coin->name = "coin";
	
	transform* t = (transform*)create_component(WADDLE_TRANSFORM);
	if (t == NULL) {
		return 0;
	}
	t->position = (SDL_FPoint){ 40.0f + (float)(rand() % 560), 40.0f + (float)(rand() % 400) };
	//t->position = (SDL_FPoint){ 40.0f + (float)(rand() % 560), 40.0f + (float)(rand() % 400) };
	t->rotation = (SDL_FPoint){ 0.0f, 0.0f };
	t->scale = (SDL_FPoint){ 1.0f, 1.0f };
	add_component(coin, WADDLE_TRANSFORM, t);

	sprite_renderer* sprite_rend = (sprite_renderer*)create_component(WADDLE_SPRITE_RENDERER);
	if (sprite_rend == NULL) {
		return 0;
	}
	sprite_rend->size = (SDL_FPoint){ 64.0f, 64.0f };
	sprite_rend->color = (SDL_Color){ 0xFF, 0xFF, 0xFF, 0xFF };
	sprite_rend->file = "test_assets/images/Coin.png";
	sprite_rend->texture = NULL;
	waddle_load_sprite(waddle->renderer, sprite_rend);

	add_component(coin, WADDLE_SPRITE_RENDERER, sprite_rend);
	return 1;
}