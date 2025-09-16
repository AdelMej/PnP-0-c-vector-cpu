# C Dynamic Vector Library

A fast, lightweight, and thoroughly tested dynamic vector library in C for numerical computations.

## Features

- Resizable dynamic arrays for `double` elements (`vector_data_t`).
- Standard operations: push, pop, insert, remove, clear.
- Mathematical operations: dot product, norm, element-wise add, sub, mul, div.
- Safe: handles NULL pointers, size mismatches, and division by zero.
- Fully unit tested with Unity (100% tests passing 😎).

## Installation / Build

```bash
git clone https://github.com/AdelMej/PnP-0-c-vector-cpu
cd PnP-0-c-vector-cpu
mkdir build
cd build
cmake ..
make
```

- `cmake` .. generates the Makefiles.
- `make` compiles the library and tests.
- `ctest` runs all unit tests (23 passing tests expected 😏).

## Usage Example

```c
#include "layer_0/vector.h"

int main() {
    Vector *v = new_vector(4);
    vector_push(v, 1.0);
    vector_push(v, 2.0);

    vector_data_t norm;
    vector_norm(v, &norm);

    vector_free(v);
    return 0;
}
```

## API Overview

All functions are declared in `layer_0/vector.h`. Most functions return an `int` status code (`VECTOR_OK`, `VECTOR_ERR_NULL`, `VECTOR_ERR_OOB`, etc.) or a pointer to a new vector.

### Vector Creation & Memory Management

| Function | Description |
|----------|-------------|
| `Vector *new_vector(size_t initial_capacity)` | Create a new vector with a specified initial capacity. |
| `void vector_free(Vector *v)` | Free the vector and its allocated memory. |
| `Vector *vector_copy(Vector *v)` | Create a deep copy of a vector. |

### Element Access & Modification

| Function | Description |
|----------|-------------|
| `int vector_push(Vector *v, vector_data_t val)` | Append an element to the end. |
| `int vector_pop(Vector *v, vector_data_t *out)` | Remove and retrieve the last element. |
| `int vector_get(Vector *v, size_t index, vector_data_t *out)` | Read element at `index`. |
| `int vector_set(Vector *v, size_t index, vector_data_t val)` | Set element at `index`. |
| `int vector_insert(Vector *v, size_t index, vector_data_t val)` | Insert element at `index`. |
| `int vector_remove(Vector *v, size_t index)` | Remove element at `index`. |
| `int vector_clear(Vector *v)` | Remove all elements but keep allocated memory. |
| `int vector_size(Vector *v, size_t *out)` | Get current number of elements. |
| `int vector_capacity(Vector *v, size_t *out)` | Get allocated capacity. |
| `int vector_empty(Vector *v)` | Returns 1 if empty, 0 if not, -1 if NULL. |

### Iterators & Transformations

| Function | Description |
|----------|-------------|
| `int vector_foreach(Vector *v, void (*func)(vector_data_t *))` | Apply a function to each element. |
| `Vector *vector_map(Vector *v, vector_data_t (*func)(vector_data_t))` | Return a new vector with a function applied to each element. |
| `ssize_t vector_find(Vector *v, int (*func)(vector_data_t))` | Return the index of the first element satisfying a condition, -1 if none or NULL. |

### Math Operations

| Function | Description |
|----------|-------------|
| `int vector_dot(Vector *a, Vector *b, vector_data_t *out)` | Compute the dot product. |
| `int vector_norm(Vector *v, vector_data_t *out)` | Compute the Euclidean norm (length). |
| `Vector *vector_add(Vector *a, Vector *b)` | Element-wise addition. |
| `Vector *vector_sub(Vector *a, Vector *b)` | Element-wise subtraction. |
| `Vector *vector_mul(Vector *a, Vector *b)` | Element-wise multiplication. |
| `Vector *vector_div(Vector *a, Vector *b)` | Element-wise division (returns NULL if division by zero occurs). |

---
