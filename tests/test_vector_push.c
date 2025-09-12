#include "layer_0/vector.h"
#include "unity.h"
#include "unity_internals.h"

static Vector *test;

void setUp(void) {
  test = new_vector(1);
  TEST_ASSERT_NOT_NULL(test);
}

void tearDown(void) {
  vector_free(test);
  test = NULL;
}

void test_vector_push_basic(void) {
  vector_data_t d = 12.0;

  vector_push(test, d);
  TEST_ASSERT_EQUAL_DOUBLE(12.0, test->data[0]);
  TEST_ASSERT_EQUAL_UINT(1, test->size);
  TEST_ASSERT_EQUAL_UINT(1, test->capacity);
}

void test_vector_push_negative(void) {
  vector_data_t d = -12.0;

  vector_push(test, d);
  TEST_ASSERT_EQUAL_DOUBLE(-12.0, test->data[0]);
  TEST_ASSERT_EQUAL_UINT(1, test->size);
  TEST_ASSERT_EQUAL_UINT(1, test->capacity);
}

void test_vector_push_doubling(void) {
  size_t num_pushes = 10000;
  vector_data_t value;

  for (size_t i = 0; i < num_pushes; i++) {
    value = (vector_data_t)(i * 1.1); // example values: 0.0, 1.1, 2.2, ...
    vector_push(test, value);

    // Check that the value was inserted correctly
    TEST_ASSERT_EQUAL_DOUBLE(value, test->data[i]);

    // Check that size is correct
    TEST_ASSERT_EQUAL_UINT(i + 1, test->size);

    // Check that capacity is enough (>= size)
    TEST_ASSERT_TRUE(test->capacity >= test->size);
  }
}

void test_vector_push_null(void) {
  vector_data_t d = 3.12;

  vector_push(NULL, d);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_vector_push_basic);
  RUN_TEST(test_vector_push_negative);
  RUN_TEST(test_vector_push_doubling);
  RUN_TEST(test_vector_push_null);
  return UNITY_END();
}
