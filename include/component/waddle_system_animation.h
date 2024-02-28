#pragma once

#ifdef WADDLE_EXPORTS
#define WADDLE_API __declspec(dllexport)
#else
#define WADDLE_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include <SDL.h>
#include "entity/waddle_entity.h"
#include "component/waddle_component_animation.h"
#include "component/waddle_component_animator.h"

WADDLE_API int add_animation_to_animator(waddle_animator* animator, waddle_animation* animation);
WADDLE_API int change_animation(waddle_animator* animator, const char* new_anim_name);
WADDLE_API void update_animation_system(entity* entities[], int entity_count, float delta_time);

#ifdef __cplusplus
}
#endif