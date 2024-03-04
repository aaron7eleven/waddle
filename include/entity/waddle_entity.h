#pragma once

#ifdef WADDLE_EXPORTS
#define WADDLE_API __declspec(dllexport)
#else
#define WADDLE_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include "component/waddle_component.h"

typedef struct {
	const char* name;
	int id;
	int component_count;
	//int max_component_per_entity;
	//component* components[16];
	int destroy;
} entity;

WADDLE_API entity* create_entity();
WADDLE_API void free_entity(entity** entity);
WADDLE_API void destroy_entity(entity* entity);

WADDLE_API void* get_component(entity* entity, component_type type);
WADDLE_API void add_component(entity* entity, component_type type, void* data);
WADDLE_API void* create_component(component_type type);
WADDLE_API void* create_component_by_size(size_t sizeof_size);
//WADDLE_API void destory_components(entity* entity);
//WADDLE_API void destory_component(entity* entity, component* );

// WADDLE_API void free_component(entity* entity, component_type type);
WADDLE_API void free_components(entity* entity);

#ifdef __cplusplus
}
#endif