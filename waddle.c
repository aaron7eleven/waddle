#pragma once
#include "waddle.h"
#include "waddle_time.h"

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

	while (!(waddle->quit)) {
		update_delta_time(waddle);
		process_input(waddle);
	}

	return 0;
}

void process_input(waddle* waddle) {
	waddle->key_state = SDL_GetKeyboardState(NULL);

	// Event Based Inputs (Handle events on queue)
	while (SDL_PollEvent(&waddle->event) != 0)
	{
		//User requests quit
		if (waddle->event.type == SDL_QUIT)
		{
			waddle_log("quitting\n");
			waddle->quit = 1;
		}
	}
}