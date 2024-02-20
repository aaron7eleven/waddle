#pragma once
#include "waddle_component.h"

typedef struct {
	const char* name;
	int id;
	int component_count;
	int max_component_per_entity;
	component* components[16];
	int destroy;
} entity;

void* get_component(entity* entity, component_type type);
void add_component(entity* entity, component_type type, void* data);
void* create_component(component_type type);
void* create_component_by_size(size_t sizeof_size);
//void destory_components(entity* entity);
//void destory_component(entity* entity, component* );

//void free_component(entity* entity, component_type type);
void free_components(entity* entity);
void destroy_entity(entity* entity);