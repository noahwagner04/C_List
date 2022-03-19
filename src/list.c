#include <stdlib.h>
#include <math.h>
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

// if the length of the array is less than half of the allocated memory, halve the size of the allocated memory
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

// set capacity to the nearest power of 2 to length that is greater than length
void _list_init_capacity(int length, int *capacity) {

	if(length == 0) {
		*capacity = 1;
		return;
	}

	int final_capacity = 1;
	int leading_zeros = 0;
	unsigned int length_bit_count = sizeof(length) * 8;

	while((unsigned int)length < pow(2, length_bit_count - 1)) {
		length <<= 1;
		leading_zeros++;
	}

	final_capacity <<= length_bit_count - leading_zeros;
	*capacity = final_capacity;
}
