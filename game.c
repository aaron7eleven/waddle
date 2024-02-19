#include "game.h"
#include "coin_spawner.h"
#include "quad_controller.h"

int game_init(game* game) {
	game->name = "Waddle: 2D test demo";
	game->waddle = waddle_create();
	
	// Check if created waddle
	if (game->waddle == NULL) {
		return 1;
	}

	// Customize waddle configuration
	game->waddle->window_title = game->name; // could assign directly

	// Initialize waddle
	if (waddle_init(game->waddle)) {
		return 1;
	}

	// Add all the game entity's and their components
	// Player
	entity* player = create_entity(game->waddle);
	player->name = "player";

	transform* player_transform = create_component(WADDLE_TRANSFORM);
	player_transform->position.x = game->waddle->screen_width / 2.0f - 32.0f; // minus width of sprite
	player_transform->position.y = game->waddle->screen_height / 2.0f - 32.0f; // minus height of sprite
	player_transform->rotation = (SDL_FPoint){ 0.0f, 0.0f };
	player_transform->scale = (SDL_FPoint){ 1.0f, 1.0f };
	add_component(player, WADDLE_TRANSFORM, player_transform);

	sprite_renderer* sprite_renderer = create_component(WADDLE_SPRITE_RENDERER);
	sprite_renderer->size = (SDL_FPoint){ 64.0f, 64.0f };
	sprite_renderer->color = (SDL_Color){ 0xFF, 0xFF, 0xFF, 0xFF };
	sprite_renderer->file = "test_assets/images/smiley_64x64.png";
	sprite_renderer->texture = NULL;
	add_component(player, WADDLE_SPRITE_RENDERER, sprite_renderer);

	quad_controller* quad_ctrl = create_component_by_size(sizeof(quad_controller));
	quad_ctrl->speed = 300.0f;
	add_component(player, QUAD_CONTROLLER, quad_ctrl);

	// coin spawner
	entity* coin_spawner_entity = create_entity(game->waddle);
	coin_spawner_entity->name = "coin_spawner";

	transform* cs_transform = create_component(WADDLE_TRANSFORM);
	cs_transform->position = (SDL_FPoint){ 0.0f, 0.0f };
	cs_transform->rotation = (SDL_FPoint){ 0.0f, 0.0f };
	cs_transform->scale = (SDL_FPoint){ 1.0f, 1.0f };
	add_component(coin_spawner_entity, WADDLE_TRANSFORM, cs_transform);

	coin_spawner* coin_spawn = create_component_by_size(sizeof(coin_spawner));
	coin_spawn->time_to_spawn = 2.0F;
	coin_spawn->spawn_timer = 0.0f;
	coin_spawn->coins_spawned = 0;
	add_component(coin_spawner_entity, COIN_SPAWNER, coin_spawn);

	waddle_load_assets(game->waddle);

	add_update_callback(game->waddle, update_quad_controller);
	add_update_callback(game->waddle, update_coin_spawner);

	return 0;
}

int game_run(game* game) {
	return waddle_run(game->waddle);
}

void game_free(game* game) {
	return waddle_free(game->waddle);
}

int game_main(int argc, char* argv[]) {
	game game;
	if (game_init(&game)) {
		return 1;
	}

	while (!game_run(&game)) {
		if (game.waddle->restart == 1) {
			if (game_init(&game)) {
				return 1;
			}
		}
		else {
			// trying to quit
			break;
		}
	}
	
	game_free(&game);
	return 0;
}