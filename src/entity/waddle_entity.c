#include <stdio.h>
#include "entity/waddle_entity.h"
#include "component/waddle_component_transform.h"
#include "component/waddle_component_quad_collider.h"
#include "component/waddle_component_quad_renderer.h"
#include "component/waddle_component_sprite_renderer.h"
#include "component/waddle_component_audio_player.h"
#include "component/waddle_component_ui_text.h"
#include "component/waddle_component_animation.h"
#include "component/waddle_component_animator.h"
#include "component/waddle_component_animated_sprite_renderer.h"

WADDLE_API void* create_component(component_type type) {
	switch (type)
	{
		case WADDLE_TRANSFORM: {
			return calloc(1, sizeof(waddle_transform));
		} break;

		case WADDLE_QUAD_RENDERER: {
			return calloc(1, sizeof(waddle_quad_renderer));
		} break;

		case WADDLE_QUAD_COLLIDER: {
			return calloc(1, sizeof(waddle_quad_collider));
		} break;

		case WADDLE_SPRITE_RENDERER: {
			return calloc(1, sizeof(waddle_sprite_renderer));
		} break;

		case WADDLE_AUDIO_PLAYER: {
			return calloc(1, sizeof(waddle_audio_player));
		} break;

		case WADDLE_UI_TEXT: {
			return calloc(1, sizeof(waddle_ui_text));
		} break;

		case WADDLE_ANIMATION: {
			return calloc(1, sizeof(waddle_animation));
		} break;

		case WADDLE_ANIMATOR: {
			return calloc(1, sizeof(waddle_animator));
		} break;

		case WADDLE_ANIMATED_SPRITE_RENDERER: {
			return calloc(1, sizeof(waddle_animated_sprite_renderer));
		} break;

	default:
		printf("component type not found in waddle. Check custom");
		return NULL;
	}
	
}

WADDLE_API void* create_component_by_size(size_t sizeof_size) {
	return calloc(1, sizeof_size);
}

WADDLE_API void* get_component(entity* entity, component_type type) {
	for (int comp_i = 0; comp_i < entity->component_count; comp_i++) {
		if (entity->components[comp_i]->type == type) {
			return entity->components[comp_i]->data;
		}
	}

	return NULL;
}

WADDLE_API void add_component(entity* entity, component_type type, void* data) {
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

WADDLE_API void free_component(component* component) {
	free(component->data);
}

WADDLE_API void free_components(entity* entity) {
	for (int comp_i = 0; comp_i < entity->component_count; comp_i++) {
		free_component(entity->components[comp_i]);
		free(entity->components[comp_i]);
		entity->components[comp_i] = NULL;
	}
	entity->component_count = 0;
}

WADDLE_API void destroy_entity(entity* entity) {
	entity->destroy = 1;
}
