#include <stdio.h>
#include "system/waddle_system_resources.h"

WADDLE_API int waddle_load_sprite(SDL_Renderer* renderer, waddle_sprite_renderer* sprite_renderer) {
	sprite_renderer->texture = IMG_LoadTexture(renderer, sprite_renderer->file);
	if (sprite_renderer->texture == NULL) {
		printf("ERROR: Failed to load asset: %s", sprite_renderer->file);
		return 1;
	}
	return 0;
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

WADDLE_API int waddle_load_animated_sprite(SDL_Renderer* renderer, waddle_animated_sprite_renderer* animated_sprite_renderer) {
	animated_sprite_renderer->texture = IMG_LoadTexture(renderer, animated_sprite_renderer->file);
	if (animated_sprite_renderer->texture == NULL) {
		printf("ERROR: Failed to load asset: %s", animated_sprite_renderer->file);
		return 1;
	}
	return 0;
}
