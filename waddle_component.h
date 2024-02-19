#pragma once

typedef enum {
	// Waddle
	WADDLE_TRANSFORM,
	WADDLE_QUAD_RENDERER,
	WADDLE_QUAD_COLLIDER,
	WADDLE_SPRITE_RENDERER,
	WADDLE_COMPONENT_COUNT,

	// Custom
	QUAD_CONTROLLER,
	COIN_SPAWNER,
	COIN_MANAGER,
	GAME_MANAGER
} component_type;

typedef struct {
	component_type type;
	void* data;
} component;