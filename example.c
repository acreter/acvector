#include "src/acvector.h"
#include <stdio.h>

typedef struct Point2D Point2D;
struct Point2D {
	int x;
	int y;
};

unsigned int array_of_points_length = 8;
Point2D array_of_points[] = {
	{0,0},
	{1,2},
	{3,4},
	{5,6},
	{7,8},
	{9,10},
	{11,12},
	{13,14},
};

int
main() {
	acVector* vector;
	Point2D* point_ptr;
	Point2D  point;

	/* we create a vector that can initially hold 4 elements of type Point2D */
	vector = acvector_create(4, sizeof(Point2D));

	/* we fill our vector.
	 * it will expand itself to be able to hold all elements */
	for (unsigned int i = 0; i < array_of_points_length; i += 1) {
		acvector_append(&vector, array_of_points + i);
		/* since the vector stores proper copys of the elements,
		 * we can add the same points multiple times */
		acvector_prepend(&vector, array_of_points + i);
	}

	/* "point_ptr" now points to the third element of the vector */
	point_ptr = acvector_get_at(&vector, 2);

	/* if we want to extract an element from the vector,
	 * we have to use the copy function instead */
	acvector_copy_element(&vector, &point, point_ptr);

	/* since we stored the element in "point" now,
	 * we can remove the third element without losing information */
	acvector_remove(&vector, 2, 1);

	/* "point_ptr" still points to the third element */
	printf("third point:\n(%2i,%2i)\n\n", point_ptr->x, point_ptr->y);
	printf("old third point:\n(%2i,%2i)\n\n", point.x, point.y);

	/* to print out the vector we will iterate over it */
	printf("current vector elements:\n");
	for (point_ptr = acvector_get_first(&vector);
			point_ptr <= (Point2D*) acvector_get_last(&vector);
			point_ptr += 1) {
		printf("(%2i,%2i)\n", point_ptr->x, point_ptr->y);
	}

	/* lastly we free the memory of the vector */
	acvector_destroy(&vector);
	return 0;
}
