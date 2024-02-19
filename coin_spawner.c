#include <stdio.h>
#include <string.h>
#include "coin_spawner.h"
#include "coin_manager.h"
#include "game_manager.h"

void update_coin_spawner(waddle* waddle) {
	for (int entity_i = 0; entity_i < waddle->entity_count; entity_i++) {
		coin_spawner* cs = (coin_spawner*) get_component(waddle->entities[entity_i], COIN_SPAWNER);
		if (cs != NULL) {
			game_manager* gm = (game_manager*) get_component(waddle->entities[entity_i], GAME_MANAGER);
			if (gm->coins_spawned >= gm->coins_to_spawn) {
				//printf("Spawned a coins...no more\n");
				break;
			}

			cs->spawn_timer += waddle->delta_time;
			if (cs->spawn_timer >= cs->time_to_spawn) {
				// spawn coin
				spawn_coin(waddle);
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
	t->position = (SDL_FPoint){ 40.0f + (float)(rand() % 1000), 40.0f + (float)(rand() % 600) };
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

	game_manager* gm = NULL;
	for (int entity_i = 0; entity_i < waddle->entity_count; entity_i++) {
		gm = (game_manager*)get_component(waddle->entities[entity_i], GAME_MANAGER);
		if (gm != NULL) {
			break;
		}
	}

	if (gm == NULL) {
		return 0;
	}

	on_coin_spawn(gm);

	coin_manager* cm = create_component_by_size(sizeof(coin_manager));
	cm->game_manager = gm;
	add_component(coin, COIN_MANAGER, cm);

	return 1;
}

void coin_on_collision_enter_callback(entity* src_entity, entity* dest_entity) {
	//printf("%s hit %s...destroying %s\n", src_entity->name, dest_entity->name, src_entity->name);
	if (strcmp(dest_entity->name, "player") == 0) {
		coin_manager* cm = (coin_manager*) get_component(src_entity, COIN_MANAGER);
		
		if (cm == NULL) {
			return;
		}

		on_coin_hit(cm->game_manager);
		destroy_entity(src_entity);
	}
}
