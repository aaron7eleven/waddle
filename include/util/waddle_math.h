#pragma once
#include <SDL.h>

float distance_squared(float x1, float y1, float x2, float y2);
float magnitude(float x, float y);
//float magnitude(float x1, float y1, float x2, float y2);
void normalize(SDL_FPoint* point);