#include "layer_0/vector.h"
#include "unity.h"

Vector *test;

void setUp(void) {
  test = new_vector(5);
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

void test_vector_clear_basic(void) {
  TEST_ASSERT_EQUAL(VECTOR_OK, vector_clear(test));
  TEST_ASSERT_EQUAL_UINT(0, test->size);
  // Capacity should remain unchanged
  TEST_ASSERT_EQUAL_UINT(5, test->capacity);
}

void test_vector_clear_empty(void) {
  vector_clear(test); // make it empty first
  TEST_ASSERT_EQUAL(VECTOR_OK, vector_clear(test));
  TEST_ASSERT_EQUAL_UINT(0, test->size);
}

void test_vector_clear_null(void) {
  TEST_ASSERT_EQUAL(VECTOR_ERR_NULL, vector_clear(NULL));
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_vector_clear_basic);
  RUN_TEST(test_vector_clear_empty);
  RUN_TEST(test_vector_clear_null);
  return UNITY_END();
}
