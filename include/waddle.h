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

// system
#include "system/waddle_system_physics.h"
#include "system/waddle_system_render.h"

// util
#include "util/waddle_log.h"
#include "util/waddle_math.h"

typedef struct waddle waddle;

typedef void (*waddle_update_callback)(waddle* waddle);

struct waddle {
	SDL_Window* window;
	SDL_Surface* surface;
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	TTF_Font* font;

	// waddle run states
	int initialize;
	int restart;
	int quit;

	// window settings
	const char* window_title;
	int screen_width;
	int screen_height;
	int fullscreen;
	int v_sync;
	Uint32 target_fps;
	Uint32 ticks_per_frame; // 1000 ms / X frames
	//Uint32 ticks_per_frame = 1000 / target_fps; // 1000 ms / X frames

	// runtime
	float delta_time;
	Uint32 start_ticks;

	// input
	SDL_Event event; // use for window events and dynamic "event" input (i.e. SDL_Keycode)
	const Uint8* key_state; // use for key presses (i.e. SDL_SCANCODE_XXXX)

	int entity_count;
	int max_entities;
	entity* entities[16];
	int max_component_per_entity;

	int update_callback_count;
	int max_update_callback_count;
	waddle_update_callback update_callbacks[16];
};


//typedef void (*waddle_system_update_callback)(waddle* waddle);

WADDLE_API waddle* waddle_create();
WADDLE_API int waddle_init(waddle* waddle);
WADDLE_API int waddle_run(waddle* waddle);
WADDLE_API int waddle_free(waddle* waddle);


// Game Loop
WADDLE_API void waddle_process_input(waddle* waddle);
WADDLE_API void waddle_update(waddle* waddle);
WADDLE_API void waddle_physics_update(waddle* waddle);
WADDLE_API void waddle_render(waddle* waddle);

WADDLE_API void waddle_internal_update(waddle* waddle);

WADDLE_API void waddle_update_delta_time(waddle* waddle);
WADDLE_API void waddle_apply_frame_delay(waddle* waddle);

WADDLE_API entity* create_entity(waddle* waddle);
WADDLE_API void free_entity(waddle* waddle, entity** entity);

WADDLE_API void add_update_callback(waddle* waddle, waddle_update_callback callback);
//void free_entities(entity* entity);

WADDLE_API int waddle_load_assets(waddle* waddle);


// Debug
void peek_entities(waddle* waddle);
void peek_entity(entity* entity);

#ifdef __cplusplus
}
#endif