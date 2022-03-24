#include <stdio.h>
#include <string.h>
#include "../include/list.h"

struct point {
	int x,y;
};

typedef list(struct point) ListPoint;

int main() {
	ListInt l = list_create(ListInt, 0);

	for (int i = 0; i < 20; ++i) {
		list_push(&l, i);
	}

	list_splice(&l, 4);

	list_pop(&l);
	list_pop(&l);
	list_pop(&l);

	printf("Int Array:\n [ ");
	for (int i = 0; i < l.length; ++i)
	{
		printf("%i, ", l.data[i]);
	}
	printf("]\n");


	ListPoint points= list_create(ListPoint, 10);

	struct point p1= {21, 21};

	for (int i = 0; i < 10; ++i) {
		points.data[i].x = i;
		points.data[i].y = i + 1;
	}

	list_splice(&points, 8);

	list_pop(&points);

	list_insert(&points, 6, p1);

	printf("Points Array:\n [ ");
	for (int i = 0; i < points.length; ++i)
	{
		printf("{%i, %i}, ", points.data[i].x, points.data[i].y);
	}
	printf("]\n");

	list_free(&l);
	list_free(&points);
	return 0;
}