#include <stdio.h>
#include "util/waddle_linked_list.h"

WADDLE_API int add_node(waddle_linked_list* ll, waddle_node* new_n) {
	waddle_node* n = ll->head;
	// find the last node
	while (n != NULL) {
		// not at end. go to next node
		n = n->next;
	}
	n = new_n;
	return 1;
}

WADDLE_API int remove_node(waddle_linked_list* ll, waddle_node* new_n) {
	waddle_node* n = ll->head;
	// find the last node
	while (n != NULL) {
		// not at end. go to next node
		n = n->next;
	}
	n = new_n;
	return 1;
}