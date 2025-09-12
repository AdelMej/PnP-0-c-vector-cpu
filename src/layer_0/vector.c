#include "layer_0/vector.h"
#include <stddef.h>
#include <stdlib.h>

/**
 * @brief Creates a new dynamic vector.
 *
 * Allocates memory for a Vector struct and its internal data array.
 * The vector is initialized with the given capacity and zero elements.
 *
 * @param initial_capacity The initial number of elements the vector can hold.
 * @return Pointer to the newly created Vector, or NULL if allocation fails.
 *
 * @note The returned vector must be freed with vector_free() to avoid memory
 * leaks.
 */
Vector *new_vector(size_t initial_capacity) {
  Vector *new_vector;
  if (initial_capacity <= 0)
    return (NULL);

  // initialization of new_vector
  new_vector = malloc(sizeof(Vector));
  if (new_vector == NULL)
    return (NULL);

  // intitialization of data structure zeroed
  new_vector->data = calloc(initial_capacity, sizeof(vector_data_t));
  if (new_vector->data == NULL) {
    free(new_vector);
    return (NULL);
  }

  // initialization of capacity and size
  new_vector->capacity = initial_capacity;
  new_vector->size = 0;

  return (new_vector);
}

/**
 * @brief Frees a dynamically allocated vector.
 *
 * This function releases the memory used by the vector's data array
 * and the Vector struct itself. After calling this function, the pointer
 * passed as argument becomes invalid and must not be used.
 *
 * @param v Pointer to the Vector to be freed. Can be NULL.
 *
 * @note The caller is responsible for setting the pointer to NULL if needed
 *       to avoid dangling references.
 */
void vector_free(Vector *v) {
  if (v == NULL)
    return;

  free(v->data);
  free(v);
}

/**
 * @brief Appends an element to the end of the vector, resizing if necessary.
 *
 * If the vector's current size equals its capacity, the internal storage
 * is automatically reallocated with a growth factor of VECTOR_GROWTH_FACTOR.
 *
 * @param v Pointer to the vector to push into.
 * @param d The element to append to the vector.
 *
 * @note If the vector pointer is NULL or memory allocation fails during
 *       resizing, the function does nothing.
 */
void vector_push(Vector *v, vector_data_t d) {
  vector_data_t *new_data;

  if (v == NULL)
    return;

  if (v->size == v->capacity) {
    new_data = realloc(v->data, sizeof(vector_data_t) * v->capacity *
                                    VECTOR_GROWTH_FACTOR);
    if (new_data == NULL)
      return;

    v->capacity *= VECTOR_GROWTH_FACTOR;
    v->data = new_data;
  }

  v->data[v->size++] = d;
}

void vector_pop(Vector *v) {}
