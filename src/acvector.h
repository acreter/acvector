#ifndef __ACVECTOR_H_INCLUDED
#define __ACVECTOR_H_INCLUDED 1

#define AC_EXTENSION_FACTOR 2
typedef struct acVector acVector;

struct acVector {
	unsigned long number_of_elements, limit;
	unsigned int size_of_element;
	char data[];
};

/* --------------------------------------------------------- */

/* meta */
acVector*     acvector_create       (unsigned long limit, unsigned int size_of_element);
void          acvector_destroy      (acVector** vector);

/* access */
void*         acvector_get_at       (acVector** vector, unsigned long index);
void*         acvector_get_first    (acVector** vector);
void*         acvector_get_last     (acVector** vector);
void          acvector_copy_element (acVector** vector, void* dest, void* src);

/* modifiers */
void          acvector_clear        (acVector** vector);
void          acvector_insert       (acVector** vector, unsigned long index, void* elements, unsigned long number_of_elements);
void          acvector_remove       (acVector** vector, unsigned long index, unsigned long number_of_elements);

/* utility */
unsigned long acvector_size         (acVector** vector);
acVector*     acvector_copy         (acVector** vector);

/* macros
 * vector  is of type acVector**
 * element is of type void* */
#define acvector_remove_from_back(vector, n_elements) acvector_remove((vector), ((*(vector))->number_of_elements - n_elements), n_elements)
#define acvector_remove_from_front(vector, n_elements) acvector_remove((vector), 0, n_elements)
#define acvector_append(vector, elements, n_elements) acvector_insert((vector), (*(vector))->number_of_elements, elements, n_elements)
#define acvector_prepend(vector, elements, n_elements) acvector_insert((vector), 0, elements, n_elements)

/* --------------------------------------------------------- */
#endif
