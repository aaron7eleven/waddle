#include "waddle_system_physics.h"
#include "waddle_component_transform.h"
#include "waddle_component_quad_collider.h"

void update_physics_system(entity* entities[], int entity_count) {
	update_colliders(entities, entity_count);
	check_collisions(entities, entity_count);
}

void update_colliders(entity* entities[], int entity_count) {
	// Update collider position
	for (int entity_i = 0; entity_i < entity_count; entity_i++) {
		if ((quad_collider*)get_component(entities[entity_i], QUAD_COLLIDER) == NULL) {
			continue;
		}

		quad_collider* quad_col = (quad_collider*) get_component(entities[entity_i], QUAD_COLLIDER);
		transform* quad_transform = (transform*) get_component(entities[entity_i], TRANSFORM);

		quad_col->rect.x = quad_transform->position.x;
		quad_col->rect.y = quad_transform->position.y;
	}
}

void check_collisions(entity* entities[], int entity_count) {
	for (int entity_i = 0; entity_i < entity_count; entity_i++) {
		for (int entity_j = entity_i + 1; entity_j < entity_count; entity_j++) {
			if (entity_i == entity_j) {
				// skip self checks
				continue;
			}

			if ((quad_collider*)get_component(entities[entity_i], QUAD_COLLIDER) == NULL) {
				continue;
			}

			if ((quad_collider*)get_component(entities[entity_j], QUAD_COLLIDER) == NULL) {
				continue;
			}

			if (check_collision(entities[entity_i], entities[entity_j])) {
				printf("collision occured\n");
			}
		}
	}
}

int check_collision(entity* a, entity* b) {
	quad_collider* a_quad_collider = (quad_collider*) get_component(a, QUAD_COLLIDER);
	quad_collider* b_quad_collider = (quad_collider*) get_component(b, QUAD_COLLIDER);

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