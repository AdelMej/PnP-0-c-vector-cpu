#include "layer_0/vector.h"
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

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

/**
 * @brief Clears all elements from the vector
 *
 * Sets the vector's size to 0 while keeping the allocated memory intact.
 * This allows the vector to be reused without reallocating memory.
 *
 * @param v Pointer to the vector to clear
 * @return VECTOR_OK on success
 * @return VECTOR_ERR_NULL if the vector pointer is NULL
 */
int vector_clear(Vector *v) {
  if (v == NULL)
    return VECTOR_ERR_NULL;

  v->size = 0;
  return VECTOR_OK;
}

/**
 * @brief Creates a copy of the given vector
 *
 * Allocates a new vector and duplicates the contents of the original vector.
 * The new vector has the same size and capacity as the source vector.
 *
 * @param v Pointer to the vector to copy
 * @return Pointer to the newly allocated copy on success
 * @return NULL if the input vector is NULL or memory allocation fails
 *
 * @note The caller is responsible for freeing the returned vector using
 * vector_free().
 */
Vector *vector_copy(Vector *v) {
  Vector *copy;

  if (v == NULL)
    return NULL;

  copy = malloc(sizeof(Vector));
  if (copy == NULL)
    return NULL;

  copy->data = malloc(sizeof(vector_data_t) * v->capacity);
  if (copy->data == NULL) {
    free(copy);
    return NULL;
  }

  copy->capacity = v->capacity;
  copy->size = v->size;
  memcpy(copy->data, v->data, sizeof(vector_data_t) * v->size);

  return copy;
}

/**
 * @brief Resize the capacity of a vector.
 *
 * Attempts to change the vector's internal storage capacity to the new value.
 * - If `resize` is larger than the current capacity, the buffer is expanded.
 * - If `resize` is smaller than the current capacity, the buffer is shrunk.
 *   If this causes `size > capacity`, the vector's size will be clamped
 *   to the new capacity.
 *
 * @note A capacity of `0` is invalid. The minimum allowed capacity is `1`.
 *
 * @param v Pointer to the vector to resize.
 * @param resize New capacity (must be >= 1).
 *
 * @return VECTOR_OK on success.
 * @return VECTOR_ERR_NULL if @p v is NULL.
 * @return VECTOR_ERR_ALLOC if memory allocation fails.
 * @return VECTOR_ERR_OOB if @p resize == 0.
 */
int vector_resize(Vector *v, size_t resize) {
  vector_data_t *temp;

  if (v == NULL)
    return VECTOR_ERR_NULL;

  if (resize == 0)
    return VECTOR_ERR_OOB;

  temp = realloc(v->data, sizeof(vector_data_t) * resize);
  if (temp == NULL)
    return VECTOR_ERR_ALLOC;

  v->data = temp;
  v->capacity = resize;

  if (v->size > v->capacity)
    v->size = v->capacity;

  return VECTOR_OK;
}

/**
 * @brief Get the current number of elements stored in the vector.
 *
 * This function stores the number of elements in the given vector in the
 * variable pointed to by `out`.
 *
 * @param v Pointer to the vector.
 * @param out Pointer to a size_t variable where the size will be stored.
 * @return VECTOR_OK if successful, VECTOR_ERR_NULL if v or out is NULL.
 */
int vector_size(Vector *v, size_t *out) {
  if (v == NULL || out == NULL)
    return VECTOR_ERR_NULL;

  *out = v->size;
  return VECTOR_OK;
}

/**
 * @brief Get the current capacity of the vector.
 *
 * This function stores the capacity of the given vector in the variable
 * pointed to by `out`.
 *
 * @param v Pointer to the vector.
 * @param out Pointer to a size_t variable where the capacity will be stored.
 * @return VECTOR_OK if successful, VECTOR_ERR_NULL if v or out is NULL.
 */
int vector_capacity(Vector *v, size_t *out) {
  if (v == NULL || out == NULL)
    return VECTOR_ERR_NULL;

  *out = v->capacity;
  return VECTOR_OK;
}

/**
 * @brief Check if the vector is empty.
 *
 * @param v Pointer to the vector.
 * @return 1 if the vector is empty, 0 if it has elements, -1 if v is NULL.
 */
int vector_empty(Vector *v) {
  if (v == NULL)
    return -1;

  return (v->size == 0);
}

/**
 * @brief Insert a value at a specified index in the vector.
 *
 * Shifts all elements starting at the index one position to the right.
 * If the vector's capacity is exceeded, it is automatically grown.
 *
 * @param v Pointer to the vector.
 * @param idx Index at which to insert the value (0 <= idx <= size).
 * @param value The value to insert.
 * @return VECTOR_OK on success,
 *         VECTOR_ERR_NULL if the vector is NULL,
 *         VECTOR_ERR_OOB if the index is out of bounds,
 *         VECTOR_ERR_ALLOC if memory allocation fails during growth.
 */
int vector_insert(Vector *v, size_t idx, vector_data_t value) {
  vector_data_t *temp;
  size_t i;

  if (v == NULL)
    return VECTOR_ERR_NULL;
  if (idx >= v->size)
    return VECTOR_ERR_OOB;

  if (v->size + 1 > v->capacity) {
    temp = realloc(v->data,
                   sizeof(vector_data_t) * v->capacity * VECTOR_GROWTH_FACTOR);
    if (temp == NULL)
      return VECTOR_ERR_ALLOC;
    v->data = temp;
    v->capacity *= VECTOR_GROWTH_FACTOR;
  }

  for (i = v->size; i > idx; i--)
    v->data[i] = v->data[i - 1];

  v->data[idx] = value;
  v->size++;

  return VECTOR_OK;
}

/**
 * @brief Remove an element at a specific index from the vector.
 *
 * Shifts all elements after the index one position to the left.
 *
 * @param v Pointer to the vector.
 * @param idx Index of the element to remove.
 * @return VECTOR_OK on success,
 *         VECTOR_ERR_NULL if the vector is NULL,
 *         VECTOR_ERR_OOB if the index is out of bounds.
 */
int vector_remove(Vector *v, size_t idx) {
  size_t i;

  if (v == NULL)
    return VECTOR_ERR_NULL;

  if (idx >= v->size)
    return VECTOR_ERR_OOB;

  for (i = idx; i < v->size - 1; i++)
    v->data[i] = v->data[i + 1];

  v->size--;

  return VECTOR_OK;
}

/**
 * @brief Apply a function to each element of the vector.
 *
 * This function iterates over all elements in the vector and applies
 * the given function to each element in-place.
 *
 * @param v Pointer to the vector.
 * @param func Function pointer that takes a pointer to an element.
 *             This function is applied to each element.
 * @return VECTOR_OK on success, VECTOR_ERR_NULL if v or func is NULL.
 */
int vector_foreach(Vector *v, void (*func)(vector_data_t *elem)) {
  size_t i;

  if (v == NULL || func == NULL)
    return VECTOR_ERR_NULL;

  for (i = 0; i < v->size; i++)
    func(&v->data[i]);

  return VECTOR_OK;
}

/**
 * @brief Create a new vector by applying a function to each element of an
 * existing vector.
 *
 * This function allocates a new vector with the same capacity as the input
 * vector and fills it with the results of applying the given function to each
 * element.
 *
 * @param v Pointer to the source vector. Must not be NULL.
 * @param func Function pointer to a mapping function that takes a vector_data_t
 *             and returns a transformed vector_data_t. Must not be NULL.
 * @return Pointer to the newly created vector with transformed elements, or
 *         NULL if the input vector or function pointer is NULL, or if
 * allocation fails.
 */
Vector *vector_map(Vector *v, vector_data_t (*func)(vector_data_t elem)) {
  Vector *copy;
  size_t i;

  if (v == NULL || func == NULL)
    return NULL;

  copy = new_vector(v->capacity);
  if (copy == NULL)
    return NULL;

  for (i = 0; i < v->size; i++)
    copy->data[i] = func(v->data[i]);

  copy->size = v->size;
  return copy;
}

/**
 * @brief Find the index of the first element matching a given condition.
 *
 * This function iterates through the vector and applies the user-provided
 * predicate function to each element. If the predicate returns non-zero,
 * the corresponding index is returned immediately.
 *
 * @param v Pointer to the vector.
 * @param func Predicate function that takes an element and returns non-zero if
 * it matches.
 * @return Index of the first matching element on success, -1 if no match is
 * found or if @p v or @p func are NULL.
 */
ssize_t vector_find(Vector *v, int (*func)(vector_data_t elem)) {
  size_t i;

  if (v == NULL || func == NULL)
    return -1;

  for (i = 0; i < v->size; i++) {
    if (func(v->data[i]))
      return (ssize_t)i;
  }

  // no match found
  return -1;
}

/**
 * @brief Compute the dot product (scalar product) of two vectors.
 *
 * Calculates the sum of the products of corresponding elements:
 *   result = a[0]*b[0] + a[1]*b[1] + ... + a[n-1]*b[n-1]
 * Both vectors must have the same number of elements.
 *
 * @param v Pointer to the first vector.
 * @param w Pointer to the second vector.
 * @param out Pointer to store the resulting dot product.
 * @return VECTOR_OK on success.
 * @return VECTOR_ERR_NULL if any pointer is NULL.
 * @return VECTOR_ERR_SIZE if the vectors have different sizes.
 *
 * @note If the vectors are empty, the returned dot product is 0.
 */
int vector_dot(Vector *a, Vector *b, vector_data_t *out) {
  size_t i;
  vector_data_t result = 0;

  if (a == NULL || b == NULL || out == NULL)
    return VECTOR_ERR_NULL;

  if (a->size != b->size)
    return VECTOR_ERR_SIZE;

  for (i = 0; i < a->size; i++)
    result += a->data[i] * b->data[i];

  *out = result;
  return VECTOR_OK;
}

/**
 * @brief Compute the Euclidean norm (length) of a vector.
 *
 * Calculates the L2 norm (magnitude) of the vector:
 * the square root of the sum of the squares of all elements.
 *
 * @param v Pointer to the vector.
 * @param out Pointer to store the resulting norm.
 * @return VECTOR_OK on success.
 * @return VECTOR_ERR_NULL if the vector or output pointer is NULL.
 *
 * @note If the vector is empty, the norm returned will be 0.
 */
int vector_norm(Vector *v, vector_data_t *out) {
  size_t i;
  vector_data_t result = 0;

  if (v == NULL || out == NULL)
    return VECTOR_ERR_NULL;

  for (i = 0; i < v->size; i++)
    result += v->data[i] * v->data[i];

  *out = sqrt(result);
  return VECTOR_OK;
}

/**
 * @brief Add two vectors element-wise.
 *
 * Allocates a new vector and stores in it the sum of corresponding elements
 * from `a` and `b`.
 *
 * @param a Pointer to the first vector.
 * @param b Pointer to the second vector.
 * @return Pointer to the resulting vector on success,
 *         or NULL if either vector is NULL or their sizes differ.
 *
 * @note The resulting vector's capacity is exactly equal to its size.
 */
Vector *vector_add(Vector *a, Vector *b) {
  Vector *result;
  size_t i;

  if (a == NULL || b == NULL)
    return NULL;

  if (a->size != b->size)
    return NULL;

  result = new_vector(a->size);
  if (result == NULL)
    return NULL;

  for (i = 0; i < a->size; i++)
    result->data[i] = a->data[i] + b->data[i];

  return result;
}

/**
 * @brief Subtract two vectors element-wise.
 *
 * Allocates a new vector and stores in it the difference of corresponding
 * elements from `a` and `b`.
 *
 * @param a Pointer to the first vector.
 * @param b Pointer to the second vector.
 * @return Pointer to the resulting vector on success,
 *         or NULL if either vector is NULL or their sizes differ.
 *
 * @note The resulting vector's capacity is exactly equal to its size.
 */
Vector *vector_sub(Vector *a, Vector *b) {
  Vector *result;
  size_t i;

  if (a == NULL || b == NULL)
    return NULL;

  if (a->size != b->size)
    return NULL;

  result = new_vector(a->size);
  if (result == NULL)
    return NULL;

  for (i = 0; i < a->size; i++)
    result->data[i] = a->data[i] - b->data[i];

  return result;
}

/**
 * @brief Multiply two vectors element-wise.
 *
 * Allocates a new vector and stores in it the product of corresponding
 * elements from `a` and `b`.
 *
 * @param a Pointer to the first vector.
 * @param b Pointer to the second vector.
 * @return Pointer to the resulting vector on success,
 *         or NULL if either vector is NULL or their sizes differ.
 *
 * @note The resulting vector's capacity is exactly equal to its size.
 */
Vector *vector_mul(Vector *a, Vector *b) {
  Vector *result;
  size_t i;

  if (a == NULL || b == NULL)
    return NULL;

  if (a->size != b->size)
    return NULL;

  result = new_vector(a->size);
  if (result == NULL)
    return NULL;

  for (i = 0; i < a->size; i++)
    result->data[i] = a->data[i] * b->data[i];

  return result;
}

/**
 * @brief Divide two vectors element-wise.
 *
 * Allocates a new vector and stores in it the quotient of corresponding
 * elements from `a` and `b`.
 *
 * @param a Pointer to the numerator vector.
 * @param b Pointer to the denominator vector.
 * @return Pointer to the resulting vector on success,
 *         or NULL if either vector is NULL, their sizes differ,
 *         or if division by zero occurs.
 *
 * @note The resulting vector's capacity is exactly equal to its size.
 */
Vector *vector_div(Vector *a, Vector *b) {
  Vector *result;
  size_t i;

  if (a == NULL || b == NULL)
    return NULL;

  if (a->size != b->size)
    return NULL;

  result = new_vector(a->size);
  if (result == NULL)
    return NULL;

  for (i = 0; i < a->size; i++) {
    if (b->data[i] == 0.0) {
      vector_free(result);
      return (NULL);
    }
    result->data[i] = a->data[i] / b->data[i];
  }

  return result;
}
