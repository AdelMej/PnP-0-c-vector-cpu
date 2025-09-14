#include "layer_0/vector.h"
#include "unity.h"

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

void test_vector_back_basic(void) {
  vector_data_t val;
  TEST_ASSERT_EQUAL(VECTOR_OK, vector_back(test, &val));
  TEST_ASSERT_EQUAL_DOUBLE(3.0, val);

  // Size should stay the same
  TEST_ASSERT_EQUAL_UINT(3, test->size);
}

void test_vector_back_empty(void) {
  vector_data_t val;
  vector_pop(test, &val);
  vector_pop(test, &val);
  vector_pop(test, &val);

  TEST_ASSERT_EQUAL(VECTOR_ERR_EMPTY, vector_back(test, &val));
}

void test_vector_back_null(void) {
  vector_data_t val;
  TEST_ASSERT_EQUAL(VECTOR_ERR_NULL, vector_back(NULL, &val));
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_vector_back_basic);
  RUN_TEST(test_vector_back_empty);
  RUN_TEST(test_vector_back_null);
  return UNITY_END();
}
