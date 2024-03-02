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

#define MAX_ENTITIES 32
#define MAX_COMPONENT_PER_ENTITY 16
#define MAX_COMPONENTS COMPONENT_COUNT

SDL_Window* window = NULL;
SDL_Surface* surface = NULL;
SDL_Renderer* renderer = NULL;

// states flags
int initialize = 0;
int restart = 0;
int quit = 0;

// window config
const char* window_title = "Waddle";
int screen_width = 1280;
int screen_height = 720;

// window settings
int fullscreen = 0;
int v_sync = 0;

// runtime time
float delta_time = 0.0f;
Uint32 start_ticks = 0;

// input
SDL_Event event; // use for window events and dynamic "event" input (i.e. SDL_Keycode)
const Uint8* key_state = 0; // use for key presses (i.e. SDL_SCANCODE_XXXX)

// entity & component info
int entity_count = 0;
entity* entities[MAX_ENTITIES];

#ifdef __cplusplus
}
#endif