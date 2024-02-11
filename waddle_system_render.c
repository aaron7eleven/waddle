#include "waddle_system_render.h"
#include "waddle_component_transform.h"
#include "waddle_component_quad_renderer.h"

void update_render_system(SDL_Renderer* renderer, entity* entity)
{
	for (int comp_i = 0; comp_i < entity->component_count; comp_i++) {	
		if (entity->components[comp_i]->type == QUAD_RENDERER) {
			quad_renderer* q_rend = (quad_renderer*)entity->components[comp_i]->data;
			SDL_SetRenderDrawColor(renderer, q_rend->color.r, q_rend->color.g, q_rend->color.b, q_rend->color.a);
			transform* t = (transform*)get_component(entity, TRANSFORM);

			SDL_FRect render_rect = {
				t->position.x,
				t->position.y,
				q_rend->rect.w * t->scale.x,
				q_rend->rect.h * t->scale.y
			};

			SDL_RenderFillRectF(renderer, &render_rect);
		}
	}
}
