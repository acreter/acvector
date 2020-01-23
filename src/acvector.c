#include "acvector.h"

#include <string.h>
#include <stdlib.h>

struct acVector {
	unsigned long limit, nElements;
	unsigned int element_size;
	unsigned char extension_factor;
	unsigned char data[1];
};

#define INDEX_LAST(v) (v->nElements - 1)

inline int acvector_extend(acVector *);
inline int acvector_resize(acVector *, unsigned long);
inline void * acvector_at_nocheck(acVector *, unsigned long);

acVector *
acvector_create(unsigned long limit, unsigned int element_size, unsigned char extension_factor) {
	acVector * vector;
	vector = malloc((sizeof *vector) + sizeof (unsigned char) * element_size * (limit -1));
	if(!vector) return NULL;

	vector->limit = limit;
	vector->nElements = 0;
	vector->element_size = element_size;

	return vector;
}

void
acvector_release(acVector * v) {
	free(v);

	return;
}

void *
acvector_at(acVector * v, unsigned long index) {
	if(index >= v->nElements) return NULL;
	return v->data + index * v->element_size;
}

int
acvector_push_back(acVector * v, void * element) {
	return acvector_insert(v, v->nElements, element);
}

int
acvector_push(acVector * v, void * element) {
	return acvector_insert(v, 0, element);
}

void *
acvector_pop_back(acVector * v) {
	return acvector_remove(v, INDEX_LAST(v));
}

void *
acvector_pop(acVector * v) {
	return acvector_remove(v, 0);
}

int
acvector_insert(acVector * v, unsigned long index, void * element) {
	if(index <= v->nElements) {
		if (acvector_extend(v)) return 1;

		unsigned char * i;
		for (i = v->data + (v->nElements + 1) * v->element_size - 1; \
			 i >= v->data + (index + 1) * v->element_size; --i) {
			*i = *(i - v->element_size);
		}

		unsigned int j;
		for (j = 0; j < v->element_size; ++j) {
			*(v->data + (index + j) * v->element_size) = *((unsigned char *) element + j);
		}
		v->nElements += 1;
		return 0;
	}

	return 2;
}

void *
acvector_remove(acVector * v, unsigned long index) {
	if (index < v->nElements) {
		char * element = malloc(v->element_size);

		unsigned int j;
		for (j = 0; j < v->element_size; ++j) {
			*(element + j) = *(v->data + (index + j) * v->element_size);
		}

		unsigned char * i;
		for (i = v->data + index * v->element_size; \
			 i < v->data + (v->nElements - 1) * v->element_size; ++i) {
			*i = *(i + v->element_size);
		}
		
		v->nElements -= 1;
		return element;
	}

	return NULL;
}

void *
acvector_iterator(acVector * v) {
	if(!(v->nElements)) return NULL;
	return acvector_at(v, 0);
}

void *
acvector_next(acVector * v, void * current) {
	if(!current || (unsigned char *) current < v->data \
				|| (unsigned char *) current > v->data + (v->nElements - 1) * v->element_size) {
		return NULL;
	}

	return current + v->element_size;
}

void *
acvector_iterator_r(acVector * v) {
	if(!(v->nElements)) return NULL;
	return acvector_at(v, v->nElements - 1);
}

void *
acvector_next_r(acVector * v, void * current) {
	if(!current || (unsigned char *) current < v->data + v->element_size \
				|| (unsigned char *) current > v->data + (v->nElements - 1) * v->element_size) {
		return NULL;
	}

	return current - v->element_size;
}

unsigned long
acvector_size_bytes(acVector * v) {
	return v->nElements * v->element_size;
}

int
acvector_trim(acVector * v) {
	return acvector_resize(v, v->nElements);
}

inline int
acvector_extend(acVector * v) {
	if(v->nElements < v->limit) return 0;
	return acvector_resize(v, v->limit * v->extension_factor);
}

inline int
acvector_resize(acVector * v, unsigned long new_size) {
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
acvector_at_nocheck(acVector * v, unsigned long index) {
	return v->data + index * v->element_size;
}
