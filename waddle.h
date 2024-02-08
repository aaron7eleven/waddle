#pragma once
#include <SDL.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "waddle_log.h"

typedef struct {
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
	SDL_Event event;
	const Uint8* key_state;

} waddle;

//typedef waddle waddle;

int waddle_init(waddle* waddle);
int waddle_run(waddle* waddle);
int waddle_free(waddle* waddle);

void process_input(waddle* waddle);
