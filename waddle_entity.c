#include <stdio.h>
#include "waddle_entity.h"
#include "waddle_component_include.h"

void* create_component(component_type type) {
	switch (type)
	{
		case WADDLE_TRANSFORM: {
			return calloc(1, sizeof(transform));
		} break;

		case WADDLE_QUAD_RENDERER: {
			return calloc(1, sizeof(quad_renderer));
		} break;

		case WADDLE_QUAD_COLLIDER: {
			return calloc(1, sizeof(quad_collider));
		} break;

		case WADDLE_SPRITE_RENDERER: {
			return calloc(1, sizeof(quad_collider));
		} break;

	default:
		printf("component type not found in waddle. Check custom");
		return NULL;
	}
	
}

void* create_component_by_size(size_t sizeof_size) {
	return calloc(1, sizeof_size);
}

void* get_component(entity* entity, component_type type) {
	for (int comp_i = 0; comp_i < entity->component_count; comp_i++) {
		if (entity->components[comp_i]->type == type) {
			return entity->components[comp_i]->data;
		}
	}

	return NULL;
}

void add_component(entity* entity, component_type type, void* data) {
	if ((entity->component_count + 1) >= entity->max_component_per_entity) {
		printf("ERROR: At max component count per entity, not adding component to entity");
		return NULL;
	}

	component* new_component = malloc(sizeof(component));
	new_component->type = type;
	new_component->data = data;
	
	entity->components[entity->component_count] = new_component;
	entity->component_count++;
}