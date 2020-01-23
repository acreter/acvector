#ifndef _VECTOR_H_INCLUDED
#define _VECTOR_H_INCLUDED

typedef struct acVector acVector;

/* e holds a pointer to the current element and v is the vector */
#define ACVECTOR_FOREACH(e, v) for(e = acvector_iterator(v); e; e = acvector_next(v, e))
#define ACVECTOR_FOREACH_R(e, v) for(e = acvector_iterator_r(v); e; e = acvector_next_r(v, e))

/* meta */
acVector * acvector_create(unsigned long limit, unsigned int element_size, unsigned char extension_factor);
void acvector_release(acVector *);

/* reading */
void * acvector_at(acVector *, unsigned long index);

/* adding */
int acVector_push(acVector *, void *);
int acVector_push_back(acVector *, void *);
int acvector_insert(acVector *, unsigned long index, void *);

/* removing */
void * acVector_pop_back(acVector *);
void * acVector_pop(acVector *);
void * acvector_remove(acVector *, unsigned long index);

/* iterating */
void * acvector_iterator(acVector *);
void * acvector_next(acVector *, void *);
void * acvector_iterator_r(acVector *);
void * acvector_next_r(acVector *, void *);

/* util */
unsigned long acvector_size_bytes(acVector *);
int acvector_trim(acVector *);

#endif
