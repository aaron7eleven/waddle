#include "util/waddle_log.h"
#include "util/waddle_string.h"

void waddle_log(const char* msg,...) {
	printf(msg);
}

WADDLE_API void waddle_log_by_level(const char* msg, waddle_log_level log_level) {
	switch (log_level)
	{
	case LOG: {
		printf("%s", waddle_strcat("WADDLE_LOG: ", msg));
	} break;

	case WARNING: {
		printf("%s", waddle_strcat("WADDLE_WARNING: ", msg));
	} break;

	case ERROR: {
		printf("%s", waddle_strcat("WADDLE_ERROR: ", msg));
	} break;

	case FATAL: {
		printf("%s", waddle_strcat("WADDLE_FATAL: ", msg));
	} break;

	default:
		break;
	}
}

WADDLE_API void waddle_log(const char* msg) {
	waddle_log_by_level(msg, LOG);
}

WADDLE_API void waddle_log_warning(const char* msg) {
	waddle_log_by_level(msg, WARNING);
}

WADDLE_API void waddle_log_error(const char* msg) {
	waddle_log_by_level(msg, ERROR);
}

WADDLE_API void waddle_log_fatal(const char* msg) {
	waddle_log_by_level(msg, FATAL);
}