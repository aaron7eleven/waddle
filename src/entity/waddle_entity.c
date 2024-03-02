#include <stdio.h>
#include "data/waddle_globals.h"
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
#include "component/waddle_component_clip_sprite_renderer.h"

entity* create_entity()
{
	if ((entity_count + 1) >= MAX_ENTITIES) {
		printf("ERROR: At max entity count, not creating entity\n");
		return NULL;
	}

	entity* new_entity = calloc(1, sizeof(entity));
	new_entity->name = "entity";
	new_entity->id = entity_count;
	new_entity->component_count = 0;
	new_entity->destroy = 0;
	new_entity->max_component_per_entity = MAX_COMPONENT_PER_ENTITY;

	for (int comp_i = 0; comp_i < MAX_COMPONENT_PER_ENTITY; comp_i++) {
		new_entity->components[comp_i] = NULL;
	}

	// find place to store entity in list
	int store_entity = 0;
	for (int entity_i = 0; entity_i < MAX_ENTITIES; entity_i++) {

		if (entities[entity_i] == NULL) {
			entities[entity_i] = new_entity;
			store_entity = 1;
			break;
		}
	}

	if (!store_entity) {
		printf("_ERROR: unable find place to store newly created entity");
		free(new_entity);
		return NULL;
	}

	entity_count++;

	return new_entity;
}

void free_entity(entity** entity_ptr)
{
	if (entity_ptr == NULL) {
		printf("ERROR: passed in entity that is null\n");
		return;
	}

	entity* entity_to_destroy = *entity_ptr;
	if (entity_to_destroy == NULL) {
		printf("ERROR: trying to destroy entity which is null\n");
		return;
	}

	// Do I have to check if the entity exists in the list of entities? *hmm*
	//int destory_entity_i = -1;
	//for (int entity_i = 0; entity_i < entity_count; entity_i++) {
	//	if (entities[entity_i]id == entity_to_destroyid) {
	//		// found entity to destroy
	//		destory_entity_i = entity_i;
	//		break;
	//	}
	//}

	//if (destory_entity_i < 0) {
	//	printf("_ERROR: unable to find entity to destroy\n");
	//	return;
	//}

	// Destroy entity
	free_components(entity_to_destroy);
	entity_to_destroy = NULL;
	free(*entity_ptr);
	*entity_ptr = NULL;

	// Restructure entities list so there are no gaps
	for (int entity_i = 0; entity_i < entity_count; entity_i++) {
		// if current entity is not null, move to next
		if (entities[entity_i] != NULL) continue;

		// if current entity index is the last index, move on to the end loop
		if ((entity_i + 1) >= entity_count) continue;

		// if next entity is null, move to next (will be come current) (double check for sanity)
		if (entities[entity_i + 1] == NULL) continue;

		// Swap entity pointer (safely)
		entity* entity_tmp = entities[entity_i];
		entities[entity_i] = entities[entity_i + 1];
		entities[entity_i + 1] = entity_tmp; // should be setting to null
	}

	entity_count--;
}

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

		case WADDLE_CLIP_SPRITE_RENDERER: {
			return calloc(1, sizeof(waddle_clip_sprite_renderer));
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
