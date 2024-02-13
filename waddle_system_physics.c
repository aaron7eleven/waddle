#include "waddle_system_physics.h"
#include "waddle_component_transform.h"
#include "waddle_component_quad_collider.h"
#include "waddle_colliders.h"
#include "waddle_math.h"

void update_physics_system(entity* entities[], int entity_count) {
	update_colliders(entities, entity_count);
	check_collisions(entities, entity_count);
}

void update_colliders(entity* entities[], int entity_count) {
	// Update collider position
	for (int entity_i = 0; entity_i < entity_count; entity_i++) {
		if ((quad_collider*)get_component(entities[entity_i], QUAD_COLLIDER) != NULL) {
			// If collision type is static, you don't need to update every frame. Just the first time.
			//quad_collider* q_collider = (quad_collider*)get_component(entities[entity_i], QUAD_COLLIDER);
			//if (q_collider->type != STATIC) {
			//	update_quad_collider(entities[entity_i]);
			//}
			update_quad_collider(entities[entity_i]);
		}
	}
}

void update_quad_collider(entity* entity) {
	quad_collider* quad_col = (quad_collider*)get_component(entity, QUAD_COLLIDER);
	transform* quad_transform = (transform*)get_component(entity, TRANSFORM);

	quad_col->delta.x = quad_transform->position.x - quad_col->rect.x;
	quad_col->delta.y = quad_transform->position.y - quad_col->rect.y;

	quad_col->rect.x = quad_transform->position.x;
	quad_col->rect.y = quad_transform->position.y;
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
				collision_response(entities[entity_i], entities[entity_j]);
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

void collision_response(entity* a, entity* b) {
	quad_collider* a_quad_collider = (quad_collider*)get_component(a, QUAD_COLLIDER);
	quad_collider* b_quad_collider = (quad_collider*)get_component(b, QUAD_COLLIDER);
	
	if (a_quad_collider->type == STATIC && b_quad_collider->type == STATIC) {
		// Don't do anything?
		return;
	}

	if (a_quad_collider->type == DYNAMIC && b_quad_collider->type == STATIC) {
		// Move a
		transform* a_quad_transform = (transform*) get_component(a, TRANSFORM);

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
		transform* b_quad_transform = (transform*)get_component(b, TRANSFORM);

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
		transform* a_quad_transform = (transform*) get_component(a, TRANSFORM);
		float a_delta_magn = magnitude(a_quad_collider->delta.x, a_quad_collider->delta.y);
		float b_delta_magn = magnitude(b_quad_collider->delta.x, b_quad_collider->delta.y);

		//float total_dx = a_quad_collider->delta.x + 
		if (a_delta_magn > 0) {
			if (b_delta_magn == 0.0f) {
				// push b using a's delta
				transform* b_quad_transform = (transform*)get_component(b, TRANSFORM);
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
		printf("uncaught collision repsonse...");
	}
	
}