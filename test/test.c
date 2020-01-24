#include <stdio.h>
#include "../src/acvector.h"

typedef enum {
	PASSED,
	FAILED
} ASSERTION;

ASSERTION
test_meta() {
	acVector * test_vector = acvector_create(16, sizeof (int), 2);
	if (!test_vector) return FAILED;
	acvector_release(&test_vector);
	return PASSED;
}

ASSERTION
test_add() {
	int error = 0;
	int elements[3] = {1,2,3};
	acVector * test_vector = acvector_create(16, sizeof (int), 2);
	if ((error = acvector_push(&test_vector, elements))) return FAILED;
	if ((error = acvector_push_back(&test_vector, elements + 1))) return FAILED;
	if ((error = acvector_insert(&test_vector, 1, elements + 2))) return FAILED;
	acvector_release(&test_vector);

	return PASSED;
}

ASSERTION
test_read() {
	int * result;
	int elements[3] = {1,2,3};
	acVector * test_vector = acvector_create(16, sizeof (int), 2);
	acvector_push(&test_vector, elements);
	acvector_push_back(&test_vector, elements + 1);
	acvector_insert(&test_vector, 1, elements + 2);

	result = acvector_at(&test_vector, 0);
	if (*result != elements[0]) return FAILED;
	result = acvector_at(&test_vector, 1);
	if (*result != elements[2]) return FAILED;
	result = acvector_at(&test_vector, 2);
	if (*result != elements[1]) return FAILED;
	result = acvector_at(&test_vector, 3);
	if (result) return FAILED;

	acvector_release(&test_vector);

	return PASSED;
}

int
test(ASSERTION (*test_function)(), const char * name) {
	if (test_function() == PASSED) {
		printf("%s: \033[30;42mPASSED\033[0m\n", name);
		return 0;
	}
	else {
		printf("%s: \033[30;41mFAILED\033[0m\n", name);
		return 1;
	}

}

int
main() {
	printf("\n#### RUNNING TESTS ####\n\n");
	int error = 0;
	error += test(test_meta, "test_meta");	
	error += test(test_add, "test_add");	
	error += test(test_read, "test_read");	

	if (!error) {
		printf("\033[30;42mALL TESTS PASSED!\033[0m\n");
	} else {
		printf("\033[30;41m%d TESTS FAILED!\033[0m\n", error);
	}
	return error;
}
