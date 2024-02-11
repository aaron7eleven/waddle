#include <math.h>
#include "waddle_math.h"

float distance_squared(float x1, float y1, float x2, float y2) {
	float delta_x = x2 - x1;
	float delta_y = y2 - y1;
	return delta_x * delta_x + delta_y * delta_y;
}

float magnitude(float x, float y) {
	float dist_sqr = distance_squared(0.0f, 0.0f, x, y);
	return sqrtf(dist_sqr);
}

//float magnitude(float x1, float y1, float x2, float y2) {
//	float dist_sqr = distance_squared(x1, y1, x2, y2);
//	return sqrtf(dist_sqr);
//}

void normalize(SDL_FPoint* point) {
	float point_magn = magnitude(point->x, point->y);
	printf("point_magn = %f\n", point_magn);
	point->x /= point_magn;
	point->y /= point_magn;

	printf("point normalized = (%f,%f)\n", point->x, point->y);
}