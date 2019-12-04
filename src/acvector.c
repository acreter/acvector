#include "acvector.h"

#include <string.h>
#include <stdlib.h>

#define INDEX_LAST(v) (v->nElements - 1)

char acvector_extend(Vector_p);
char acvector_resize(Vector_p, size_t);
void * acvector_at_nocheck(Vector_p, size_t);

Vector_p
acvector_init(size_t limit, size_t element_size) {
	Vector_p v = malloc(sizeof(Vector));
	if(!v) return NULL;

	v->data = malloc(limit * element_size);
	if(!v->data) {
		free(v);
		return NULL;
	}

	v->limit = limit;
	v->nElements = 0;
	v->element_size = element_size;

	return v;
}

void
acvector_release(Vector_p v) {
	free(v->data);
	v->data = NULL;
	free(v);

	return;
}

void *
acvector_at(Vector_p v, size_t index) {
	if(index >= v->nElements) return NULL;
	return v->data + index * v->element_size;
}

char
acvector_push_back(Vector_p v, void * element) {
	return acvector_insert(v, v->nElements, element);
}

char
acvector_push(Vector_p v, void * element) {
	return acvector_insert(v, 0, element);
}

void *
acvector_pop_back(Vector_p v) {
	return acvector_remove(v, INDEX_LAST(v));
}

void *
acvector_pop(Vector_p v) {
	return acvector_remove(v, 0);
}

char
acvector_insert(Vector_p v, size_t index, void * element) {
	void * at_index;
	void * at_index_inc;

	if(index <= v->nElements) {
		if(!acvector_extend(v)) return 0;

		at_index = acvector_at_nocheck(v, index);
		at_index_inc = acvector_at_nocheck(v, index + 1);
		memmove(at_index_inc, at_index, (v->nElements - index) * v->element_size);
		memcpy(at_index, element, v->element_size);
		v->nElements += 1;
		return 1;
	}

	return 0;
}

void *
acvector_remove(Vector_p v, size_t index) {
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
acvector_iterator(Vector_p v) {
	if(!(v->nElements)) return NULL;
	return acvector_at(v, 0);
}

void *
acvector_next(Vector_p v, void * current) {
	if(!current || (current - v->data) / v->element_size >= INDEX_LAST(v)) return NULL;

	return current + v->element_size;
}

void *
acvector_iterator_r(Vector_p v) {
	if(!(v->nElements)) return NULL;
	return acvector_at(v, INDEX_LAST(v));
}

void *
acvector_next_r(Vector_p v, void * current) {
	if(!current || current <= v->data) return NULL;

	return current - v->element_size;
}

size_t
acvector_size_bytes(Vector_p v) {
	return v->nElements * v->element_size;
}

char
acvector_trim(Vector_p v) {
	return acvector_resize(v, v->nElements);
}

char
acvector_extend(Vector_p v) {
	if(v->nElements < v->limit) return 1;
	return acvector_resize(v, v->limit * VECTOR_EXTEND_FACTOR);
}

char
acvector_resize(Vector_p v, size_t new_size) {
	if(v->nElements <= new_size) {
		void * new = realloc(v->data, new_size * v->element_size);
		if(new) {
			v->data = new;
			v->limit = new_size;
		} else {
			return 0;
		}
	}

	return 1;
}

void *
acvector_at_nocheck(Vector_p v, size_t index) {
	return v->data + index * v->element_size;
}
