#include "acvector.h"
#include <stdlib.h>
#include <string.h>

/* meta */
acVector*
acvector_create(unsigned long l, unsigned int soe) {
	acVector* v = calloc(1, sizeof (acVector) + l * soe);
	if(v) {
		v->limit = l;
		v->number_of_elements = 0;
		v->size_of_element = soe;
		return v;
	}

	return 0;
}

void
acvector_destroy(acVector** v) {
	free(*v);
	*v = 0;
	return;
}

/* access */
void*
acvector_get_at(acVector** v, unsigned long i) {
	return (*v)->data + (*v)->size_of_element * i;
}

void*
acvector_get_first(acVector** v) {
	return (*v)->data;
}

void*
acvector_get_last(acVector** v) {
	return (*v)->data + (*v)->size_of_element * ((*v)->number_of_elements - 1);
}

void
acvector_copy_element(acVector** v, void* d, void* s) {
	memcpy(d, s, (*v)->size_of_element);
	return;
}

/* modifiers */
void
acvector_clear(acVector** v) {
	(*v)->number_of_elements = 0;
}

void
acvector_insert(acVector** v, unsigned long i, void* e, unsigned long n_elements) {
	while ((*v)->number_of_elements + n_elements >= (*v)->limit) {
		acVector* new = realloc(*v, sizeof (acVector) + (*v)->limit * (*v)->size_of_element * AC_EXTENSION_FACTOR);
		if (!new) return;
		new->limit *= AC_EXTENSION_FACTOR;
		*v = new;
	}

	memmove(acvector_get_at(v, i + n_elements),
			acvector_get_at(v, i),
			(*v)->size_of_element * ((*v)->number_of_elements - i));

	memcpy(acvector_get_at(v, i),
			e,
			(*v)->size_of_element * n_elements);

	(*v)->number_of_elements += n_elements;
	return;
}

void
acvector_remove(acVector** v, unsigned long i, unsigned long n_elements) {
	memmove(acvector_get_at(v, i),
			acvector_get_at(v, i + n_elements),
			(*v)->size_of_element * ((*v)->number_of_elements - i - n_elements));
	(*v)->number_of_elements -= n_elements;
	return;
}
