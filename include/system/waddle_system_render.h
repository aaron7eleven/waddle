#pragma once

#ifdef WADDLE_EXPORTS
#define WADDLE_API __declspec(dllexport)
#else
#define WADDLE_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include "entity/waddle_entity.h"

WADDLE_API void update_render_system(entity* entity);

#ifdef __cplusplus
}
#endif