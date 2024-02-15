#pragma once
#include "waddle.h"

typedef struct {
	waddle* waddle;
	const char* name;
} game;


int game_init(game* game);
int game_run(game* game);
int game_free(game* game);
int game_main(int argc, char* argv[]);