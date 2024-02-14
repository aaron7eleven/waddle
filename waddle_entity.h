#pragma once
#include "waddle_component.h"

typedef struct {
	const char* name;
	int id;
	int component_count;
	int max_component_per_entity;
	component* components[16];
} entity;

void* get_component(entity* entity, component_type type);
void add_component(entity* entity, component_type type, void* data);