#include <stdio.h>

#include <SDL_mixer.h>

#include "data/waddle_globals.h"
#include "entity/waddle_entity.h"
#include "system/waddle_system_resources.h"
#include "component/waddle_component_animated_sprite_renderer.h"
#include "component/waddle_component_clip_sprite_renderer.h"
#include "component/waddle_component_sprite_renderer.h"

int waddle_load_assets() {
	// Loop through each entity's component to load any assets it's components are pointing to
	entity* entity;
	int output = 0;
	for (int entity_i = 0; entity_i < entity_count; entity_i++) {
		entity = entities[entity_i];

		waddle_sprite_renderer* sprite_rend = (waddle_sprite_renderer*) get_component(entity, WADDLE_SPRITE_RENDERER);
		if (sprite_rend != NULL) {
			if (waddle_load_texture(renderer, sprite_rend->file, &sprite_rend->texture)) {
				printf("ERROR: failed to load texture on sprite renderer for %s", entity->name);
				output = 1;
			}
		}
		
		waddle_animated_sprite_renderer* anim_sprite_rend = (waddle_animated_sprite_renderer*) get_component(entity, WADDLE_ANIMATED_SPRITE_RENDERER);
		if (anim_sprite_rend != NULL) {
			if (waddle_load_texture(renderer, anim_sprite_rend->file, &anim_sprite_rend->texture)) {
				printf("ERROR: failed to load texture on animated sprite renderer for %s", entity->name);
				output = 1;
			}
		}

		waddle_clip_sprite_renderer* clip_sprite_rend = (waddle_clip_sprite_renderer*) get_component(entity, WADDLE_CLIP_SPRITE_RENDERER);
		if (clip_sprite_rend != NULL) {
			if (waddle_load_texture(renderer, clip_sprite_rend->file, &clip_sprite_rend->texture)) {
				printf("ERROR: failed to load texture on clip sprite renderer for %s", entity->name);
				output = 1;
			}
		}

		waddle_audio_player* audio_player = (waddle_audio_player*) get_component(entity, WADDLE_AUDIO_PLAYER);
		if (audio_player != NULL) {
			if (waddle_load_audio(audio_player)) {
				printf("ERROR: failed to load audio for %s", entity->name);
				output = 1;
			}
		}
		
		waddle_ui_text* ui_text = (waddle_ui_text*) get_component(entity, WADDLE_UI_TEXT);
		if (ui_text != NULL) {
			if (waddle_load_font(ui_text)) {
				printf("ERROR: failed to load font on ui text for %s", entity->name);
				output = 1;
			}
		}
	}
	return output;
}

WADDLE_API int waddle_load_audio(waddle_audio_player* audio_player) {
	switch (audio_player->type)
	{
	case WAV: {
		audio_player->clip = Mix_LoadWAV(audio_player->path);
		if (audio_player->clip == NULL) {
			printf("Failed to load %s! SDL_mixer Error: %s\n", audio_player->path, Mix_GetError());
			return 1;
		}
	} break;

	default:
		printf("Not loading audio. (OGG, MP3 are not supported yet)");
		break;
	}

	return 0;
}

WADDLE_API int waddle_load_font(waddle_ui_text* ui_text) {
	ui_text->font = TTF_OpenFont(ui_text->file, ui_text->point_size);
	if (ui_text->font == NULL) {
		printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
		return 1;
	}
	return 0;
}

WADDLE_API int waddle_load_texture(SDL_Renderer* renderer, const char* file, SDL_Texture** texture) {
	*(texture) = IMG_LoadTexture(renderer, file);
	if (*(texture) == NULL) {
		printf("ERROR: Failed to load texture: %s", file);
		return 1;
	}
	return 0;
}


