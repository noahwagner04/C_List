#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

/*
cast to char pointer because these functions don't need to access the 
data in the array, so assume it's pointing to characters
*/
int _list_expand(char **data, int *length, int *capacity, int type_size);
int _list_shrink(char **data, int *length, int *capacity, int type_size);

int _list_insert(char **data, int *length, int *capacity, int type_size, int index);
int _list_splice(char **data, int *length, int *capacity, int type_size, int index);

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
		_list.length = (size) < 0 ? 0 : (size);\
		_list.data = malloc(_list.length * sizeof(*_list.data));\
		_list.capacity = _list.length * 2;\
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

// returns the variable that was removed from the array
#define list_pop(l)\
	( (l)->length > 0 ? (_list_shrink(_list_unpack(l)), (l)->data[--(l)->length]) : (l)->data[0] )

/*
inserts the given value at the given index, where index is less than or equal to the list's length
returns the new length of the array on success, and 0 on failure to expand the list or if index is out of range
*/
#define list_insert(l, index, val)\
	( _list_insert(_list_unpack(l), index) ? ((l)->data[index] = (val), ++(l)->length) : 0 )

/*
removes the value at the given index of the list
returns the new length of the array on success, and 0 if start is out of range
*/
#define list_splice(l, index)\
	( _list_splice(_list_unpack(l), index) ? --(l)->length : 0 )

// should probably add a clone function

// predefined list types
typedef list(char) ListChar;
typedef list(int) ListInt;
typedef list(float) ListFloat;
typedef list(double) ListDouble;

#endif