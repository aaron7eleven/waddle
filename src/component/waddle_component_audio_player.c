#include <stdio.h>
#include "component/waddle_component_audio_player.h"

int waddle_load_audio(waddle_audio_player* audio_player) {
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

void play(waddle_audio_player* audio_player) {
	//printf("playing audio\n");
	Mix_Volume(-1, volume_clamp(audio_player->volume));
	Mix_PlayChannel(-1, audio_player->clip, 0);
}

int volume_clamp(int volume) {
	if (volume > MIX_MAX_VOLUME) return MIX_MAX_VOLUME;
	if (volume < 0) return 0;
	return volume;
}