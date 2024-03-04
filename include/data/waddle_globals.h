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
#include "component/waddle_component.h"

#define MAX_ENTITIES 32
#define MAX_COMPONENT_PER_ENTITY 16
#define MAX_COMPONENTS COMPONENT_COUNT

WADDLE_API extern SDL_Window* window;
WADDLE_API extern SDL_Surface* surface;
WADDLE_API extern SDL_Renderer* renderer;

// states flags
WADDLE_API extern int initialize;
WADDLE_API extern int restart;
WADDLE_API extern int quit;

// window config
WADDLE_API extern const char* window_title;
WADDLE_API extern int screen_width;
WADDLE_API extern int screen_height;

// window settings
WADDLE_API extern int fullscreen;
WADDLE_API extern int v_sync;

// runtime time
WADDLE_API extern float delta_time;
WADDLE_API extern Uint32 start_ticks;

// input
WADDLE_API extern SDL_Event event; // use for window events and dynamic "event" input (i.e. SDL_Keycode)
WADDLE_API extern const Uint8* key_state; // use for key presses (i.e. SDL_SCANCODE_XXXX)

// entity & component info
WADDLE_API extern int entity_count;
WADDLE_API extern entity* entities[MAX_ENTITIES];

// component
WADDLE_API extern component* components[MAX_COMPONENTS][MAX_ENTITIES];

#ifdef __cplusplus
}
#endif