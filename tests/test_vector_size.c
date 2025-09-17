#include "Unity/unity_internals.h"
#include "layer_0/vector.h"
#include "unity.h"

Vector *test;

void setUp(void) {
  test = vector_new(4);
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

void test_vector_size_basic(void) {
  size_t size;
  int ret;

  // Check initial size (3 elements pushed in setUp)
  ret = vector_size(test, &size);
  TEST_ASSERT_EQUAL_INT(VECTOR_OK, ret);
  TEST_ASSERT_EQUAL_UINT(3, size);

  // Push one more element
  vector_push(test, 4.0);
  ret = vector_size(test, &size);
  TEST_ASSERT_EQUAL_INT(VECTOR_OK, ret);
  TEST_ASSERT_EQUAL_UINT(4, size);
}

void test_vector_size_null_vector(void) {
  size_t size;
  int ret;

  ret = vector_size(NULL, &size);
  TEST_ASSERT_EQUAL_INT(VECTOR_ERR_NULL, ret);
}

void test_vector_size_null_size(void) {
  int ret;

  ret = vector_size(test, NULL);
  TEST_ASSERT_EQUAL_INT(VECTOR_ERR_NULL, ret);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_vector_size_basic);
  RUN_TEST(test_vector_size_null_size);
  RUN_TEST(test_vector_size_null_vector);
  return UNITY_END();
}
