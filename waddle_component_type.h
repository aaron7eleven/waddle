#pragma once
//#include "waddle_component_types.h"
//#include "waddle_game_component_types.h"

//typedef enum {
//	WADDLE_COMPONENT_START = 0,
//	WADDLE_COMPONENT_END = WADDLE_COMPONENT_COUNT - 1,
//	WADDLE_GAME_COMPONENT_START = WADDLE_COMPONENT_COUNT,
//	WADDLE_GAME_COMPONENT_END = WADDLE_GAME_COMPONENT_START + WADDLE_GAME_COMPONENT_COUNT - 1,
//	COMPONENT_COUNT
//} component_type;

typedef enum {
	// Waddle
	WADDLE_TRANSFORM,
	WADDLE_QUAD_RENDERER,
	WADDLE_QUAD_COLLIDER,

	// User defined
	QUAD_CONTROLLER
} component_type;