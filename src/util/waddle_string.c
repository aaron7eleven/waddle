#include <stdio.h>
#include <string.h>
#include "util/waddle_string.h"

char* waddle_int_to_string(int value) {
	char* text_buf = malloc(sizeof(char) * 16);
	sprintf_s(text_buf, 16, "%d", value);
	return text_buf;
}

WADDLE_API char* waddle_strcat(const char* a, const char* b) {
	size_t a_len = strlen(a);
	size_t b_len = strlen(b);

	size_t buf_size_in_bytes = (a_len + b_len + 1) * sizeof(char);
	char* buffer = (char*)malloc(buf_size_in_bytes); // +1 for the null terminator

	strcpy_s(buffer, buf_size_in_bytes, a);
	strcat_s(buffer, buf_size_in_bytes, b);
	return buffer;
}