#pragma once

#ifdef WADDLE_EXPORTS
#define WADDLE_API __declspec(dllexport)
#else
#define WADDLE_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	// Waddle
	WADDLE_TRANSFORM,
	WADDLE_QUAD_RENDERER,
	WADDLE_QUAD_COLLIDER,
	WADDLE_SPRITE_RENDERER,
	WADDLE_AUDIO_PLAYER,
	WADDLE_UI_TEXT,
	WADDLE_ANIMATION,
	WADDLE_ANIMATOR,
	WADDLE_ANIMATED_SPRITE_RENDERER,
	WADDLE_COMPONENT_COUNT,
} waddle_component_type;

#ifndef component_type
	typedef waddle_component_type component_type;
#endif

typedef struct {
	component_type type;
	void* data;
} component;

#ifdef __cplusplus
}
#endif