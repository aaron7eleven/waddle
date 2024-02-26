#include "system/waddle_system_audio.h"

WADDLE_API void play(waddle_audio_player* audio_player) {
	Mix_Volume(-1, volume_clamp(audio_player->volume));
	Mix_PlayChannel(-1, audio_player->clip, 0);
}

int volume_clamp(int volume) {
	if (volume > MIX_MAX_VOLUME) return MIX_MAX_VOLUME;
	if (volume < 0) return 0;
	return volume;
}