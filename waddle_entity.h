#pragma once
#include "waddle_component.h"

typedef struct {
	int id;
	int component_count;
	component* components[16];
} entity;

void* get_component(entity* entity, component_type type);