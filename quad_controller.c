#include "quad_controller.h"

void update_quad_controller(waddle* waddle) {
	for (int entity_i = 0; entity_i < waddle->entity_count; entity_i++) {
		for (int comp_i = 0; comp_i < waddle->entities[entity_i]->component_count; comp_i++) {
			if (waddle->entities[entity_i]->components[comp_i]->type == QUAD_CONTROLLER) {
				quad_controller* quad_ctrl = (quad_controller*)waddle->entities[entity_i]->components[comp_i]->data;

				quad_ctrl->velocity.x = 0.0f;
				quad_ctrl->velocity.y = 0.0f;

				if (waddle->key_state[SDL_SCANCODE_UP] || waddle->key_state[SDL_SCANCODE_W]) {
					quad_ctrl->velocity.y -= 1.0f;
				}

				if (waddle->key_state[SDL_SCANCODE_DOWN] || waddle->key_state[SDL_SCANCODE_S]) {
					quad_ctrl->velocity.y += 1.0f;
				}

				if (waddle->key_state[SDL_SCANCODE_LEFT] || waddle->key_state[SDL_SCANCODE_A]) {
					quad_ctrl->velocity.x -= 1.0f;
				}

				if (waddle->key_state[SDL_SCANCODE_RIGHT] || waddle->key_state[SDL_SCANCODE_D]) {
					quad_ctrl->velocity.x += 1.0f;
				}

				if (magnitude(quad_ctrl->velocity.x, quad_ctrl->velocity.y) > 1.0f) {
					normalize(&(quad_ctrl->velocity));
				}

				transform* t = (transform*)get_component(waddle->entities[entity_i], WADDLE_TRANSFORM);
				t->position.x += quad_ctrl->velocity.x * quad_ctrl->speed * waddle->delta_time;
				t->position.y += quad_ctrl->velocity.y * quad_ctrl->speed * waddle->delta_time;
			}
		}
	}

	
}