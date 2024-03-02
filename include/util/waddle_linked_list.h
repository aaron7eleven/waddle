#pragma once

#ifdef WADDLE_EXPORTS
#define WADDLE_API __declspec(dllexport)
#else
#define WADDLE_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include "util/waddle_node.h"

typedef struct {
	waddle_node* head;
	int count;
} waddle_linked_list;

WADDLE_API int add_node(waddle_linked_list* ll, waddle_node* new_n);
WADDLE_API int remove_node(waddle_linked_list* ll, waddle_node* new_n);
//WADDLE_API int remove_node(waddle_linked_list* ll, waddle_node* new_n);

#ifdef __cplusplus
}
#endif