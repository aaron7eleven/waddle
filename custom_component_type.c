#include "custom_component.h"
#include "quad_controller.h"

void* create_custom_component(custom_component_type type) {
	
	switch (type)
	{
		case QUAD_CONTROLLER: {
			return calloc(1, sizeof(quad_controller));
		} break;

		default:
			printf("custom component type not found\n");
			return;
	}

	return NULL;
}