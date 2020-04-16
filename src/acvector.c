#include "acvector.h"

#include <stdlib.h>
#include <string.h>

int acvector_extend(acVector **);
int acvector_resize(acVector **, unsigned long);

acVector *
acvector_create(unsigned long limit, unsigned int element_size, unsigned char extension_factor) {
	if (!limit) return 0;
	acVector * vector;
	vector = calloc(1, (sizeof *vector) + sizeof (AC_BYTE_T) * element_size * limit - 1);
	if(!vector) return 0;

	vector->immutable = 0;
	vector->limit = limit;
	vector->nElements = 0;
	vector->element_size = element_size;
	vector->extension_factor = extension_factor;

	return vector;
}

void
acvector_release(acVector ** v) {
	free(*v);
	*v = 0;

	return;
}

void *
acvector_at(acVector ** v, unsigned long index) {
	if(index >= (**v).nElements) return 0;
	return (**v).data + index * (**v).element_size;
}

int
acvector_push_back(acVector ** v, void * element) {
	return acvector_insert(v, (**v).nElements, element);
}

int
acvector_push(acVector ** v, void * element) {
	return acvector_insert(v, 0, element);
}

void *
acvector_pop_back(acVector ** v) {
	return acvector_remove(v, (**v).nElements - 1);
}

void *
acvector_pop(acVector ** v) {
	return acvector_remove(v, 0);
}

int
acvector_insert(acVector ** v, unsigned long index, void * element) {
	if ((**v).immutable) return 3;
	if (index <= (**v).nElements) {
		if (acvector_extend(v)) return 1;

		memmove((**v).data + (index + 1) * (**v).element_size,
				(**v).data + index * (**v).element_size,
				(**v).element_size * ((**v).nElements - index));
		memcpy((**v).data + index * (**v).element_size, element, (**v).element_size);

		(**v).nElements += 1;
		return 0;
	}

	return 2;
}

void *
acvector_remove(acVector ** v, unsigned long index) {
	if ((**v).immutable) return NULL;
	if (index < (**v).nElements) {
		AC_BYTE_T* element = malloc((**v).element_size);

		memcpy(element, (**v).data + index * (**v).element_size, (**v).element_size);
		memmove((**v).data + index * (**v).element_size,
				(**v).data + (index + 1) * (**v).element_size,
				(**v).element_size * ((**v).nElements - index - 1));

		(**v).nElements -= 1;
		return element;
	}

	return NULL;
}

void *
acvector_iterator(acVector ** v) {
	if(!((**v).nElements)) return NULL;
	return acvector_at(v, 0);
}

void *
acvector_next(acVector ** v, void * current) {
	if(!current || (AC_BYTE_T *) current < (**v).data \
				|| (AC_BYTE_T *) current >= (**v).data + ((**v).nElements - 1) * (**v).element_size) {
		return NULL;
	}

	return current + (**v).element_size;
}

void *
acvector_iterator_r(acVector ** v) {
	if(!((**v).nElements)) return NULL;
	return acvector_at(v, (**v).nElements - 1);
}

void *
acvector_next_r(acVector ** v, void * current) {
	if(!current || (AC_BYTE_T *) current < (**v).data + (**v).element_size \
				|| (AC_BYTE_T *) current > (**v).data + ((**v).nElements - 1) * (**v).element_size) {
		return NULL;
	}

	return current - (**v).element_size;
}

unsigned long
acvector_size_bytes(acVector ** v) {
	return (**v).nElements * (**v).element_size;
}

int
acvector_trim(acVector ** v) {
	if ((**v).immutable) return 3;
	return acvector_resize(v, (**v).nElements + 1);
}

int
acvector_extend(acVector ** v) {
	if((**v).nElements < (**v).limit) return 0;
	return acvector_resize(v, (**v).limit * (**v).extension_factor);
}

int
acvector_resize(acVector ** v, unsigned long new_size) {
	if((**v).nElements <= new_size) {
		acVector * new = realloc(*v, (sizeof **v) + sizeof (AC_BYTE_T) * (**v).element_size * new_size - 1);
		if(new) {
			(**v).limit = new_size;
			*v = new;
			return 0;
		}
		return 1;
	}

	return 2;
}
