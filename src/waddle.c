#pragma once
#include "waddle.h"

waddle* waddle_create() {
	waddle* w = (waddle*) calloc(1, sizeof(waddle));
	w->window_title = "Waddle";
	return w;
}

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
	waddle->screen_width = 1280;
	waddle->screen_height = 720;
	waddle->v_sync = 0;
	waddle->fullscreen = 0;

	//Create window
	Uint32 window_flags = SDL_WINDOW_SHOWN;
	window_flags = waddle->fullscreen ? window_flags | SDL_WINDOW_FULLSCREEN : window_flags;

	waddle->window = SDL_CreateWindow(waddle->window_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, waddle->screen_width, waddle->screen_height, window_flags);
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
	int img_flags = IMG_INIT_PNG | IMG_INIT_JPG;
	if (!(IMG_Init(img_flags) & img_flags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return 1;
	}

	// Load text library
	//if (TTF_Init() == -1) {
	//	printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
	//	return 1;
	//}

	//// Load Font
	//app->font = TTF_OpenFont("assets/font/DotGothic16-Regular.ttf", app->fontPointSize);
	//if (app->font == NULL) {
	//	printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
	//	return 1;
	//}

	if (!waddle->initialize) {
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

	waddle->target_fps = 60;
	waddle->ticks_per_frame = 1000 / waddle->target_fps;
	waddle->start_ticks = SDL_GetTicks();

	waddle->entity_count = 0;
	waddle->max_entities = 16;
	
	for (int entity_i = 0; entity_i < waddle->max_entities; entity_i++) {
		waddle->entities[entity_i] = NULL;
	}

	waddle->max_component_per_entity = 16;

	waddle->update_callback_count = 0;
	waddle->max_update_callback_count = 16;

	for (int update_cb_i = 0; update_cb_i < waddle->max_update_callback_count; update_cb_i++) {
		waddle->update_callbacks[update_cb_i] = NULL;
	}

	waddle->quit = 0;
	waddle->restart = 0;
	waddle->initialize = 1;

	return 0;
}

int waddle_free(waddle* waddle) {
	//free(app->game);

	// Quit additional SDL subsystems

	if (waddle->quit && !waddle->restart) {
		Mix_Quit();
	}
	//Mix_Quit();
	//TTF_Quit();
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

int waddle_load_assets(waddle* waddle) {
	// Loop through each entity's component to load any assets it's components are pointing to
	entity* entity;
	int output = 0;
	for (int entity_i = 0; entity_i < waddle->entity_count; entity_i++) {
		entity = waddle->entities[entity_i];
		for (int comp_i = 0; comp_i < entity->component_count; comp_i++) {
			
			switch (entity->components[comp_i]->type) {
				case WADDLE_SPRITE_RENDERER: {
					waddle_sprite_renderer* sprite_rend = (waddle_sprite_renderer*)entity->components[comp_i]->data;
					if (waddle_load_sprite(waddle->renderer, sprite_rend)) {
						printf("ERROR: failed to load sprite for %s", entity->name);
						output = 1;
					}
				} break;

				case WADDLE_AUDIO_PLAYER: {
					waddle_audio_player* audio_player = (waddle_audio_player*) entity->components[comp_i]->data;
					if (waddle_load_audio(audio_player)) {
						printf("ERROR: failed to load audio for %s", entity->name);
						output = 1;
					}
				} break;

				default: {

				} break;
			}
		}
	}
	return output;
}

int waddle_run(waddle* waddle) {
	while (!waddle->quit && !waddle->restart)
	{
		waddle_update_delta_time(waddle);
		waddle_process_input(waddle);
		waddle_update(waddle);
		waddle_physics_update(waddle);
		waddle_internal_update(waddle);
		waddle_render(waddle);
	}

	return !waddle->quit && !waddle->restart;
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
	for (int callback_i = 0; callback_i < waddle->update_callback_count; callback_i++) {
		waddle->update_callbacks[callback_i](waddle);
	}
}


void waddle_physics_update(waddle* waddle) {
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

void waddle_internal_update(waddle* waddle) {
	for (int entity_i = 0; entity_i < waddle->entity_count; entity_i++) {
		if (waddle->entities[entity_i]->destroy) {
			free_entity(waddle, &(waddle->entities[entity_i]));
		}
	}
}

void waddle_update_delta_time(waddle* waddle) {
	waddle->delta_time = (SDL_GetTicks() - waddle->start_ticks) / 1000.0f;
	waddle->start_ticks = SDL_GetTicks();
}

void waddle_apply_frame_delay(waddle* waddle) {
	Uint32 current_frame_ticks = SDL_GetTicks() - waddle->start_ticks;
	if (current_frame_ticks < waddle->ticks_per_frame)
	{
		//Wait remaining time
		SDL_Delay(waddle->ticks_per_frame - current_frame_ticks);
	}
}

entity* create_entity(waddle* waddle)
{
	if ((waddle->entity_count + 1) >= waddle->max_entities) {
		printf("ERROR: At max entity count, not creating entity");
		return NULL;
	}

	entity* new_entity = malloc(sizeof(entity));
	new_entity->name = "entity";
	new_entity->id = waddle->entity_count;
	new_entity->component_count = 0;
	new_entity->destroy = 0;
	new_entity->max_component_per_entity = waddle->max_component_per_entity;

	for (int comp_i = 0; comp_i < waddle->max_component_per_entity; comp_i++) {
		new_entity->components[comp_i] = NULL;
	}

	int store_entity = 0;
	// find place to store entity in list
	for (int entity_i = 0; entity_i < waddle->max_entities; entity_i++) {

		if (waddle->entities[entity_i] == NULL) {
			waddle->entities[entity_i] = new_entity;
			store_entity = 1;
			break;
		}
	}

	if (!store_entity) {
		printf("WADDLE_ERROR: unable find place to store newly created entity");
		free(new_entity);
		return NULL;
	}

	//waddle->entities[waddle->entity_count] = new_entity;
	waddle->entity_count++;

	return new_entity;
}

void free_entity(waddle* waddle, entity** entity_ptr)
{
	if (entity_ptr == NULL) {
		printf("ERROR: passed in entity that is null\n");
		return;
	}
	
	entity* entity_to_destroy = *entity_ptr;
	if (entity_to_destroy == NULL) {
		printf("ERROR: trying to destroy entity which is null\n");
		return;
	}
	
	// Do I have to check if the entity exists in the list of entities? *hmm*
	//int destory_entity_i = -1;
	//for (int entity_i = 0; entity_i < waddle->entity_count; entity_i++) {
	//	if (waddle->entities[entity_i]->id == entity_to_destroy->id) {
	//		// found entity to destroy
	//		destory_entity_i = entity_i;
	//		break;
	//	}
	//}

	//if (destory_entity_i < 0) {
	//	printf("WADDLE_ERROR: unable to find entity to destroy\n");
	//	return;
	//}

	// Destroy entity
	free_components(entity_to_destroy);
	entity_to_destroy = NULL;
	free(*entity_ptr);
	*entity_ptr = NULL;

	// Restructure entities so there are no gaps
	for (int entity_i = 0; entity_i < waddle->entity_count; entity_i++) {
		// if current entity is not null, move to next
		if (waddle->entities[entity_i] != NULL) continue;

		// if current entity index is the last index, move on to the end loop
		if ((entity_i + 1) >= waddle->entity_count) continue;
		
		// if next entity is null, move to next (will be come current) (double check for sanity)
		if (waddle->entities[entity_i + 1] == NULL) continue;
		
		// Swap entity pointer (safely)
		entity* entity_tmp = waddle->entities[entity_i];
		waddle->entities[entity_i] = waddle->entities[entity_i + 1];
		waddle->entities[entity_i+1] = entity_tmp; // should be setting to null
	}

	waddle->entity_count--;
}

void add_update_callback(waddle* waddle, waddle_update_callback callback) {
	if ((waddle->update_callback_count + 1) >= waddle->max_update_callback_count) {
		printf("ERROR: At max update callback count, not adding callback\n");
		return;
	}

	waddle->update_callbacks[waddle->update_callback_count] = callback;
	waddle->update_callback_count++;
}

void peek_entities(waddle* waddle) {
	for (int entity_i = 0; entity_i < waddle->entity_count; entity_i++) {
		// stuff with entity
		peek_entity(waddle->entities[entity_i]);
	}
}

void peek_entity(entity* entity) {
	for (int comp_i = 0; comp_i < entity->component_count; comp_i++) {
		switch (entity->components[comp_i]->type)
		{
			// add statements to filter by component type
			case WADDLE_TRANSFORM: {
				waddle_transform* t = (waddle_transform*)get_component(entity, WADDLE_TRANSFORM);
				if (t == NULL) {
					printf("%s: no transform");
				}
			} break;

			case WADDLE_QUAD_RENDERER: {
				waddle_quad_renderer* quad_rend = (waddle_quad_renderer*)get_component(entity, WADDLE_QUAD_RENDERER);
				if (quad_rend == NULL) {
					printf("%s: no quad renderer");
				}
			} break;

			//case WADDLE_SPRITE_RENDERER: {
			//	sprite_renderer* sprite_rend = (sprite_renderer*)get_component(entity, WADDLE_SPRITE_RENDERER);
			//} break;

			default: {
				//printf("component not peekable - id = %d\n", entity->components[comp_i]->type);
			} break;
		}
	}
}
