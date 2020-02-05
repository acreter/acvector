#include "../src/acvector.h"
#include "../actest/src/actest.h"

#include <stdio.h>

char*
test_remove(void* data) {
	if (!data) return "acvector_create failed";
	acVector* test_vector = (acVector*) data;
	int* element;

	element = acvector_remove(&test_vector, 3);
	if (!element) return "acvector_remove failed";
	if (*element != 2) return "acvector_remove: wrong element removed";
	free(element);
	
	element = acvector_pop_back(&test_vector);
	if (!element) return "acvector_pop_back failed";
	if (*element != 3) return "acvector_pop_back: wrong element removed";
	free(element);

	element = acvector_pop(&test_vector);
	if (!element) return "acvector_pop failed";
	if (*element != -1) return "acvector_pop: wrong element removed";
	free(element);

	return 0;
}

char*
test_add(void* data) {
	if (!data) return "acvector_create failed";
	acVector* test_vector = (acVector*) data;
	int error;
	int elements[] = {4,5,6};

	error = acvector_insert(&test_vector, 2, elements);
	if (error) return "acvector_insert failed";
	if (((int*) test_vector->data)[2] != *elements) return "acvector_insert: wrong location";

	error = acvector_push(&test_vector, elements + 1);
	if (error) return "acvector_push failed";
	if (((int*) test_vector->data)[0] != elements[1]) return "acvector_push: wrong location";

	error = acvector_push_back(&test_vector, elements + 2);
	if (error) return "acvector_push_back failed";
	if (((int*) test_vector->data)[7] != elements[2]) return "acvector_push_back: wrong location";

	return 0;
}

char*
test_read(void* data) {
	if (!data) return "acvector_create failed";
	acVector* test_vector = (acVector*) data;
	int* result;

	result = acvector_at(&test_vector, 0);
	if (!result) return "acvector_at 1: got NULL pointer on valid input";
	if (*result != ((int*) test_vector->data)[0]) return "wrong output";

	result = acvector_at(&test_vector, 1);
	if (!result) return "acvector_at 2: got NULL pointer on valid input";
	if (*result != ((int*) test_vector->data)[1]) return "wrong output";

	result = acvector_at(&test_vector, 2);
	if (!result) return "acvector_at 3: got NULL pointer on valid input";
	if (*result != ((int*) test_vector->data)[2]) return "wrong output";

	result = acvector_at(&test_vector, 3);
	if (!result) return "acvector_at 4: got NULL pointer on valid input";
	if (*result != ((int*) test_vector->data)[3]) return "wrong output";

	return 0;
}

void*
prepare() {
	acVector * test_vector = acvector_create(16, sizeof (int), 2);

	if (!test_vector) return NULL;

	int* test_vector_data = (int*) test_vector->data;

	test_vector_data[0] = -1;
	test_vector_data[1] = 0;
	test_vector_data[2] = 1;
	test_vector_data[3] = 2;
	test_vector_data[4] = 3;

	test_vector->nElements = 5;

	return test_vector;
}

void
release(void* data) {
	acVector* test_vector = (acVector*) data;
	acvector_release(&test_vector);
	return;
}

int
main() {
	unsigned int number_of_tests = 3;

	unsigned short* test_results_failed_array;
	test_results_failed_array = actest_run_bulk(prepare, release, number_of_tests, test_read, test_add, test_remove);
	
	for (unsigned int i = 0; i < number_of_tests; ++i) {
		if (test_results_failed_array[i]) {
			free(test_results_failed_array);
			return 1;
		}
	}

	free(test_results_failed_array);

	return 0;
}
