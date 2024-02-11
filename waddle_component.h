#pragma once

typedef enum {
	TRANSFORM,
	QUAD_RENDERER,
	QUAD_COLLIDER,
	QUAD_CONTROLLER
} component_type;


typedef struct {
	component_type type;
	void* data;
} component;