#ifndef __ACVECTOR_H_INCLUDED
#define __ACVECTOR_H_INCLUDED 1

#define AC_EXTENSION_FACTOR 2
typedef struct acVector acVector;

struct acVector {
	unsigned long number_of_elements, limit;
	unsigned int size_of_element;
	char data[1];
};

/* --------------------------------------------------------- */

/* meta */
acVector* acvector_create       (unsigned long limit, unsigned int size_of_element);
void      acvector_destroy      (acVector** vector);

/* access */
void*     acvector_get_at       (acVector** vector, unsigned long index);
void*     acvector_get_first    (acVector** vector);
void*     acvector_get_last     (acVector** vector);
void      acvector_copy_element (acVector** vector, void* dest, void* src);

/* iterator */
void*     acvector_next         (acVector** vector, void* element);
void*     acvector_prev         (acVector** vector, void* element);

/* modifiers */
void      acvector_clear        (acVector** vector);
void      acvector_insert       (acVector** vector, unsigned long index, void* element);
void      acvector_remove       (acVector** vector, unsigned long index);

/* macros
 * vector  is of type acVector**
 * element is of type void* */
#define acvector_remove_last(vector) acvector_remove((vector), ((*(vector))->number_of_elements - 1))
#define acvector_remove_first(vector) acvector_remove((vector), 0)
#define acvector_append(vector, element) acvector_insert((vector), (*(vector))->number_of_elements, element)
#define acvector_prepend(vector, element) acvector_insert((vector), 0, element)

/* --------------------------------------------------------- */
#endif
