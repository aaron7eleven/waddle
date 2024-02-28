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

WADDLE_API void update_animation_system(entity* entities[], int entity_count);
WADDLE_API void change_animation_state(void* animation_state);
WADDLE_API void change_animation_state_by_name(const char* state_name);

#ifdef __cplusplus
}
#endif