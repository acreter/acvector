#ifndef _VECTOR_H_INCLUDED
#define _VECTOR_H_INCLUDED

typedef struct acVector acVector;
typedef unsigned char AC_BYTE_T;

struct acVector {
	AC_BYTE_T immutable;
	unsigned long limit, nElements;
	unsigned int element_size;
	unsigned short extension_factor;
	AC_BYTE_T data[1];
};

/* META */
/* returns a pointer to the new vector or NULL if the request failed */
acVector * acvector_create(unsigned long limit, unsigned int element_size, unsigned char extension_factor);
void acvector_release(acVector **);

/* READ */
void * acvector_at(acVector **, unsigned long index);

/* ADD */
int acvector_push(acVector **, void *);
int acvector_push_back(acVector **, void *);
int acvector_insert(acVector **, unsigned long index, void *);

/* REMOVE */
void * acvector_pop_back(acVector **);
void * acvector_pop(acVector **);
void * acvector_remove(acVector **, unsigned long index);

/* ITERATE */
/* all iterate functions either return a pointer to the next element or NULL
 * if such an element does not exist */
void * acvector_iterator(acVector **);
void * acvector_next(acVector **, void *);
void * acvector_iterator_r(acVector **);
void * acvector_next_r(acVector **, void *);

/* quick macros to iterate over all elements of a vector. e holds a pointer to
 * the current element and v is a pointer to the vector */
#define ACVECTOR_FOREACH(e, v) for(e = acvector_iterator(&(v)); e; e = acvector_next(&(v), e))
#define ACVECTOR_FOREACH_R(e, v) for(e = acvector_iterator_r(&(v)); e; e = acvector_next_r(&(v), e))

/* UTIL */
int acvector_trim(acVector **);
unsigned long acvector_size_bytes(acVector **);
#endif
