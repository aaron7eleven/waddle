#include "system/waddle_system_render.h"
#include "component/waddle_component_transform.h"
#include "component/waddle_component_quad_renderer.h"
#include "component/waddle_component_quad_collider.h"
#include "component/waddle_component_sprite_renderer.h"

void update_render_system(SDL_Renderer* renderer, entity* entity)
{
	for (int comp_i = 0; comp_i < entity->component_count; comp_i++) {
		switch (entity->components[comp_i]->type)
		{
		case WADDLE_QUAD_RENDERER: {
			waddle_transform* t = (waddle_transform*) get_component(entity, WADDLE_TRANSFORM);
			if (t == NULL) {
				printf("%s's sprite renderer doesn't have a transform\n", entity->name);
				break;
			}

			waddle_quad_renderer* q_rend = (waddle_quad_renderer*)entity->components[comp_i]->data;
			SDL_FRect render_rect = {
				t->position.x,
				t->position.y,
				q_rend->size.x * t->scale.x,
				q_rend->size.y * t->scale.y
			};

			SDL_SetRenderDrawColor(renderer, q_rend->color.r, q_rend->color.g, q_rend->color.b, q_rend->color.a);
			SDL_RenderFillRectF(renderer, &render_rect);

			// Debug: Gives quad an outline to show where texture is supposed to be
			SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
			SDL_RenderDrawRectF(renderer, &render_rect);

		} break;

			case WADDLE_QUAD_COLLIDER: {
				continue;
				waddle_quad_collider* q_collider = (waddle_quad_collider*)entity->components[comp_i]->data;
				SDL_FRect render_rect = {
					q_collider->rect.x,
					q_collider->rect.y,
					q_collider->rect.w * q_collider->scale.x,
					q_collider->rect.h * q_collider->scale.y
				};

				SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
				SDL_RenderDrawRectF(renderer, &render_rect);
			} break;

		case WADDLE_SPRITE_RENDERER: {
			waddle_sprite_renderer* sprite_rend = (waddle_sprite_renderer*)entity->components[comp_i]->data;
			waddle_transform* t = (waddle_transform*)get_component(entity, WADDLE_TRANSFORM);

			if (t == NULL) {
				printf("%s's sprite renderer doesn't have a transform\n", entity->name);
				break;
			}

			SDL_FRect render_rect = {
				t->position.x,
				t->position.y,
				sprite_rend->size.x * t->scale.x,
				sprite_rend->size.y * t->scale.y
			};

			SDL_SetRenderDrawColor(renderer, sprite_rend->color.r, sprite_rend->color.g, sprite_rend->color.b, sprite_rend->color.a);
			SDL_RenderCopyF(renderer, sprite_rend->texture, NULL, &render_rect);

			// Debug: Gives sprite an outline to show where texture is supposed to be
			SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
			SDL_RenderDrawRectF(renderer, &render_rect);
		} break;

		default:
			break;
		}
	}
}