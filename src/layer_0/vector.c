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
 * @brief Appends an element to the end of the vector, resizing if necessary
 *
 * If the vector's current size equals its capacity, the internal storage is
 * automatically reallocated with a growth factor of VECTOR_GROWTH_FACTOR.
 *
 * @param v Pointer to the vector to push into
 * @param d Element to append to the vector
 *
 * @return VECTOR_OK on success
 * @return VECTOR_ERR_NULL if the vector pointer is NULL
 * @return VECTOR_ERR_ALLOC if memory allocation fails during resizing
 *
 * @note After a successful push, v->size is incremented by 1.
 * @note The vector grows automatically; the caller does not need to manage
 * capacity.
 */
int vector_push(Vector *v, vector_data_t d) {
  vector_data_t *new_data;

  if (v == NULL)
    return VECTOR_ERR_NULL;

  if (v->size == v->capacity) {
    new_data = realloc(v->data, sizeof(vector_data_t) * v->capacity *
                                    VECTOR_GROWTH_FACTOR);
    if (new_data == NULL)
      return VECTOR_ERR_ALLOC;

    v->capacity *= VECTOR_GROWTH_FACTOR;
    v->data = new_data;
  }

  v->data[v->size++] = d;
  return VECTOR_OK;
}

/**
 * @brief Sets the element at a specific index in the vector
 *
 * If the index is valid, the element at that position is overwritten with the
 * provided value.
 *
 * @param v Pointer to the vector to modify
 * @param idx Index of the element to set
 * @param d New value to store at the given index
 *
 * @return VECTOR_OK on success
 * @return VECTOR_ERR_NULL if the vector pointer is NULL
 * @return VECTOR_ERR_OOB if the index is out of bounds (>= vector size)
 *
 * @note This function does not resize the vector. The index must be within the
 * current size.
 */
int vector_set(Vector *v, size_t idx, vector_data_t d) {
  if (v == NULL)
    return VECTOR_ERR_NULL;

  if (idx >= v->size)
    return VECTOR_ERR_OOB;

  v->data[idx] = d;
  return VECTOR_OK;
}

/**
 * @brief Retrieves the element at a specific index in the vector
 *
 * The value at the given index is stored in the location pointed to by `out`.
 * This function does not modify the vector.
 *
 * @param v Pointer to the vector
 * @param idx Index of the element to retrieve
 * @param out Pointer to store the retrieved element
 * @return VECTOR_OK on success
 * @return VECTOR_ERR_NULL if `v` or `out` is NULL
 * @return VECTOR_ERR_OOB if `idx` is out of bounds (>= vector size)
 *
 * @note This function is safe for all possible values of vector_data_t
 */
int vector_get(Vector *v, size_t idx, vector_data_t *out) {
  if (v == NULL)
    return VECTOR_ERR_NULL;

  if (idx >= v->size)
    return VECTOR_ERR_OOB;

  *out = v->data[idx];
  return VECTOR_OK;
}

/**
 * @brief Removes and retrieves the last element from the vector
 *
 * The last element is stored in the location pointed to by `out`.
 * The vector size is decremented by one.
 *
 * @param v Pointer to the vector
 * @param out Pointer to store the removed element
 * @return VECTOR_OK on success
 * @return VECTOR_ERR_NULL if `v` or `out` is NULL
 * @return VECTOR_ERR_EMPTY if the vector is empty
 *
 * @note Safe for all values of vector_data_t.
 */
int vector_pop(Vector *v, vector_data_t *out) {
  if (v == NULL)
    return VECTOR_ERR_NULL;

  if (v->size == 0)
    return VECTOR_ERR_EMPTY;

  *out = v->data[--v->size];
  return VECTOR_OK;
}

/**
 * @brief Returns the last element of the vector without removing it
 *
 * The element is stored in the location pointed to by `out`.
 * The vector size is not modified.
 *
 * @param v Pointer to the vector
 * @param out Pointer to store the element
 * @return VECTOR_OK on success
 * @return VECTOR_ERR_NULL if `v` or `out` is NULL
 * @return VECTOR_ERR_EMPTY if the vector is empty
 *
 * @note Safe for all values of vector_data_t.
 */
int vector_back(Vector *v, vector_data_t *out) {
  if (v == NULL)
    return VECTOR_ERR_NULL;

  if (v->size == 0)
    return VECTOR_ERR_EMPTY;

  *out = v->data[v->size - 1];
  return VECTOR_OK;
}
