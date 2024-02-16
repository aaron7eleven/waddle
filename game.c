#include "game.h"
//#include "quad_controller.h"
//#include "coin_spawner.h"

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
	//	{ 1.0f, 1.0f }
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
	//	300.0f,
	//	{ 0.0f, 0.0f }
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
	//	300.0f,
	//	{ 0.0f, 0.0f }
	//});

	//entity* quad = create_entity(game->waddle);
	//quad->name = "quad";
	//add_component(quad, WADDLE_TRANSFORM, &(transform) {
	//	{ 100.0f, 100.0f},
	//	{ 0.0f, 0.0f },
	//	{ 1.0f, 1.0f }
	//});
	//add_component(quad, WADDLE_QUAD_RENDERER, &(quad_renderer) {
	//	{ 100.0f, 100.0f, 50.0f, 50.0f },
	//	{ 0.0f, 0.0f, 0.0f, 0.0f },
	//	{ 0xDB, 0xE7, 0xC9, 0xFF }
	//});
	//add_component(quad, QUAD_CONTROLLER, &(quad_controller) {
	//	300.0f,
	//	{ 0.0f, 0.0f }
	//});
	//add_component(quad, WADDLE_QUAD_COLLIDER, &(quad_collider) {
	//	{ 100.0f, 100.0f, 50.0f, 50.0f },
	//		DYNAMIC,
	//	{ 0.0f, 0.0f },
	//	{ 1.0f, 1.0f }
	//});

	//entity* coin_spawner = create_entity(game->waddle);
	//coin_spawner->name = "coin_spawner";
	//add_component(coin_spawner, WADDLE_TRANSFORM, &(transform)	{
	//	{ 0.0f, 0.0f },
	//	{ 0.0f, 0.0f },
	//	{ 1.0f, 1.0f }
	//});
	//add_component(coin_spawner, COIN_SPAWNER, &(coin_spawner) {
	//	{ 2.0f },
	//	{ 0.0f },
	//	{ 0 }
	//});


	waddle_load_assets(game->waddle);

	//add_update_callback(game->waddle, update_quad_controller);
	//add_update_callback(game->waddle, update_coin_spawner);

	return 0;
}

int game_run(game* game) {
	return waddle_run(game->waddle);
}

int game_free(game* game) {
	return waddle_free(game->waddle);
}

int game_main(int argc, char* argv[]) {
	game game;
	game_init(&game);
	game_run(&game);
	game_free(&game);
	return 0;
}