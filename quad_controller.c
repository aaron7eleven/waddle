#include "quad_controller.h"
#include "waddle_component_transform.h"

void update_quad_controller(float delta_time, const Uint8* key_state, entity* entity) {
	
	for (int comp_i = 0; comp_i < entity->component_count; comp_i++) {
		if (entity->components[comp_i]->type == QUAD_CONTROLLER) {
			quad_controller* quad_ctrl = (quad_controller*)entity->components[comp_i]->data;
			
			quad_ctrl->velocity.x = 0.0f;
			quad_ctrl->velocity.y = 0.0f;
			
			if (key_state[SDL_SCANCODE_UP] || key_state[SDL_SCANCODE_W]) {
				quad_ctrl->velocity.y -= 1.0f;
			}

			if (key_state[SDL_SCANCODE_DOWN] || key_state[SDL_SCANCODE_S]) {
				quad_ctrl->velocity.y += 1.0f;
			}

			if (key_state[SDL_SCANCODE_LEFT] || key_state[SDL_SCANCODE_A]) {
				quad_ctrl->velocity.x -= 1.0f;
			}

			if (key_state[SDL_SCANCODE_RIGHT] || key_state[SDL_SCANCODE_D]) {
				quad_ctrl->velocity.x += 1.0f;
			}

			transform* t = (transform*)get_component(entity, TRANSFORM);
			t->position.x += quad_ctrl->velocity.x * quad_ctrl->speed * delta_time;
			t->position.y += quad_ctrl->velocity.y * quad_ctrl->speed * delta_time;


		}
	}
}