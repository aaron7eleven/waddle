//#pragma once
//
//#ifdef WADDLE_EXPORTS
//#define WADDLE_API __declspec(dllexport)
//#else
//#define WADDLE_API __declspec(dllimport)
//#endif
//
//#ifdef __cplusplus
//extern "C" {
//#endif
//
//#include <stdio.h>
//
//typedef enum {
//	LOG,
//	WARNING,
//	ERROR,
//	FATAL
//} waddle_log_level;
//
//WADDLE_API void waddle_log_by_level(waddle_log_level log_level, const char* format, ...);
//WADDLE_API void waddle_log(const char* msg);
//WADDLE_API void waddle_log_warning(const char* msg);
//WADDLE_API void waddle_log_error(const char* msg);
//WADDLE_API void waddle_log_fatal(const char* msg);
//
//#ifdef __cplusplus
//}
//#endif