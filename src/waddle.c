#pragma once
#include <stdio.h>

#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "waddle.h"
#include "data/waddle_globals.h"
#include "component/waddle_component_transform.h"

int waddle_init() {
	if (!initialize) {
		// https://www.gamedev.net/forums/topic/336190-possible-to-call-sdl_init-more-than-once/3187085/
		if (SDL_Init(SDL_INIT_EVERYTHING))
		{
			printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
			return 1;
		}
	}

	//Create window
	Uint32 window_flags = SDL_WINDOW_SHOWN;
	window_flags = fullscreen ? window_flags | SDL_WINDOW_FULLSCREEN : window_flags;

	window = SDL_CreateWindow(window_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, window_flags);
	if (window == NULL)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return 1;
	}

	// Create Renderer
	Uint32 render_flags = SDL_RENDERER_ACCELERATED;
	render_flags = v_sync ? render_flags | SDL_RENDERER_PRESENTVSYNC : render_flags;
	renderer = SDL_CreateRenderer(window, -1, render_flags);
	if (renderer == NULL) {
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		return 1;
	}

	//Get window surface
	surface = SDL_GetWindowSurface(window);

	//Initialize PNG loading
	int img_flags = IMG_INIT_PNG | IMG_INIT_JPG;
	if (!(IMG_Init(img_flags) & img_flags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return 1;
	}

	// Load text library
	if (TTF_Init() == -1) {
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		return 1;
	}

	//// Load Font
	//appfont = TTF_OpenFont("assets/font/DotGothic16-Regular.ttf", appfontPointSize);
	//if (appfont == NULL) {
	//	printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
	//	return 1;
	//}

	if (!initialize) {
		int mixer_flags = MIX_INIT_MP3 | MIX_INIT_OGG;
		if (!Mix_Init(mixer_flags)) {
			printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
			return 1;
		}

		//Initialize SDL_mixer
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			printf("SDL_Mixer Open Audio could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
			return 1;
		}
	}

	srand((unsigned)time(NULL));

	start_ticks = SDL_GetTicks();
	
	for (int entity_i = 0; entity_i < MAX_ENTITIES; entity_i++) {
		entities[entity_i] = NULL;
	}

	initialize = 1;

	return 0;
}

int waddle_free() {
	//free(appgame);

	// Quit additional SDL subsystems
	if (quit && !restart) {
		Mix_Quit();
	}

	TTF_Quit();
	IMG_Quit();

	SDL_FreeSurface(surface);
	surface = NULL;

	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	SDL_DestroyWindow(window);
	window = NULL;

	//Quit SDL subsystems
	if (quit && !restart) {
		SDL_Quit();
	}
	return 0;
}

void waddle_update_delta_time() {
	delta_time = (SDL_GetTicks() - start_ticks) / 1000.0f;
	start_ticks = SDL_GetTicks();
}

int waddle_run() {
	while (!quit && !restart)
	{
		waddle_update_delta_time();
		waddle_process_input();
		waddle_update();
		waddle_render();
	}

	return !quit && !restart;
}

void waddle_process_input() {
	key_state = SDL_GetKeyboardState(NULL);

	// Event Based Inputs (Handle events on queue)
	while (SDL_PollEvent(&event) != 0)
	{
		//User requests quit
		if (event.type == SDL_QUIT)
		{
			quit = 1;
		}
	}
}


void waddle_update() {
	for (int entity_i = 0; entity_i < entity_count; entity_i++) {
		waddle_transform* entity_transform = (waddle_transform*) get_component(entities[entity_i], WADDLE_TRANSFORM);

		if (contains_collider(entities[entity_i]) && (entity_transform != NULL)) {
			update_physics_system(entities[entity_i]);
		}

		// internal update
		if (entities[entity_i]->destroy) {
			free_entity(&(entities[entity_i]));
			continue; // don't need to continue processing if going to be destoryed
		}

		if (get_component(entities[entity_i], WADDLE_ANIMATOR)) {
			//update_animation_system(entities[entity_i]);
			update_animation_system(entities[entity_i]);
		}
	}
}

void waddle_render() {
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(renderer);
	for (int entity_i = 0; entity_i < entity_count; entity_i++) {
		waddle_transform* entity_transform = (waddle_transform*)get_component(entities[entity_i], WADDLE_TRANSFORM);

		// Non-UI
		if (contains_renderer(entities[entity_i]) && (entity_transform != NULL)) {
			update_render_system(entities[entity_i]);
		}

		// UI
		if (get_component(entities[entity_i], WADDLE_UI_TEXT) != NULL) {
			update_render_system(entities[entity_i]);
		}

	}
	SDL_RenderPresent(renderer);
}

int contains_collider(entity* entity) {

	if (get_component(entity, WADDLE_QUAD_COLLIDER)) {
		return 1;
	}

	return 0;
}

int contains_renderer(entity* entity) {	
	if (get_component(entity, WADDLE_SPRITE_RENDERER)) {
		return 1;
	}

	if (get_component(entity, WADDLE_CLIP_SPRITE_RENDERER)) {
		return 1;
	}

	if (get_component(entity, WADDLE_ANIMATED_SPRITE_RENDERER)) {
		return 1;
	}

	return 0;
}
