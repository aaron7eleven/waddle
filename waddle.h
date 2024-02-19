#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "waddle_include.h"
//#include "waddle_callback_test.h"

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

waddle* waddle_create();
int waddle_init(waddle* waddle);
int waddle_run(waddle* waddle);
int waddle_free(waddle* waddle);


// Game Loop
void waddle_process_input(waddle* waddle);
void waddle_update(waddle* waddle);
void waddle_physics_update(waddle* waddle);
void waddle_render(waddle* waddle);

void waddle_update_delta_time(waddle* waddle);
void waddle_apply_frame_delay(waddle* waddle);

entity* create_entity(waddle* waddle);
void destroy_entity(waddle* waddle, entity** entity);

void add_update_callback(waddle* waddle, waddle_update_callback callback);
//void free_entities(entity* entity);

int waddle_load_assets(waddle* waddle);


// Debug
void peek_entities(waddle* waddle);
void peek_entity(entity* entity);
