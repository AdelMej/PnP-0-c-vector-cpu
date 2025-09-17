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

void test_vector_empty_basic(void) {
  int ret;

  // Vector has elements from setUp
  ret = vector_empty(test);
  TEST_ASSERT_EQUAL_INT(0, ret); // not empty

  // Clear the vector
  vector_clear(test);
  ret = vector_empty(test);
  TEST_ASSERT_EQUAL_INT(1, ret); // now empty
}

void test_vector_empty_null(void) {
  int ret;

  // Null vector should return 0
  ret = vector_empty(NULL);
  TEST_ASSERT_EQUAL_INT(-1, ret);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_vector_empty_basic);
  RUN_TEST(test_vector_empty_null);
  return UNITY_END();
}
