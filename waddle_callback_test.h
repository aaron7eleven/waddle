#pragma once

typedef struct waddle_data waddle_data;

typedef void (*waddle_callback)(waddle_data* waddle_data);

//typedef struct {
//	waddle_callback callbacks[8];
//} waddle_data;

struct waddle_data {
	waddle_callback callbacks[8];
};