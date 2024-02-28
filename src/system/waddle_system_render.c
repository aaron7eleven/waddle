#include "system/waddle_system_render.h"
#include "component/waddle_component_transform.h"
#include "component/waddle_component_quad_renderer.h"
#include "component/waddle_component_quad_collider.h"
#include "component/waddle_component_sprite_renderer.h"
#include "component/waddle_component_ui_text.h"
#include "component/waddle_component_animated_sprite_renderer.h"
#include "component/waddle_component_animator.h"

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

		case WADDLE_ANIMATED_SPRITE_RENDERER: {
			waddle_animated_sprite_renderer* anim_sprite_rend = (waddle_animated_sprite_renderer*)entity->components[comp_i]->data;
			waddle_transform* t = (waddle_transform*)get_component(entity, WADDLE_TRANSFORM);
			waddle_animator* animator = (waddle_transform*)get_component(entity, WADDLE_ANIMATOR);

			if (t == NULL) {
				printf("%s's animated sprite renderer doesn't have a transform\n", entity->name);
				break;
			}

			if (animator == NULL) {
				printf("%s's animated sprite renderer doesn't have a animator\n", entity->name);
				break;
			}

			SDL_FRect src_rect = {
				animator->current_frame.x,
				animator->current_frame.y,
				anim_sprite_rend->frame_size.x,
				anim_sprite_rend->frame_size.y
			};

			SDL_FRect render_rect = {
				t->position.x,
				t->position.y,
				anim_sprite_rend->frame_size.x * t->scale.x,
				anim_sprite_rend->frame_size.y * t->scale.y
			};


			SDL_SetRenderDrawColor(renderer, anim_sprite_rend->color.r, anim_sprite_rend->color.g, anim_sprite_rend->color.b, anim_sprite_rend->color.a);
			SDL_RenderCopyF(renderer, anim_sprite_rend->texture, &src_rect, &render_rect);

			// Debug: Gives sprite an outline to show where texture is supposed to be
			SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
			SDL_RenderDrawRectF(renderer, &render_rect);
		} break;


		case WADDLE_UI_TEXT: {
			waddle_ui_text* ui_text = (waddle_ui_text*) entity->components[comp_i]->data;

			SDL_Surface* text_surface = TTF_RenderText_Solid(ui_text->font, ui_text->text, ui_text->color);
			if (text_surface == NULL) {
				printf("Unable to render ui text surface (%s)! SDL_TTF Error: %s\n", ui_text->text, TTF_GetError());
				break;
			}
			
			SDL_Texture* ui_text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
			if (ui_text_texture == NULL) {
				printf("Unable to create ui text texture from %s! SDL Error: %s\n", ui_text->text, SDL_GetError());
				break;
			}

			SDL_RenderCopyExF(renderer, ui_text_texture, NULL, &ui_text->rect, 0, NULL, SDL_FLIP_NONE);
			SDL_FreeSurface(text_surface);
			SDL_DestroyTexture(ui_text_texture);

			// Debug: Gives outline to show it supposed to be rendering
			SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0xFF, 0xFF);
			SDL_RenderDrawRectF(renderer, &ui_text->rect);
		} break;

		default:
			break;
		}
	}
}