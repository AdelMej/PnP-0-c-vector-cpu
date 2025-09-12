/**
 * vector.h - Header file for Matrix library
 *
 * Provides functions for creating, manipulating, and freeing vectors.
 */
#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include <stddef.h>

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

Vector *new_vector(size_t initial_capacity);
void vector_free(Vector *v);

#endif /* MY_VECTOR_H */
