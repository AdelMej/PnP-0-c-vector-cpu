#include "layer_0/vector.h"
#include "unity.h"

Vector *test;

void setUp(void) {
  test = vector_new(12);
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

void test_vector_set_basic(void) {
  TEST_ASSERT_EQUAL(VECTOR_OK, vector_set(test, 0, 42.0));
  TEST_ASSERT_EQUAL_DOUBLE(test->data[0], 42.0);
  TEST_ASSERT_EQUAL(VECTOR_OK, vector_set(test, 1, 42.0));
  TEST_ASSERT_EQUAL_DOUBLE(test->data[1], 42.0);
  TEST_ASSERT_EQUAL(VECTOR_OK, vector_set(test, 2, 42.0));
  TEST_ASSERT_EQUAL_DOUBLE(test->data[2], 42.0);
}

void test_vector_set_null(void) {
  TEST_ASSERT_EQUAL(VECTOR_ERR_NULL, vector_set(NULL, 0, 12.0));
}

void test_vector_set_invalid_index(void) {
  TEST_ASSERT_EQUAL(VECTOR_ERR_OOB, vector_set(test, 5, 12.0));
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_vector_set_basic);
  RUN_TEST(test_vector_set_null);
  RUN_TEST(test_vector_set_invalid_index);
  return UNITY_END();
}
