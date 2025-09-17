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

void test_vector_pop_basic(void) {
  vector_data_t val;

  // Pop last element
  TEST_ASSERT_EQUAL(VECTOR_OK, vector_pop(test, &val));
  TEST_ASSERT_EQUAL_DOUBLE(3.0, val);
  TEST_ASSERT_EQUAL_UINT(2, test->size);

  // Pop again
  TEST_ASSERT_EQUAL(VECTOR_OK, vector_pop(test, &val));
  TEST_ASSERT_EQUAL_DOUBLE(2.0, val);
  TEST_ASSERT_EQUAL_UINT(1, test->size);
}

void test_vector_pop_empty(void) {
  vector_data_t val;
  // Pop all elements first
  vector_pop(test, &val);
  vector_pop(test, &val);
  vector_pop(test, &val);

  TEST_ASSERT_EQUAL(VECTOR_ERR_EMPTY, vector_pop(test, &val));
}

void test_vector_pop_null(void) {
  vector_data_t val;
  TEST_ASSERT_EQUAL(VECTOR_ERR_NULL, vector_pop(NULL, &val));
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_vector_pop_basic);
  RUN_TEST(test_vector_pop_empty);
  RUN_TEST(test_vector_pop_null);
  return UNITY_END();
}
