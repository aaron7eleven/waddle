#pragma once

#ifdef WADDLE_EXPORTS
#define WADDLE_API __declspec(dllexport)
#else
#define WADDLE_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

WADDLE_API void waddle_log(const char* msg);

#ifdef __cplusplus
}
#endif