#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

/*
cast to char pointer because these functions don't need to access the 
data in the array, so assume it's pointing to characters
*/
int _list_expand(char **data, int *length, int *capacity, int type_size);
int _list_shrink(char **data, int *length, int *capacity, int type_size);

// creates an arbitrary type list struct
#define list(T)\
	struct { T *data; int length, capacity; }

// sets all values in list struct to 0
#define list_init(l)\
	memset(l, 0, sizeof(*(l)))

// frees the memory from the heap, sets all values in list struct to 0
#define list_free(l)\
	( free((l)->data), list_init(l) )

// get a pointer to each variable in the list struct, used as input to various functions
#define _list_unpack(l)\
	(char **) &(l)->data, &(l)->length, &(l)->capacity, sizeof(*(l)->data)

// returns the new length of the array, returns 0 on failure to reallocate memory
#define list_push(l, val)\
	( _list_expand(_list_unpack(l)) ? ((l)->data[(l)->length++] = (val), (l)->length) : 0 )

// returns the variable that was removed from the array, return 0 if the array is already of length 0
#define list_pop(l)\
	( (l)->length != 0 ? (_list_shrink(_list_unpack(l)), (l)->data[--(l)->length]) : 0 )

// predefined list types
typedef list(char) list_char;
typedef list(int) list_int;
typedef list(float) list_float;
typedef list(double) list_double;

#endif