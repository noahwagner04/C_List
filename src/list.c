#include <stdlib.h>
#include "list.h"

// if the new length exedes the allocated memory, double the allocated memories size
int _list_expand(char **data, int *length, int *capacity, int type_size) {
	if(*length + 1 > *capacity) {
		void *temp;
		int new_capacity = *capacity == 0 ? 1 : *capacity * 2;
		temp = realloc(*data, new_capacity * type_size);
		if(temp == NULL) return 0;
		*data = temp;
		*capacity = new_capacity;
	}
	return 1;
}

int _list_shrink(char **data, int *length, int *capacity, int type_size) {
	if(*length - 1 < *capacity / 2) {
		void *temp;
		int new_capacity = *capacity / 2;
		temp = realloc(*data, new_capacity * type_size);
		if(temp == NULL) return 0;
		*data = temp;
		*capacity = new_capacity;
	}
	return 1;
}