#include "quad_controller.h"

void update_quad_controller(float delta_time, const Uint8* key_state, void* data) {
	if (key_state[SDL_SCANCODE_UP]) {
		printf("pressed up");
	}
}