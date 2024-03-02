#pragma once

#ifdef WADDLE_EXPORTS
#define WADDLE_API __declspec(dllexport)
#else
#define WADDLE_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct waddle_node waddle_node;

struct waddle_node {
	void* data;
	waddle_node* next;
};


#ifdef __cplusplus
}
#endif