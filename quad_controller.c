#include "quad_controller.h"

void update_quad_controller(waddle* waddle) {
	for (int entity_i = 0; entity_i < waddle->entity_count; entity_i++) {
		entity* entity = waddle->entities[entity_i];
		quad_controller* quad_ctrl = (quad_controller*) get_component(entity, QUAD_CONTROLLER);
		if (quad_ctrl != NULL) {
			transform* t = (transform*) get_component(entity, WADDLE_TRANSFORM);
			if (t == NULL) {
				printf("%s doesn't have a transform to use in quad_controller", entity->name);
				continue;
			}

			SDL_FPoint velocity = { 0.0f , 0.0f };

			if (waddle->key_state[SDL_SCANCODE_UP] || waddle->key_state[SDL_SCANCODE_W]) {
				//quad_ctrl->velocity.y -= 1.0f;
				velocity.y -= 1.0f;
			}

			if (waddle->key_state[SDL_SCANCODE_DOWN] || waddle->key_state[SDL_SCANCODE_S]) {
				//quad_ctrl->velocity.y += 1.0f;
				velocity.y += 1.0f;
			}

			if (waddle->key_state[SDL_SCANCODE_LEFT] || waddle->key_state[SDL_SCANCODE_A]) {
				//quad_ctrl->velocity.x -= 1.0f;
				velocity.x -= 1.0f;
			}

			if (waddle->key_state[SDL_SCANCODE_RIGHT] || waddle->key_state[SDL_SCANCODE_D]) {
				//quad_ctrl->velocity.x += 1.0f;
				velocity.x += 1.0f;
			}

			if (magnitude(velocity.x, velocity.y) > 1.0f) {
				normalize(&velocity);
			}

			t->position.x += velocity.x * quad_ctrl->speed * waddle->delta_time;
			t->position.y += velocity.y * quad_ctrl->speed * waddle->delta_time;
		}
	}
}