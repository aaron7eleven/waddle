#include "game.h"
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
	entity* quad = create_entity(game->waddle);
	quad->name = "quad";
	add_component(quad, WADDLE_TRANSFORM, &(transform) {
		{ 100.0f, 100.0f},
		{ 0.0f, 0.0f },
		{ 1.0f, 1.0f }
	});
	add_component(quad, WADDLE_QUAD_RENDERER, &(quad_renderer) {
		{ 100.0f, 100.0f, 50.0f, 50.0f },
		{ 0xDB, 0xE7, 0xC9, 0xFF }
	});
	add_component(quad, QUAD_CONTROLLER, &(quad_controller) {
		300.0f,
		{ 0.0f, 0.0f }
	});
	add_component(quad, WADDLE_QUAD_COLLIDER, &(quad_collider) {
		{ 300.0f, 100.0f, 50.0f, 50.0f },
		DYNAMIC,
		{0.0f, 0.0f}
	});

	//entity* moveable_quad = create_entity(game->waddle);
	//add_component(moveable_quad, WADDLE_TRANSFORM, &(transform) {
	//	{ 300.0f, 100.0f},
	//	{ 0.0f, 0.0f },
	//	{ 1.0f, 1.0f }
	//});
	//add_component(moveable_quad, WADDLE_QUAD_RENDERER, &(quad_renderer) {
	//	{ 100.0f, 100.0f, 50.0f, 50.0f },
	//	{ 0xDB, 0xE7, 0xC9, 0xFF }
	//});
	////add_component(quad, QUAD_CONTROLLER, &(quad_controller) {
	////	300.0f,
	////	{ 0.0f, 0.0f }
	////});
	//add_component(moveable_quad, WADDLE_QUAD_COLLIDER, &(quad_collider) {
	//	{ 100.0f, 100.0f, 50.0f, 50.0f },
	//		DYNAMIC
	//});

	entity* small_wall = create_entity(game->waddle);
	small_wall->name = "small_wall";
	add_component(small_wall, WADDLE_TRANSFORM, &(transform) {
		{ 200.0f, 200.0f},
		{ 0.0f, 0.0f },
		{ 1.0f, 1.0f }
	});
	add_component(small_wall, WADDLE_QUAD_RENDERER, &(quad_renderer) {
		{ 50.0f, 50.0f, 100.0f, 100.0f },
		{ 0x78, 0x94, 0x61, 0xFF }
	});
	add_component(small_wall, WADDLE_QUAD_COLLIDER, &(quad_collider) {
		{ 100.0f, 100.0f, 100.0f, 100.0f },
		STATIC,
		{ 0.0f, 0.0f }
	});

	entity* medium_wall = create_entity(game->waddle);
	medium_wall->name = "medium_wall";
	add_component(medium_wall, WADDLE_TRANSFORM, &(transform) {
		{ 250.0f, 250.0f},
		{ 0.0f, 0.0f },
		{ 1.0f, 1.0f }
	});
	add_component(medium_wall, WADDLE_QUAD_RENDERER, &(quad_renderer) {
		{ 50.0f, 50.0f, 200.0f, 200.0f },
		{ 0x78, 0x94, 0x61, 0xFF }
	});
	add_component(medium_wall, WADDLE_QUAD_COLLIDER, &(quad_collider) {
		{ 100.0f, 100.0f, 200.0f, 200.0f },
		STATIC,
		{ 0.0f, 0.0f }
	});

	add_update_callback(game->waddle, update_quad_controller);

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