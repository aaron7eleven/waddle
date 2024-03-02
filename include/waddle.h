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
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

// entity
#include "entity/waddle_entity.h"

// component
#include "component/waddle_component.h"
#include "component/waddle_component_transform.h"
#include "component/waddle_component_quad_collider.h"
#include "component/waddle_component_quad_renderer.h"
#include "component/waddle_component_sprite_renderer.h"
#include "component/waddle_component_audio_player.h"
#include "component/waddle_component_ui_text.h"
#include "component/waddle_component_animation.h"
#include "component/waddle_component_animator.h"
#include "component/waddle_component_animated_sprite_renderer.h"
#include "component/waddle_component_clip_sprite_renderer.h"

// system
#include "system/waddle_system_physics.h"
#include "system/waddle_system_render.h"
#include "system/waddle_system_audio.h"
#include "system/waddle_system_resources.h"
#include "system/waddle_system_animation.h"

// util
#include "util/waddle_log.h"
#include "util/waddle_math.h"
#include "util/waddle_string.h"
//#include "util/waddle_window.h"


WADDLE_API int waddle_init();
WADDLE_API int waddle_run();
WADDLE_API int waddle_free();


// Game Loop
void waddle_update_delta_time();
void waddle_process_input();
void waddle_update();
void waddle_render();


int contains_collider(entity* entity);

int contains_renderer(entity* entity);


#ifdef __cplusplus
}
#endif