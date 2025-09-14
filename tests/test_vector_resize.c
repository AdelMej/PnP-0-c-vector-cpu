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

void test_vector_resize_expand(void) {
  size_t old_capacity = test->capacity;
  TEST_ASSERT_EQUAL(VECTOR_OK, vector_resize(test, 10));
  TEST_ASSERT_EQUAL(10, test->capacity);
  TEST_ASSERT_EQUAL(3, test->size); // data preserved
  TEST_ASSERT_EQUAL_FLOAT(1.0, test->data[0]);
  TEST_ASSERT_EQUAL_FLOAT(2.0, test->data[1]);
  TEST_ASSERT_EQUAL_FLOAT(3.0, test->data[2]);
  TEST_ASSERT_TRUE(test->capacity > old_capacity);
}

void test_vector_resize_shrink(void) {
  TEST_ASSERT_EQUAL(VECTOR_OK, vector_resize(test, 2));
  TEST_ASSERT_EQUAL(2, test->capacity);
  TEST_ASSERT_EQUAL(2, test->size); // shrinks down
  TEST_ASSERT_EQUAL_FLOAT(1.0, test->data[0]);
  TEST_ASSERT_EQUAL_FLOAT(2.0, test->data[1]);
}

void test_vector_resize_zero(void) {
  // Valid vector
  Vector *v = new_vector(4);
  TEST_ASSERT_NOT_NULL(v);

  // Try resizing to 0 → should fail
  TEST_ASSERT_EQUAL(VECTOR_ERR_OOB, vector_resize(v, 0));

  // Vector should remain unchanged
  TEST_ASSERT_EQUAL_UINT(4, v->capacity);
  TEST_ASSERT_EQUAL_UINT(0, v->size);

  vector_free(v);
}

void test_vector_resize_null(void) {
  TEST_ASSERT_EQUAL(VECTOR_ERR_NULL, vector_resize(NULL, 10));
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_vector_resize_expand);
  RUN_TEST(test_vector_resize_shrink);
  RUN_TEST(test_vector_resize_zero);
  RUN_TEST(test_vector_resize_null);
  return UNITY_END();
}
