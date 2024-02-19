#include <stdio.h>
#include <string.h>
#include "coin_spawner.h"

void update_coin_spawner(waddle* waddle) {
	for (int entity_i = 0; entity_i < waddle->entity_count; entity_i++) {
		coin_spawner* cs = (coin_spawner*) get_component(waddle->entities[entity_i], COIN_SPAWNER);
		if (cs != NULL) {
			if (cs->coins_spawned >= 4) {
				//printf("Spawned a coins...no more\n");
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
	
	waddle_transform* t = (waddle_transform*)create_component(WADDLE_TRANSFORM);
	if (t == NULL) {
		return 0;
	}
	t->position = (SDL_FPoint){ 40.0f + (float)(rand() % 560), 40.0f + (float)(rand() % 400) };
	t->rotation = (SDL_FPoint){ 0.0f, 0.0f };
	t->scale = (SDL_FPoint){ 1.0f, 1.0f };
	add_component(coin, WADDLE_TRANSFORM, t);

	waddle_sprite_renderer* sprite_rend = (waddle_sprite_renderer*)create_component(WADDLE_SPRITE_RENDERER);
	if (sprite_rend == NULL) {
		return 0;
	}
	sprite_rend->size = (SDL_FPoint){ 64.0f, 64.0f };
	sprite_rend->color = (SDL_Color){ 0xFF, 0xFF, 0xFF, 0xFF };
	sprite_rend->file = "test_assets/images/Coin.png";
	sprite_rend->texture = NULL;
	waddle_load_sprite(waddle->renderer, sprite_rend);
	add_component(coin, WADDLE_SPRITE_RENDERER, sprite_rend);

	waddle_quad_collider* quad_collider = create_component(WADDLE_QUAD_COLLIDER);
	quad_collider->type = STATIC;
	quad_collider->rect = (SDL_FRect){ 0.0f, 0.0f, 64.0f, 64.0f };
	quad_collider->delta = (SDL_FPoint){ 0.0f, 0.0f };
	quad_collider->scale = (SDL_FPoint){ 1.0f, 1.0f };
	quad_collider->on_collision_enter_callback = coin_on_collision_enter_callback;
	add_component(coin, WADDLE_QUAD_COLLIDER, quad_collider);

	return 1;
}

void coin_on_collision_enter_callback(entity* src_entity, entity* dest_entity) {
	//printf("%s hit %s...destroying %s\n", src_entity->name, dest_entity->name, src_entity->name);
	if (strcmp(dest_entity->name, "player") == 0) {
		destroy_entity(src_entity);
	}
}