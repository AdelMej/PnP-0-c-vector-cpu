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

void test_vector_get_basic(void) {
  vector_data_t val;

  TEST_ASSERT_EQUAL(VECTOR_OK, vector_get(test, 0, &val));
  TEST_ASSERT_EQUAL_DOUBLE(1.0, val);

  TEST_ASSERT_EQUAL(VECTOR_OK, vector_get(test, 1, &val));
  TEST_ASSERT_EQUAL_DOUBLE(2.0, val);

  TEST_ASSERT_EQUAL(VECTOR_OK, vector_get(test, 2, &val));
  TEST_ASSERT_EQUAL_DOUBLE(3.0, val);
}

void test_vector_get_null(void) {
  vector_data_t val;
  TEST_ASSERT_EQUAL(VECTOR_ERR_NULL, vector_get(NULL, 0, &val));
}

void test_vector_get_invalid_index(void) {
  vector_data_t val;
  TEST_ASSERT_EQUAL(VECTOR_ERR_OOB, vector_get(test, 5, &val));
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_vector_get_basic);
  RUN_TEST(test_vector_get_null);
  RUN_TEST(test_vector_get_invalid_index);
  return UNITY_END();
}
