#ifndef _VECTOR_H_INCLUDED
#define _VECTOR_H_INCLUDED

#include <stddef.h>

#define acVector_p acVector *
#define ACVECTOR_EXTEND_FACTOR 2

typedef struct acVector {
	void * data;
	size_t limit,
		   nElements,
		   element_size;
} acVector;

#define ACVECTOR_FOREACH(e, v) for(e = acvector_iterator(v); e; e = acvector_next(v, e))
#define ACVECTOR_FOREACH_R(e, v) for(e = acvector_iterator_r(v); e; e = acvector_next_r(v, e))

acVector_p acvector_init(size_t limit, size_t element_size);
void acvector_release(acVector_p v);

void * acvector_at(acVector_p v, size_t);

char acvector_push_back(acVector_p, void *);
char acvector_push(acVector_p, void *);
char acvector_insert(acVector_p, size_t, void *);

void * acvector_pop_back(acVector_p);
void * acvector_pop(acVector_p);
void * acvector_remove(acVector_p, size_t);

void * acvector_iterator(acVector_p);
void * acvector_next(acVector_p, void *);
void * acvector_iterator_r(acVector_p);
void * acvector_next_r(acVector_p, void *);

size_t acvector_size_bytes(acVector_p);
char acvector_trim(acVector_p);

#endif
