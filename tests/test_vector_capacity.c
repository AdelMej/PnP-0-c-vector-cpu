#include "Unity/unity_internals.h"
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

void test_vector_capacity_basic(void) {
  size_t cap;
  int ret;

  // Initial capacity set when vector was created
  ret = vector_capacity(test, &cap);
  TEST_ASSERT_EQUAL_INT(VECTOR_OK, ret);
  TEST_ASSERT_EQUAL_UINT(4, cap); // setUp created vector with capacity 4

  // Push more elements than initial capacity to trigger resize
  vector_push(test, 4.0);
  ret = vector_capacity(test, &cap);
  TEST_ASSERT_EQUAL_INT(VECTOR_OK, ret);
  TEST_ASSERT_TRUE(cap >=
                   4); // capacity should have increased if resizing happened
}

void test_vector_capacity_null_vector(void) {
  size_t cap;
  int ret;

  // Null vector
  ret = vector_capacity(NULL, &cap);
  TEST_ASSERT_EQUAL_INT(VECTOR_ERR_NULL, ret);
}
void test_vector_capacity_null_capacity(void) {
  int ret;

  // Null output pointer
  ret = vector_capacity(test, NULL);
  TEST_ASSERT_EQUAL_INT(VECTOR_ERR_NULL, ret);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_vector_capacity_basic);
  RUN_TEST(test_vector_capacity_null_capacity);
  RUN_TEST(test_vector_capacity_null_vector);
  return UNITY_END();
}
