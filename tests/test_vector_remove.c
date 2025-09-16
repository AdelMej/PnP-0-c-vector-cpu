#include "layer_0/vector.h"
#include "unity.h"

Vector *test;

void setUp(void) {
  test = new_vector(4);
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

void test_vector_remove_basic(void) {
  size_t size;

  TEST_ASSERT_EQUAL(VECTOR_OK, vector_remove(test, 2));
  vector_size(test, &size);
  TEST_ASSERT_EQUAL(size, 2);

  TEST_ASSERT_EQUAL(VECTOR_OK, vector_remove(test, 1));
  vector_size(test, &size);
  TEST_ASSERT_EQUAL(1, size);
}

void test_vector_remove_null(void) {
  TEST_ASSERT_EQUAL(VECTOR_ERR_NULL, vector_remove(NULL, 0));
}

void test_vector_remove_invalid_index(void) {
  TEST_ASSERT_EQUAL(VECTOR_ERR_OOB, vector_remove(test, 42));
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_vector_remove_basic);
  RUN_TEST(test_vector_remove_null);
  RUN_TEST(test_vector_remove_invalid_index);
  return UNITY_END();
}
