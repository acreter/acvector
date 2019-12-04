#ifndef _VECTOR_H_INCLUDED
#define _VECTOR_H_INCLUDED

#include <stddef.h>

#define Vector_p Vector *
#define VECTOR_EXTEND_FACTOR 2

typedef struct Vector {
	void * data;
	size_t limit,
		   nElements,
		   element_size;
} Vector;

#define acvector_foreach(e, v) for(e = acvector_iterator(v); e; e = acvector_next(v, e))
#define acvector_foreach_r(e, v) for(e = acvector_iterator_r(v); e; e = acvector_next_r(v, e))

Vector_p acvector_init(size_t limit, size_t element_size);
void acvector_release(Vector_p v);

void * acvector_at(Vector_p v, size_t);

char acvector_push_back(Vector_p, void *);
char acvector_push(Vector_p, void *);
char acvector_insert(Vector_p, size_t, void *);

void * acvector_pop_back(Vector_p);
void * acvector_pop(Vector_p);
void * acvector_remove(Vector_p, size_t);

void * acvector_iterator(Vector_p);
void * acvector_next(Vector_p, void *);
void * acvector_iterator_r(Vector_p);
void * acvector_next_r(Vector_p, void *);

size_t acvector_size_bytes(Vector_p);
char acvector_trim(Vector_p);

#endif
