/**
 * @file vector.h
 * @brief Dynamic vector library
 *
 * Provides functions for creating, manipulating, and freeing dynamic vectors.
 * Supports operations like push, set, get, and automatic resizing.
 * Error handling is done via defined VECTOR_ERR_* codes.
 */
#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include <stddef.h>
#include <sys/types.h>

/** @name Vector error codes */
//@{
#define VECTOR_OK 0        /**< Operation succeeded */
#define VECTOR_ERR_OOB 1   /**< Index out of bounds */
#define VECTOR_ERR_ALLOC 2 /**< Memory allocation failed */
#define VECTOR_ERR_NULL 3  /**< Null pointer passed */
#define VECTOR_ERR_EMPTY 4 /**< Vector is empty */
#define VECTOR_ERR_SIZE 5  /**< Vector size mismatch */
//@}

/**
 * @brief Factor by which the vector capacity grows when needed
 */
#define VECTOR_GROWTH_FACTOR 2

/**
 * @typedef vector_data_t
 * @brief The type of elements stored in the vector.
 *
 * Currently defined as double for AI and numerical computations.
 */
typedef double vector_data_t;

/**
 * @brief Dynamic array of elements.
 *
 * Represents a resizable array of `vector_data_t` elements.
 * Tracks the number of elements (`size`) and allocated capacity (`capacity`).
 *
 * @note Always use @ref vector_free to release the allocated memory.
 */
typedef struct {
    vector_data_t
        *data;   /**< Pointer to the dynamically allocated array of elements */
    size_t size; /**< Current number of elements stored in the vector */
    size_t capacity; /**< Total allocated capacity of the vector */
} Vector;

/****************************************************
 *                                                  *
 *            MEMORY AND CONSTRUCTOR                *
 *                                                  *
 ****************************************************/

/**
 * @brief Creates a new vector with a given initial capacity
 * @param initial_capacity Number of elements to allocate initially
 * @return Pointer to the new vector, or NULL if allocation fails
 */
Vector *vector_new(size_t initial_capacity);

/**
 * @brief Frees a vector and its contents
 * @param vector Pointer to the vector
 */
void vector_free(Vector *vector);

/****************************************************
 *                                                  *
 *                 UTILITY FUNCTIONS                *
 *                                                  *
 ****************************************************/

/**
 * @brief Appends an element to the end of the vector, resizing if necessary
 * @param vector Pointer to the vector
 * @param data Element to append
 * @return VECTOR_OK on success
 * @return VECTOR_ERR_NULL if the vector pointer is NULL
 * @return VECTOR_ERR_ALLOC if memory allocation fails during resizing
 */
int vector_push(Vector *vector, vector_data_t data);

/**
 * @brief Sets the element at a specific index in the vector
 * @param vector Pointer to the vector
 * @param index Index to modify
 * @param data New value
 * @return VECTOR_OK on success
 * @return VECTOR_ERR_NULL if the vector pointer is NULL
 * @return VECTOR_ERR_OOB if the index is out of bounds
 */
int vector_set(Vector *vector, size_t index, vector_data_t data);

/**
 * @brief Gets the element at a specific index
 *
 * @param vector Pointer to the vector
 * @param index Index to read
 * @param out Pointer to store the retrieved value
 * @return VECTOR_OK on success
 * @return VECTOR_ERR_NULL if vector or out pointer is NULL
 * @return VECTOR_ERR_OOB if index is out of bounds
 */
int vector_get(Vector *vector, size_t index, vector_data_t *out);

/**
 * @brief Removes and returns the last element in the vector
 *
 * @param vector Pointer to the vector
 * @param out Pointer to store the removed element
 * @return VECTOR_OK on success
 * @return VECTOR_ERR_NULL if vector or out pointer is NULL
 * @return VECTOR_ERR_OOB if vector is empty
 */
int vector_pop(Vector *vector, vector_data_t *out);

/**
 * @brief Returns the last element without removing it
 *
 * @param vector Pointer to the vector
 * @param out Pointer to store the element
 * @return VECTOR_OK on success
 * @return VECTOR_ERR_NULL if vector or out pointer is NULL
 * @return VECTOR_ERR_OOB if vector is empty
 */
int vector_back(Vector *vector, vector_data_t *out);

/**
 * @brief Clears all elements from the vector
 *
 * Sets the vector size to 0 but keeps the allocated memory intact.
 * Useful for reusing a vector without reallocating.
 *
 * @param vector Pointer to the vector to clear
 * @return VECTOR_OK on success
 * @return VECTOR_ERR_NULL if the vector pointer is NULL
 */
int vector_clear(Vector *vector);

/**
 * @brief Creates a copy of a vector
 *
 * Allocates a new vector and duplicates all elements from the source vector.
 *
 * @param vector Pointer to the vector to copy
 * @return Pointer to the new vector on success
 * @return NULL if the source vector is NULL or memory allocation fails
 */
Vector *vector_copy(Vector *vector);

/**
 * @brief Resizes the vector to a new capacity
 *
 * Reallocates the internal storage of the vector to the specified capacity.
 * If the new capacity is smaller than the current size, the vector is
 * truncated.
 *
 * @param vector Pointer to the vector to resize
 * @param new_capacity The new desired capacity
 * @return VECTOR_OK on success
 * @return VECTOR_ERR_NULL if the vector pointer is NULL
 * @return VECTOR_ERR_ALLOC if memory allocation fails
 */
int vector_resize(Vector *vector, size_t new_capacity);

/**
 * @brief Insert a new element at a given index in the vector.
 *
 * Shifts elements after the index to the right. If the vector's capacity
 * is reached, it will be resized automatically.
 *
 * @param vector Pointer to the vector.
 * @param index Position at which to insert the element.
 * @param value The value to insert.
 * @return VECTOR_OK on success, VECTOR_ERR_NULL if vector is NULL,
 *         VECTOR_ERR_OOB if index is out of bounds, VECTOR_ERR_ALLOC if memory
 * allocation fails.
 */
int vector_insert(Vector *vector, size_t index, vector_data_t value);

/**
 * @brief Remove an element at a given index from the vector.
 *
 * @param vector Pointer to the vector.
 * @param index Position of the element to remove.
 * @return VECTOR_OK on success, VECTOR_ERR_NULL if vector is NULL,
 *         VECTOR_ERR_OOB if index is out of bounds.
 */
int vector_remove(Vector *vector, size_t index);

/****************************************************
 *                                                  *
 *                 QUERY / ACCESSORS                *
 *                                                  *
 ****************************************************/

/**
 * @brief Get the current number of elements stored in the vector.
 *
 * This function writes the current size of the vector into the variable
 * pointed to by `out`. If the vector pointer is NULL, it returns an error.
 *
 * @param vector Pointer to the vector.
 * @param out Pointer to a size_t variable where the vector size will be stored.
 * @return VECTOR_OK on success, VECTOR_ERR_NULL if the vector pointer is NULL.
 */
int vector_size(Vector *vector, size_t *out);

/**
 * @brief Get the current capacity of the vector.
 *
 * This function retrieves the maximum number of elements the vector can
 * currently hold.
 *
 * @param vector Pointer to the vector.
 * @param out Pointer to a size_t where the capacity will be stored.
 * @return VECTOR_OK (0) on success, or VECTOR_ERR_NULL if the vector pointer is
 * NULL.
 */
int vector_capacity(Vector *vector, size_t *out);

/**
 * @brief Check if the vector is empty.
 *
 * This function checks whether the vector currently contains any elements.
 *
 * @param vector Pointer to the vector.
 * @return 1 if the vector is empty, 0 if it contains elements, or -1 if vector
 * is NULL.
 */
int vector_empty(Vector *vector);

/****************************************************
 *                                                  *
 *                ITERATORS / TRANSFORMS            *
 *                                                  *
 ****************************************************/

/**
 * @brief Apply a function to each element of the vector.
 *
 * @param vector Pointer to the vector.
 * @param function Function to apply to each element. Receives a pointer to the
 * element.
 * @return VECTOR_OK on success, VECTOR_ERR_NULL if vector or function is NULL.
 */
int vector_foreach(Vector *vector, void (*function)(vector_data_t *element));

/**
 * @brief Create a new vector by applying a function to each element of an
 * existing vector.
 *
 * @param vector Pointer to the original vector.
 * @param function Function to apply to each element. Receives element by value
 * and returns the transformed value.
 * @return Pointer to a newly allocated vector with transformed elements, or
 * NULL if allocation fails or vector/function is NULL.
 */
Vector *vector_map(Vector *vector,
                   vector_data_t (*function)(vector_data_t element));

/**
 * @brief Find the index of the first element that satisfies a condition.
 *
 * @param vector Pointer to the vector.
 * @param function Function that returns non-zero if the element matches the
 * condition.
 * @return Index of the first matching element, or -1 if none match or if
 * vector/function is NULL.
 */
ssize_t vector_find(Vector *vector, int (*function)(vector_data_t element));

/****************************************************
 *                                                  *
 *                 MATH OPERATIONS                  *
 *                                                  *
 ****************************************************/

/**
 * @brief Compute the dot product (scalar product) of two vectors.
 *
 * The dot product is calculated as:
 *   dot = A[0]*B[0] + A[1]*B[1] + ... + A[n-1]*B[n-1]
 * where both vectors must have the same number of elements.
 *
 * @param vector_a Pointer to the first vector.
 * @param vector_b Pointer to the second vector.
 * @param out Pointer to a variable where the resulting dot product will be
 * stored.
 * @return VECTOR_OK on success.
 * @return VECTOR_ERR_NULL if any input pointer is NULL.
 * @return VECTOR_ERR_SIZE if the vectors have different sizes.
 *
 * @note If the vectors are empty, the dot product returned will be 0.
 */
int vector_dot(Vector *vector_a, Vector *vector_b, vector_data_t *out);

/**
 * @brief Compute the Euclidean norm (length) of a vector.
 *
 * The Euclidean norm is calculated as:
 *   ||v|| = sqrt(v[0]^2 + v[1]^2 + ... + v[n-1]^2)
 *
 * @param vector Pointer to the vector.
 * @param out Pointer to store the resulting norm.
 * @return VECTOR_OK on success.
 * @return VECTOR_ERR_NULL if either pointer is NULL.
 *
 * @note If the vector is empty, the returned norm is 0.
 */
int vector_norm(Vector *vector, vector_data_t *out);

/**
 * @brief Add two vectors element-wise.
 *
 * Both vectors must have the same number of elements.
 *
 * @param vector_a Pointer to the first vector.
 * @param vector_b Pointer to the second vector.
 * @return Pointer to a new vector containing the sums on success,
 *         or NULL if either vector is NULL or sizes differ.
 */
Vector *vector_add(Vector *vector_a, Vector *vector_b);

/**
 * @brief Subtract two vectors element-wise.
 *
 * Both vectors must have the same number of elements.
 *
 * @param vector_a Pointer to the first vector.
 * @param vector_b Pointer to the second vector.
 * @return Pointer to a new vector containing the differences on success,
 *         or NULL if either vector is NULL or sizes differ.
 */
Vector *vector_sub(Vector *vector_a, Vector *vector_b);

/**
 * @brief Multiply two vectors element-wise.
 *
 * Both vectors must have the same number of elements.
 *
 * @param vector_a Pointer to the first vector.
 * @param vector_b Pointer to the second vector.
 * @return Pointer to a new vector containing the products on success,
 *         or NULL if either vector is NULL or sizes differ.
 */
Vector *vector_mul(Vector *vector_a, Vector *vector_b);

/**
 * @brief Divide two vectors element-wise.
 *
 * Both vectors must have the same number of elements.
 *
 * @param vector_a Pointer to the first vector.
 * @param vector_b Pointer to the second vector.
 * @return Pointer to a new vector containing the quotients on success,
 *         or NULL if either vector is NULL, sizes differ, or any element
 *         of vector_b is zero.
 *
 * @note If any element of vector_b is zero, the function returns NULL
 *       and no partial results are produced.
 */
Vector *vector_div(Vector *vector_a, Vector *vector_b);

#endif /* MY_VECTOR_H */
