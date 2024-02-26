#include "util/waddle_string.h"

char* waddle_int_to_string(int value) {
	char* text_buf = malloc(sizeof(char) * 16);
	sprintf(text_buf, "%d", value);
	return text_buf;
}