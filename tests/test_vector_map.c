#include "layer_0/vector.h"
#include "unity.h"
#include "unity_internals.h"

Vector *test;

void setUp(void) {
  test = new_vector(12);
  TEST_ASSERT_NOT_NULL(test);
  // Push some initial values
  vector_push(test, 1.0);
  vector_push(test, 2.0);
  vector_push(test, 3.0);
}

void tearDown(void) {
  vector_free(test);
  test = NULL;
}

static vector_data_t multiply_by_two(vector_data_t x) { return x * 2; }

void test_vector_map_basic(void) {
  Vector *result = vector_map(test, multiply_by_two);
  TEST_ASSERT_NOT_NULL(result);
  TEST_ASSERT_EQUAL_UINT(3, result->size);
  TEST_ASSERT_EQUAL_DOUBLE(2.0, result->data[0]);
  TEST_ASSERT_EQUAL_DOUBLE(4.0, result->data[1]);
  TEST_ASSERT_EQUAL_DOUBLE(6.0, result->data[2]);

  vector_free(result);
}

void test_vector_map_null_vector(void) {
  TEST_ASSERT_NULL(vector_map(NULL, multiply_by_two));
}

void test_vector_map_null_function(void) {
  TEST_ASSERT_NULL(vector_map(test, NULL));
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_vector_map_basic);
  RUN_TEST(test_vector_map_null_vector);
  RUN_TEST(test_vector_map_null_function);
  return UNITY_END();
}
