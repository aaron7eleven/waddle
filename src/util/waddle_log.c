//#include <stdarg.h>
//#include "util/waddle_log.h"
//#include "util/waddle_string.h"
//
//WADDLE_API void waddle_log_by_level(waddle_log_level log_level, const char* format, ...) {
//	va_list args;
//	va_start(args, format);
//	
//	switch (log_level)
//	{
//	case LOG: {
//		vprintf("%s", waddle_strcat("WADDLE_LOG: ", format));
//	} break;
//
//	case WARNING: {
//		vprintf("%s", waddle_strcat("WADDLE_WARNING: ", format));
//	} break;
//
//	case ERROR: {
//		vprintf("%s", waddle_strcat("WADDLE_ERROR: ", format));
//	} break;
//
//	case FATAL: {
//		vprintf("%s", waddle_strcat("WADDLE_FATAL: ", format));
//	} break;
//
//	default:
//		vprintf("WADDLE_ERROR: Unknown log level in waddle_log_by_level");
//		break;
//	}
//
//	va_end(args);
//}
//
//WADDLE_API void waddle_log(const char* msg, ...) {
//	waddle_log_by_level(LOG, msg, ...);
//}
//
//WADDLE_API void waddle_log_warning(const char* msg) {
//	waddle_log_by_level(msg, WARNING);
//}
//
//WADDLE_API void waddle_log_error(const char* msg) {
//	waddle_log_by_level(msg, ERROR);
//}
//
//WADDLE_API void waddle_log_fatal(const char* msg) {
//	waddle_log_by_level(msg, FATAL);
//}