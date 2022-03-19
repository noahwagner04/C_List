#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

/*
cast to char pointer because these functions don't need to access the 
data in the array, so assume it's pointing to characters
*/
int _list_expand(char **data, int *length, int *capacity, int type_size);
int _list_shrink(char **data, int *length, int *capacity, int type_size);

void _list_init_capacity(int length, int *capacity);

// creates an arbitrary type list struct
#define list(t)\
	struct { t *data; int length, capacity; }

// sets all values in list struct to 0
#define _list_set_empty(l)\
	memset(l, 0, sizeof(*(l)))

// creates a list struct with the correct length and capacity
#define list_create(lt, size)\
	({\
		lt _list;\
		_list_set_empty(&_list);\
		_list.length = (size);\
		_list.data = malloc((size) * sizeof(*_list.data));\
		_list_init_capacity(_list.length, &_list.capacity);\
		_list;\
	})

// frees the memory from the heap, sets all values in list struct to 0
#define list_free(l)\
	( free((l)->data), _list_set_empty(l) )

// get a pointer to each variable in the list struct, used as input to various functions
#define _list_unpack(l)\
	(char **) &(l)->data, &(l)->length, &(l)->capacity, sizeof(*(l)->data)

// returns the new length of the array, returns 0 on failure to reallocate memory
#define list_push(l, val)\
	( _list_expand(_list_unpack(l)) ? ((l)->data[(l)->length++] = (val), (l)->length) : 0 )

// returns the variable that was removed from the array, return 0 if the array is already of length 0
#define list_pop(l)\
	( (l)->length > 0 ? (_list_shrink(_list_unpack(l)), (l)->data[--(l)->length]) : (l)->data[(l)->length] )

// predefined list types
typedef list(char) list_char;
typedef list(int) list_int;
typedef list(float) list_float;
typedef list(double) list_double;

#endif