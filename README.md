# List
## A basic dynamic array system for C
### How to build
This library only contains 2 files, list.c and list.h, so compiling is stright forward. If you want, you can use the provided makefile by running the following commands in the project root.
```
mkdir build
make
```
A liblist.a file will be generated in the build directory.
### How to use
#### Instantiating
There are four default list types that are declared in list.h: ListInt, ListChar, ListDouble, and ListFloat. Use the list(type) maro in a typedef if you want to create your own list types.
```c
struct point {
	int x,y;
};

typedef list(struct point) ListPoint;
```
Instantiating lists is very simple, use the list_create function.
```c
ListPoint points = list_create(ListPoint, 10);

```
The above code creates a list of point structs that has an initial length of 10.

#### Modifying & Using
Currently there are four ways to modify a list, all of which can only change 1 index at a time.
```c
ListPoint points = list_create(ListPoint, 10);
struct point p1 = {1, 2};

// adds a point to the end of the list
list_push(&points, p1);

// removes the last index of a list
list_pop(&points);

// adds a point to the third index of the list
list_insert(&points, 3, p1);

// removes the point at index 7
list_splice(&points, 7);

// if you want to access the data in the list, you must use the data pointer
int x = points.data[5].x;
int y = points.data[5].y;
	
// the length attribute can be used to access the length of the list
int length = points.length;

// free the memory taken up by the list
list_free(&points);
```

### References
Here are some resources that helped me decide how to implement the library.
* https://github.com/rxi/vec
* https://stackoverflow.com/questions/60643222/how-to-solve-right-hand-operand-has-no-effect-error
* https://stuff.mit.edu/afs/athena/project/rhel-doc/3/rhel-cpp-en-3/macro-pitfalls.html
* https://stackoverflow.com/questions/3532621/using-and-returning-output-in-c-macro
* https://stackoverflow.com/questions/6966299/error-lvalue-required-in-this-simple-c-code-ternary-with-assignment
* https://stackoverflow.com/questions/10820340/the-need-for-parentheses-in-macros-in-c