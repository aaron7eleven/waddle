#pragma once
#include <stdlib.h>
#include "waddle.h"
#include "waddle_time.h"
#include "waddle_entity.h"
#include "waddle_component.h"
#include "waddle_component_quad_renderer.h"
#include "waddle_component_transform.h"
#include "waddle_component_quad_collider.h"
#include "waddle_colliders.h"
#include "quad_controller.h"

#include "waddle_system_render.h"
#include "waddle_system_physics.h"


int waddle_init(waddle* waddle) {
	if (!waddle->initialize) {
		// https://www.gamedev.net/forums/topic/336190-possible-to-call-sdl_init-more-than-once/3187085/
		if (SDL_Init(SDL_INIT_EVERYTHING))
		{
			waddle_log("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
			return 1;
		}
	}

	// window config
	waddle->screen_width = 640;
	waddle->screen_height = 480;
	waddle->v_sync = 1;
	waddle->fullscreen = 0;

	//Create window
	Uint32 window_flags = SDL_WINDOW_SHOWN;
	window_flags = waddle->fullscreen ? window_flags | SDL_WINDOW_FULLSCREEN : window_flags;
	waddle->window = SDL_CreateWindow("Waddle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, waddle->screen_width, waddle->screen_height, window_flags);
	if (waddle->window == NULL)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return 1;
	}

	// Create Renderer
	Uint32 render_flags = SDL_RENDERER_ACCELERATED;
	render_flags = waddle->v_sync ? render_flags | SDL_RENDERER_PRESENTVSYNC : render_flags;
	waddle->renderer = SDL_CreateRenderer(waddle->window, -1, render_flags);
	if (waddle->renderer == NULL) {
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		return 1;
	}

	//Get window surface
	waddle->surface = SDL_GetWindowSurface(waddle->window);

	//Initialize PNG loading
	int img_flags = IMG_INIT_PNG;
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
	//app->font = TTF_OpenFont("assets/font/DotGothic16-Regular.ttf", app->fontPointSize);
	//if (app->font == NULL) {
	//	printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
	//	return 1;
	//}

	//if (!waddle->initialize) {
	//	int mixer_flags = MIX_INIT_MP3 | MIX_INIT_OGG;
	//	if (!Mix_Init(mixer_flags)) {
	//		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
	//		return 1;
	//	}

	//	//Initialize SDL_mixer
	//	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	//	{
	//		printf("SDL_Mixer Open Audio could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
	//		return 1;
	//	}
	//}

	srand((unsigned)time(NULL));

	waddle->target_fps = 60;
	waddle->ticks_per_frame = 1000 / waddle->target_fps;
	waddle->start_ticks = SDL_GetTicks();

	waddle->quit = 0;
	waddle->restart = 0;
	waddle->initialize = 1;

	waddle->entity_count = 0;
	waddle->max_entities = 16;
	
	for (int entity_i = 0; entity_i < waddle->max_entities; entity_i++) {
		waddle->entities[entity_i] = NULL;
	}

	waddle->max_component_per_entity = 16;


	return 0;
}

int waddle_free(waddle* waddle) {
	//free(app->game);

	// Quit additional SDL subsystems

	//if (waddle->quit && !waddle->restart) {
	//	Mix_Quit();
	//}
	//Mix_Quit();
	TTF_Quit();
	IMG_Quit();

	SDL_FreeSurface(waddle->surface);
	waddle->surface = NULL;

	SDL_DestroyRenderer(waddle->renderer);
	waddle->renderer = NULL;

	SDL_DestroyWindow(waddle->window);
	waddle->window = NULL;

	//Quit SDL subsystems
	//SDL_Quit();
	if (waddle->quit && !waddle->restart) {
		SDL_Quit();
	}
	return 0;
}

int waddle_run(waddle* waddle) {

	entity* quad = create_entity(waddle);
	add_component(quad, TRANSFORM, &(transform) {
		{ 100.0f, 100.0f},
		{ 0.0f, 0.0f },
		{ 1.0f, 1.0f }
	});
	add_component(quad, QUAD_RENDERER, &(quad_renderer) {
		{ 100.0f, 100.0f, 50.0f, 50.0f },
		{ 0xDB, 0xE7, 0xC9, 0xFF }
	});
	add_component(quad, QUAD_CONTROLLER, &(quad_controller) {
		300.0f, 
		{ 0.0f, 0.0f }
	});
	add_component(quad, QUAD_COLLIDER, &(quad_collider) {
		{ 100.0f, 100.0f, 50.0f, 50.0f },
		DYNAMIC
	});

	entity* wall = create_entity(waddle);
	add_component(wall, TRANSFORM, &(transform) {
		{ 200.0f, 200.0f},
		{ 0.0f, 0.0f },
		{ 1.0f, 1.0f }
	});
	add_component(wall, QUAD_RENDERER, &(quad_renderer) {
		{ 50.0f, 50.0f, 100.0f, 100.0f },
		{ 0x78, 0x94, 0x61, 0xFF }
	});
	add_component(wall, QUAD_COLLIDER, &(quad_collider) {
		{ 100.0f, 100.0f, 100.0f, 100.0f },
		STATIC
	});


	while (!(waddle->quit)) {
		waddle_update_delta_time(waddle);
		waddle_process_input(waddle);
		waddle_update(waddle);
		waddle_update_physics(waddle);
		waddle_render(waddle);
	}

	return 0;
}

void waddle_process_input(waddle* waddle) {
	waddle->key_state = SDL_GetKeyboardState(NULL);

	// Event Based Inputs (Handle events on queue)
	while (SDL_PollEvent(&waddle->event) != 0)
	{
		//User requests quit
		if (waddle->event.type == SDL_QUIT)
		{
			waddle->quit = 1;
		}
	}
}

void waddle_update(waddle* waddle) {
	for (int entity_i = 0; entity_i < waddle->entity_count; entity_i++) {
		update_quad_controller(waddle->delta_time, waddle->key_state, waddle->entities[entity_i]);
	}
}

void waddle_update_physics(waddle* waddle) {
	update_physics_system(waddle->entities, waddle->entity_count);
}


void waddle_render(waddle* waddle) {
	SDL_SetRenderDrawColor(waddle->renderer, 0x50, 0x60, 0x3A, 0xFF);
	SDL_RenderClear(waddle->renderer);
	for (int entity_i = 0; entity_i < waddle->entity_count; entity_i++) {
		update_render_system(waddle->renderer, waddle->entities[entity_i]);
	}
	SDL_RenderPresent(waddle->renderer);
}

entity* create_entity(waddle* waddle)
{
	if ((waddle->entity_count + 1) >= waddle->max_entities) {
		printf("ERROR: At max entity count, not creating entity");
		return NULL;
	}

	entity* new_entity = malloc(sizeof(entity));
	new_entity->id = waddle->entity_count;
	new_entity->component_count = 0;
	new_entity->max_component_per_entity = waddle->max_component_per_entity;

	for (int comp_i = 0; comp_i < waddle->max_component_per_entity; comp_i++) {
		new_entity->components[comp_i] = NULL;
	}

	waddle->entities[waddle->entity_count] = new_entity;
	waddle->entity_count++;

	return new_entity;
}