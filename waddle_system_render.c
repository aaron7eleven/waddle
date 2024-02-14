#include "waddle_system_render.h"
#include "waddle_component_transform.h"
#include "waddle_component_quad_renderer.h"
#include "waddle_component_quad_collider.h"

void update_render_system(SDL_Renderer* renderer, entity* entity)
{
	for (int comp_i = 0; comp_i < entity->component_count; comp_i++) {	
		if (entity->components[comp_i]->type == WADDLE_QUAD_RENDERER) {
			quad_renderer* q_rend = (quad_renderer*)entity->components[comp_i]->data;
			SDL_SetRenderDrawColor(renderer, q_rend->color.r, q_rend->color.g, q_rend->color.b, q_rend->color.a);
			transform* t = (transform*)get_component(entity, WADDLE_TRANSFORM);

			SDL_FRect render_rect = {
				t->position.x,
				t->position.y,
				q_rend->rect.w * t->scale.x,
				q_rend->rect.h * t->scale.y
			};

			SDL_RenderFillRectF(renderer, &render_rect);
		}
		else if (entity->components[comp_i]->type == WADDLE_QUAD_COLLIDER) {
			continue;
			quad_collider* q_collider = (quad_collider*)entity->components[comp_i]->data;
			SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
			transform* t = (transform*)get_component(entity, WADDLE_TRANSFORM);

			SDL_FRect render_rect = {
				t->position.x,
				t->position.y,
				q_collider->rect.w * t->scale.x,
				q_collider->rect.h * t->scale.y
			};

			SDL_RenderDrawRectF(renderer, &render_rect);
		}
	}
}
