#include <stdio.h>
#include "waddle_entity.h"
void* get_component(entity* entity, component_type type) {
	for (int comp_i = 0; comp_i < entity->component_count; comp_i++) {
		if (entity->components[comp_i]->type == type) {
			return entity->components[comp_i]->data;
		}
	}

	return NULL;
}