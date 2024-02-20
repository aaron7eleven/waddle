#pragma once
#include "waddle.h"
// These are lazy copy and paste "functions" that contain loops that happen often

void waddle_entities_component_loop(waddle* waddle) {
	for (int entity_i = 0; entity_i < waddle->entity_count; entity_i++) {
		for (int comp_i = 0; comp_i < waddle->entities[entity_i]->component_count; comp_i++) {
			switch (waddle->entities[entity_i]->components[comp_i]->type)
			{
				// add statements to filter by component type
			default:
				break;
			}
		}
	}
}

void waddle_entity_component_loop(entity* entity) {
	for (int comp_i = 0; comp_i < entity->component_count; comp_i++) {
		switch (entity->components[comp_i]->type)
		{
			// add statements to filter by component type
		default:
			break;
		}
	}
}

void waddle_entities_loop(waddle* waddle) {
	for (int entity_i = 0; entity_i < waddle->entity_count; entity_i++) {
		// stuff with entity
	}
}