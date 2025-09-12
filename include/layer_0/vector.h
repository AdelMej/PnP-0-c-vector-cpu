/**
 * vector.h - Header file for Matrix library
 *
 * Provides functions for creating, manipulating, and freeing vectors.
 */
#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include <stddef.h>

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
Vector *new_vector(size_t initial_capacity);
void vector_free(Vector *v);

// -- utility functions --
void vector_push(Vector *v, vector_data_t d);

#endif /* MY_VECTOR_H */
