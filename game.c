#include "game.h"
#include "custom_component.h"
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
	//entity* quad = create_entity(game->waddle);
	//quad->name = "quad";
	//add_component(quad, WADDLE_TRANSFORM, &(transform) {
	//	{ 100.0f, 100.0f},
	//	{ 0.0f, 0.0f },
	//	{ 1.0f, 1.0f },
	//});
	//add_component(quad, WADDLE_QUAD_RENDERER, &(quad_renderer) {
	//	{ 50.0f, 50.0f },
	//	{ 0xDB, 0xE7, 0xC9, 0xFF }
	//});
	//add_component(quad, WADDLE_QUAD_COLLIDER, &(quad_collider) {
	//	DYNAMIC,
	//	{ 100.0f, 100.0f, 50.0f, 50.0f },
	//	{ 0.0f, 0.0f },
	//	{ 1.0f, 1.0f }
	//});
	//add_component(quad, QUAD_CONTROLLER, &(quad_controller) {
	//	300.0f
	//});

	//entity* coin_spawner_entity = create_entity(game->waddle);
	//coin_spawner_entity->name = "coin_spawner";
	//add_component(coin_spawner_entity, WADDLE_TRANSFORM, &(transform) {
	//	{ 10.0f, 0.0f },
	//	{ 0.0f, 0.0f },
	//	{ 1.0f, 1.0f }
	//});
	//add_component(coin_spawner_entity, WADDLE_QUAD_RENDERER, &(quad_renderer) {
	//	{ 10.0f, 10.0f },
	//	{ 0x00, 0x00, 0xFF, 0xFF }
	//});
	//add_component(coin_spawner_entity, QUAD_CONTROLLER, &(quad_controller) {
	//	300.0f
	//});
	//add_component(coin_spawner_entity, COIN_SPAWNER, &(coin_spawner) {
	//	2.0f,
	//	0.0f,
	//	0
	//});

	//entity* sprite = create_entity(game->waddle);
	//sprite->name = "sprite";
	//add_component(sprite, WADDLE_TRANSFORM, &(transform) {
	//	{ 200.0f, 100.0f},
	//	{ 0.0f, 0.0f },
	//	{ 1.0f, 1.0f }
	//});
	//add_component(sprite, WADDLE_SPRITE_RENDERER, &(sprite_renderer) {
	//	{ 128.0f, 128.0f },
	//	{ 0xFF, 0xFF, 0xFF, 0xFF },
	//	"test_assets/images/smiley_64x64.png",
	//	NULL
	//});

	//add_component(sprite, WADDLE_QUAD_COLLIDER, &(quad_collider) {
	//	DYNAMIC,
	//	{ 200.0f, 100.0f, 128.0f, 128.0f },
	//	{ 0.0f, 0.0f },
	//	{ 1.0f, 1.0f }
	//});
	//add_component(sprite, WADDLE_QUAD_RENDERER, &(quad_renderer) {
	//	{ 64.0f, 64.0f },
	//	{ 0xFF, 0xFF, 0xFF, 0xFF }
	//});
	//add_component(sprite, QUAD_CONTROLLER, &(quad_controller) {
	//	300.0f
	//});

	//entity* entity = create_entity(game->waddle);
	//entity->name = "quad";
	//peek_entity(entity);
	//transform* t = create_component(WADDLE_TRANSFORM);
	//t->position.x = 100.0f;
	//t->position.y = 100.0f;
	//t->rotation = (SDL_FPoint){ 0.0f, 0.0f };
	//t->scale = (SDL_FPoint){ 1.0f, 1.0f };

	////peek_entity(entity);
	//add_component(entity, WADDLE_TRANSFORM, t);
	////peek_entity(entity);
	//transform* got_t = (transform*)get_component(entity, WADDLE_TRANSFORM);
	//
	//quad_renderer* quad_renderer = create_component(WADDLE_QUAD_RENDERER);
	//quad_renderer->size = (SDL_FPoint){ 64.0f, 64.0f };
	//quad_renderer->color = (SDL_Color){ 0xFF, 0xFF, 0xFF, 0xFF };
	//
	////peek_entity(entity);
	//add_component(entity, WADDLE_QUAD_RENDERER, quad_renderer);
	////peek_entity(entity);

	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++) {
			entity* entity = create_entity(game->waddle);
			entity->name = "quad";
			
			transform* transform = create_waddle_component(WADDLE_TRANSFORM);
			transform->position.x = (float)((float) x * 100.0f + 100.0f);
			transform->position.y = (float)((float) y * 100.0f + 100.0f);
			transform->rotation = (SDL_FPoint){ 0.0f, 0.0f };
			transform->scale = (SDL_FPoint){ 1.0f, 1.0f };
			add_component(entity, WADDLE_TRANSFORM, transform);

			quad_renderer* quad_renderer = create_waddle_component(WADDLE_QUAD_RENDERER);
			quad_renderer->size = (SDL_FPoint) { 64.0f, 64.0f };
			quad_renderer->color = (SDL_Color){ 0xFF, 0xFF, 0xFF, 0xFF };
			add_component(entity, WADDLE_QUAD_RENDERER, quad_renderer);

			quad_controller* quad_controller = create_custom_component(QUAD_CONTROLLER);
			quad_controller->speed = 300.0f;
			add_component(entity, QUAD_CONTROLLER, quad_controller);

		}
	}

	//peek_entities(game->waddle);

	//waddle_load_assets(game->waddle);

	add_update_callback(game->waddle, update_quad_controller);
	//add_update_callback(game->waddle, update_coin_spawner);
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