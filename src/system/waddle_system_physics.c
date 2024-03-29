#include <stdio.h>


#include "data/waddle_globals.h"
#include "system/waddle_system_physics.h"
#include "component/waddle_component_quad_collider.h"
#include "component/waddle_component_transform.h"
#include "util/waddle_math.h"

WADDLE_API void update_physics_system(entity* entity) {
	update_collider(entity);
	check_collisions(entity);
}

WADDLE_API void update_collider(entity* entity) {
	waddle_quad_collider* quad_col = (waddle_quad_collider*) get_component(entity, WADDLE_QUAD_COLLIDER);
	if (quad_col != NULL) {
		update_quad_collider(entity);
	}
}

WADDLE_API void update_quad_collider(entity* entity) {
	waddle_quad_collider* quad_col = (waddle_quad_collider*)get_component(entity, WADDLE_QUAD_COLLIDER);
	waddle_transform* quad_transform = (waddle_transform*)get_component(entity, WADDLE_TRANSFORM);

	if (quad_col == NULL) {
		printf("update_quad_collider():%s doesn't have a quad_collider\n", entity->name);
		return;
	}

	if (quad_transform == NULL) {
		printf("update_quad_collider():%s doesn't have a transform\n", entity->name);
		return;
	}

	quad_col->delta.x = quad_transform->position.x - quad_col->rect.x;
	quad_col->delta.y = quad_transform->position.y - quad_col->rect.y;

	quad_col->rect.x = quad_transform->position.x;
	quad_col->rect.y = quad_transform->position.y;	
}

WADDLE_API void check_collisions(entity* entity) {
	for (int entity_i = 0; entity_i < entity_count; entity_i++) {
		if (entity->id == entities[entity_i]->id) {
			// skip self checks
			continue;
		}

		if ((waddle_quad_collider*)get_component(entities[entity_i], WADDLE_QUAD_COLLIDER) == NULL) {
			continue;
		}

		if (check_collision(entity, entities[entity_i])) {
			//printf("collision occured\n");
			waddle_quad_collider* quad_collider = (waddle_quad_collider*)get_component(entity, WADDLE_QUAD_COLLIDER);
			if (quad_collider->on_collision_enter_callback != NULL) {
				quad_collider->on_collision_enter_callback(entity, entities[entity_i]);
			}

			waddle_quad_collider* i_quad_collider = (waddle_quad_collider*) get_component(entities[entity_i], WADDLE_QUAD_COLLIDER);
			if (i_quad_collider->on_collision_enter_callback != NULL) {
				i_quad_collider->on_collision_enter_callback(entities[entity_i], entity);
			}
				
			//collision_response(entities[entity_i], entities[entity_j]);
		}
	}
}

WADDLE_API int check_collision(entity* a, entity* b) {
	waddle_quad_collider* a_quad_collider = (waddle_quad_collider*) get_component(a, WADDLE_QUAD_COLLIDER);
	waddle_quad_collider* b_quad_collider = (waddle_quad_collider*) get_component(b, WADDLE_QUAD_COLLIDER);

	// Is the right edge of b to the left of the left edge of a
	if ((b_quad_collider->rect.x + b_quad_collider->rect.w) < a_quad_collider->rect.x ) {
		//printf("right edge of b is left of left edge of a\n");
		return 0;
	}

	// Is the right edge of a to the left of the left edge of b
	if ((a_quad_collider->rect.x + a_quad_collider->rect.w) < b_quad_collider->rect.x) {
		//printf("right edge of a is left of left edge of b\n");
		return 0;
	}

	// Is the bottom edge of b to the above of the top edge of a
	if ((b_quad_collider->rect.y + b_quad_collider->rect.h) < a_quad_collider->rect.y) {
		//printf("bottom edge of b is above of top edge of a\n");
		return 0;
	}

	// Is the bottom edge of a to the above of the top edge of b
	if ((a_quad_collider->rect.y + a_quad_collider->rect.h) < b_quad_collider->rect.y) {
		//printf("bottom edge of a is above of top edge of b\n");
		return 0;
	}

	return 1;
}

WADDLE_API void collision_response(entity* a, entity* b) {
	waddle_quad_collider* a_quad_collider = (waddle_quad_collider*)get_component(a, WADDLE_QUAD_COLLIDER);
	waddle_quad_collider* b_quad_collider = (waddle_quad_collider*)get_component(b, WADDLE_QUAD_COLLIDER);
	
	if (a_quad_collider->type == STATIC && b_quad_collider->type == STATIC) {
		// Don't do anything?
		return;
	}

	if (a_quad_collider->type == DYNAMIC && b_quad_collider->type == STATIC) {
		// Move a
		waddle_transform* a_quad_transform = (waddle_transform*) get_component(a, WADDLE_TRANSFORM);

		// undo delta. Makes a passable collision. Not perfect. Leaves a little gap between colliders sometimes.
		// could get a closer to collision by 
		// getting the actual delta between the edges by computing them based on delta rather than the change in transform
		// moves it to the same position before the collision
		a_quad_transform->position.x -= a_quad_collider->delta.x;
		a_quad_transform->position.y -= a_quad_collider->delta.y;
		printf("dynamic a hit static b by (%f,%f)\n", a_quad_collider->delta.x, a_quad_collider->delta.y);
		update_quad_collider(a);
	}
	else if (a_quad_collider->type == STATIC && b_quad_collider->type == DYNAMIC) {
		// Move b
		waddle_transform* b_quad_transform = (waddle_transform*)get_component(b, WADDLE_TRANSFORM);

		// undo delta. Makes a passable collision. Not perfect. Leaves a little gap between colliders sometimes.
		// could get a closer to collision by 
		// getting the actual delta between the edges by computing them based on delta rather than the change in transform
		// moves it to the same position before the collision
		b_quad_transform->position.x -= b_quad_collider->delta.x;
		b_quad_transform->position.y -= b_quad_collider->delta.y;
		printf("dynamic a hit static b by (%f,%f)\n", b_quad_collider->delta.x, b_quad_collider->delta.y);
		update_quad_collider(b);
	}
	else if (a_quad_collider->type == DYNAMIC && b_quad_collider->type == DYNAMIC) {
		// Move a & b (equally in opposite directions?)
		// Move a
		waddle_transform* a_quad_transform = (waddle_transform*) get_component(a, WADDLE_TRANSFORM);
		float a_delta_magn = magnitude(a_quad_collider->delta.x, a_quad_collider->delta.y);
		float b_delta_magn = magnitude(b_quad_collider->delta.x, b_quad_collider->delta.y);

		//float total_dx = a_quad_collider->delta.x + 
		if (a_delta_magn > 0) {
			if (b_delta_magn == 0.0f) {
				// push b using a's delta
				waddle_transform* b_quad_transform = (waddle_transform*)get_component(b, WADDLE_TRANSFORM);
				b_quad_transform->position.x += a_quad_collider->delta.x;
				b_quad_transform->position.y += a_quad_collider->delta.y;
				update_quad_collider(b);
			}
		}

		//a_quad_transform->position.x -= (a_quad_collider->delta.x / 2.0f);
		//a_quad_transform->position.y -= (a_quad_collider->delta.y / 2.0f);
		////printf("dynamic a hit static b by (%f,%f)\n", a_quad_collider->delta.x, a_quad_collider->delta.y);
		//update_quad_collider(a);

		//transform* b_quad_transform = (transform*)get_component(b, TRANSFORM);
		//b_quad_transform->position.x -= (b_quad_collider->delta.x / 2.0f);
		//b_quad_transform->position.y -= (b_quad_collider->delta.y / 2.0f);
		//update_quad_collider(b);

		//printf("dynamic a hit dynamic a\n");
	}
	else {
		//printf("uncaught collision repsonse...\n");
	}
	
}