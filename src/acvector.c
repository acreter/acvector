#include "acvector.h"

#include <string.h>
#include <stdlib.h>

#define INDEX_LAST(v) (v->nElements - 1)

inline int acvector_extend(acVector_p);
inline int acvector_resize(acVector_p, size_t);
inline void * acvector_at_nocheck(acVector_p, size_t);

int
acvector_init(acVector_p v, size_t limit, size_t element_size) {
	if(!v) return 1;

	v->data = malloc(limit * element_size);
	if(!v->data) return 1;

	v->limit = limit;
	v->nElements = 0;
	v->element_size = element_size;

	return 0;
}

void
acvector_release(acVector_p v) {
	free(v->data);
	v->data = NULL;

	return;
}

void *
acvector_at(acVector_p v, size_t index) {
	if(index >= v->nElements) return NULL;
	return acvector_at_nocheck(v, index);
}

int
acvector_push_back(acVector_p v, void * element) {
	return acvector_insert(v, v->nElements, element);
}

int
acvector_push(acVector_p v, void * element) {
	return acvector_insert(v, 0, element);
}

void *
acvector_pop_back(acVector_p v) {
	return acvector_remove(v, INDEX_LAST(v));
}

void *
acvector_pop(acVector_p v) {
	return acvector_remove(v, 0);
}

int
acvector_insert(acVector_p v, size_t index, void * element) {
	void * at_index;
	void * at_index_inc;

	if(index <= v->nElements) {
		if(!acvector_extend(v)) return 1;

		at_index = acvector_at_nocheck(v, index);
		at_index_inc = acvector_at_nocheck(v, index + 1);
		memmove(at_index_inc, at_index, (v->nElements - index) * v->element_size);
		memcpy(at_index, element, v->element_size);
		v->nElements += 1;
		return 0;
	}

	return 1;
}

void *
acvector_remove(acVector_p v, size_t index) {
	void * element;
	void * buffer;

	if((buffer = acvector_at(v, index))) {
		element = malloc(v->element_size);
		memcpy(element, buffer, v->element_size);
		memmove(buffer, buffer + v->element_size, (INDEX_LAST(v) - index) * v->element_size);
		v->nElements -= 1;
		return element;
	}

	return NULL;
}

void *
acvector_iterator(acVector_p v) {
	if(!(v->nElements)) return NULL;
	return acvector_at(v, 0);
}

void *
acvector_next(acVector_p v, void * current) {
	if(!current || (current - v->data) / v->element_size >= INDEX_LAST(v)) return NULL;

	return current + v->element_size;
}

void *
acvector_iterator_r(acVector_p v) {
	if(!(v->nElements)) return NULL;
	return acvector_at(v, INDEX_LAST(v));
}

void *
acvector_next_r(acVector_p v, void * current) {
	if(!current || current <= v->data) return NULL;

	return current - v->element_size;
}

size_t
acvector_size_bytes(acVector_p v) {
	return v->nElements * v->element_size;
}

int
acvector_trim(acVector_p v) {
	return acvector_resize(v, v->nElements);
}

inline int
acvector_extend(acVector_p v) {
	if(v->nElements < v->limit) return 1;
	return acvector_resize(v, v->limit * ACVECTOR_EXTEND_FACTOR);
}

inline int
acvector_resize(acVector_p v, size_t new_size) {
	if(v->nElements <= new_size) {
		void * new = realloc(v->data, new_size * v->element_size);
		if(new) {
			v->data = new;
			v->limit = new_size;
		} else {
			return 1;
		}
	}

	return 0;
}

inline void *
acvector_at_nocheck(acVector_p v, size_t index) {
	return v->data + index * v->element_size;
}
