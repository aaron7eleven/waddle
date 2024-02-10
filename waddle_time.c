#include "waddle_time.h"

void waddle_update_delta_time(waddle* waddle) {
	waddle->delta_time = (SDL_GetTicks() - waddle->start_ticks) / 1000.0f;
	waddle->start_ticks = SDL_GetTicks();
}

void waddle_apply_frame_delay(waddle* waddle) {
	Uint32 current_frame_ticks = SDL_GetTicks() - waddle->start_ticks;
	if (current_frame_ticks < waddle->ticks_per_frame)
	{
		//Wait remaining time
		SDL_Delay(waddle->ticks_per_frame - current_frame_ticks);
	}
}