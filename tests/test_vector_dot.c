#include "Unity/unity_internals.h"
#include "layer_0/vector.h"
#include "unity.h"

Vector *a;
Vector *b;

void setUp(void) {
  a = vector_new(4);
  b = vector_new(4);
  TEST_ASSERT_NOT_NULL(a);
  TEST_ASSERT_NOT_NULL(b);

  // Push some initial values
  vector_push(a, 1.0);
  vector_push(a, 2.0);
  vector_push(a, 3.0);

  vector_push(b, 4.0);
  vector_push(b, 5.0);
  vector_push(b, 6.0);
}

void tearDown(void) {
  vector_free(a);
  vector_free(b);
}

void test_vector_dot_basic(void) {
  vector_data_t result;

  TEST_ASSERT_EQUAL(VECTOR_OK, vector_dot(a, b, &result));
  TEST_ASSERT_EQUAL_DOUBLE(32.0, result);
}

void test_vector_dot_null(void) {
  vector_data_t result;

  TEST_ASSERT_EQUAL(VECTOR_ERR_NULL, vector_dot(NULL, b, &result));
  TEST_ASSERT_EQUAL(VECTOR_ERR_NULL, vector_dot(a, NULL, &result));
  TEST_ASSERT_EQUAL(VECTOR_ERR_NULL, vector_dot(a, b, NULL));
}

void test_vector_dot_size_missmatch(void) {
  Vector *c = vector_new(2); // smaller vector
  vector_push(c, 1.0);
  vector_push(c, 2.0);

  vector_data_t result;

  // a has 3 elements, c has 2 elements
  TEST_ASSERT_EQUAL(VECTOR_ERR_SIZE, vector_dot(a, c, &result));
  TEST_ASSERT_EQUAL(VECTOR_ERR_SIZE, vector_dot(c, a, &result));

  vector_free(c);
}

void test_vector_dot_empty(void) {
  Vector *empty1 = vector_new(1);
  Vector *empty2 = vector_new(1);
  vector_data_t result;

  TEST_ASSERT_NOT_NULL(empty1);
  TEST_ASSERT_NOT_NULL(empty2);

  // size is 0, capacity is 1
  TEST_ASSERT_EQUAL(VECTOR_OK, vector_dot(empty1, empty2, &result));
  TEST_ASSERT_EQUAL_DOUBLE(0.0, result);

  vector_free(empty1);
  vector_free(empty2);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_vector_dot_basic);
  RUN_TEST(test_vector_dot_null);
  RUN_TEST(test_vector_dot_size_missmatch);
  return UNITY_END();
}
