#pragma once

#ifdef WADDLE_EXPORTS
#define WADDLE_API __declspec(dllexport)
#else
#define WADDLE_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

WADDLE_API char* waddle_int_to_string(int value);
WADDLE_API char* waddle_strcat(const char* a, const char* b);

#ifdef __cplusplus
}
#endif