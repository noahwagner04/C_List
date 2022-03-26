#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "list.h"

/*
if the new length exedes the allocated memory, double the allocated memories size
returns 0 on success, and -1 on failure to allocate memory
*/
int _list_expand(char **data, int *length, int *capacity, int type_size) {
	if (*length + 1 > *capacity) {
		void *temp;
		int new_capacity = *capacity == 0 ? 1 : *capacity * 2;
		temp = realloc(*data, new_capacity * type_size);
		if (temp == NULL) return -1;
		*data = temp;
		*capacity = new_capacity;
	}
	return 0;
}

/*
if the new length of the list is less than half of the allocated memory, halve the size of the allocated memory
returns 0 on success, and -1 on failure to allocate memory
*/
int _list_shrink(char **data, int *length, int *capacity, int type_size) {
	if (*length - 1 < *capacity / 2) {
		void *temp;
		int new_capacity = *capacity / 2;
		temp = realloc(*data, new_capacity * type_size);
		if (temp == NULL) return -1;
		*data = temp;
		*capacity = new_capacity;
	}
	return 0;
}

// shift the list 1 space to the right starting at the specified index, resize the list if neccessary
// return 0 if the resize was succesful, return -1 if the resize failed or if the index is out of range
int _list_insert(char **data, int *length, int *capacity, int type_size, int index) {
	int expand_result = _list_expand(data, length, capacity, type_size);
	if (expand_result == 0 || index > *length || index < 0) return -1;
	memmove (
	    *data + (index + 1) * type_size,
	    *data + index * type_size,
	    (*length - index) * type_size
	);
	return 0;
}

// shift the list 1 space to the left starting at the specified index, resize the list if neccessary
// return -1 if the index is out of range or 0 otherwise
int _list_splice(char **data, int *length, int *capacity, int type_size, int index) {
	_list_shrink(data, length, capacity, type_size);
	if ((index + 1) > *length || index < 0) return -1;
	memmove (
	    *data + (index * type_size),
	    *data + (index + 1) * type_size,
	    (*length - (index + 1)) * type_size
	);
	return 0;
}