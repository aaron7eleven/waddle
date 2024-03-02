#include <string.h>

#include "data/waddle_globals.h"
#include "system/waddle_system_animation.h"

WADDLE_API int add_animation_to_animator(waddle_animator* animator, waddle_animation* animation) {
	if ((animator->animation_count + 1) >= animator->max_animation_count) {
		printf("ERROR: animator has too reached limit of animations");
		return 0;
	}

	animator->animations[animator->animation_count] = animation;
	animator->animation_count++;
	return 1;
}

WADDLE_API int change_animation(waddle_animator* animator, const char* new_anim_name) {
	// find animation
	for (int i_anim = 0; i_anim < animator->animation_count; i_anim++) {
		if (strcmp(animator->animations[i_anim]->name, new_anim_name) == 0) {
			// Change to found animation
			animator->current_animation = animator->animations[i_anim];
			animator->current_frame = animator->animations[i_anim]->start_frame;
			animator->current_frame_count = 0;
			animator->frame_timer = 0.0f;
			return 1;
		}
	}

	return 0;
}

WADDLE_API void update_animation_system(entity* entity) {
	// update animator
	waddle_animator* animator = (waddle_animator*) get_component(entity, WADDLE_ANIMATOR);
	animator->frame_timer += delta_time;
	if (animator->frame_timer >= animator->current_animation->time_between_frames) {
		// move to next frame
		animator->frame_timer -= animator->current_animation->time_between_frames;
		if ((animator->current_frame_count + 1) == animator->current_animation->number_of_frames) {
			// loop back to beginning
			animator->current_frame_count = 0;
			animator->current_frame = animator->current_animation->start_frame;
		}
		else {
			// move to next frame of animation
			animator->current_frame_count++;
			// can't "add" SDL_Point's together. Do piecewise.
			animator->current_frame.x += animator->current_animation->frame_diff.x;
			animator->current_frame.y += animator->current_animation->frame_diff.y;
		}
	}
}

