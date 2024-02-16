#pragma once

typedef enum {
	// Waddle
	WADDLE_TRANSFORM,
	WADDLE_QUAD_RENDERER,
	WADDLE_QUAD_COLLIDER,
	WADDLE_SPRITE_RENDERER,

	// User defined
	QUAD_CONTROLLER,
	COIN_SPAWNER
} component_type;