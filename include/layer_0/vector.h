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

/** @name Vector error codes */
//@{
#define VECTOR_OK 0        /**< Operation succeeded */
#define VECTOR_ERR_OOB 1   /**< Index out of bounds */
#define VECTOR_ERR_ALLOC 2 /**< Memory allocation failed */
#define VECTOR_ERR_NULL 3  /**< Null pointer passed */
#define VECTOR_ERR_EMPTY 4 /**< Vector is empty */
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
 * @typedef vector_data_t
 * @brief The type of elements stored in the vector.
 *
 * Currently defined as double for AI and numerical computations.
 */
typedef struct {
  vector_data_t
      *data;   /**< Pointer to the dynamically allocated array of elements */
  size_t size; /**< Current number of elements stored in the vector */
  size_t capacity; /**< Total allocated capacity of the vector */
} Vector;

// -- memory and contructor --
/**
 * @brief Creates a new vector with a given initial capacity
 * @param initial_capacity Number of elements to allocate initially
 * @return Pointer to the new vector, or NULL if allocation fails
 */
Vector *new_vector(size_t initial_capacity);

/**
 * @brief Frees a vector and its contents
 * @param vector Pointer to the vector
 */
void vector_free(Vector *vector);

// -- utility functions --
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

// -- getter-style functions --
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

#endif /* MY_VECTOR_H */
