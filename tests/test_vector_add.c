#include "Unity/unity_internals.h"
#include "layer_0/vector.h"
#include "unity.h"

Vector *a;
Vector *b;

void setUp(void) {
  a = new_vector(3);
  b = new_vector(3);
  TEST_ASSERT_NOT_NULL(a);
  TEST_ASSERT_NOT_NULL(b);

  vector_push(a, 1.0);
  vector_push(a, 2.0);
  vector_push(a, 3.0);

  vector_push(b, 4.0);
  vector_push(b, -1.0);
  vector_push(b, 2.0);
}

void tearDown(void) {
  vector_free(a);
  vector_free(b);
}

void test_vector_add_basic(void) {
  Vector *res = vector_add(a, b);
  TEST_ASSERT_NOT_NULL(res);
  TEST_ASSERT_EQUAL_DOUBLE(5.0, res->data[0]);
  TEST_ASSERT_EQUAL_DOUBLE(1.0, res->data[1]);
  TEST_ASSERT_EQUAL_DOUBLE(5.0, res->data[2]);
  vector_free(res);
}

void test_vector_add_null(void) {
  TEST_ASSERT_NULL(vector_add(NULL, b));
  TEST_ASSERT_NULL(vector_add(a, NULL));
  TEST_ASSERT_NULL(vector_add(NULL, NULL));
}

void test_vector_add_size_mismatch(void) {
  Vector *c = new_vector(2);
  TEST_ASSERT_NOT_NULL(c);
  TEST_ASSERT_NULL(vector_add(a, c));
  TEST_ASSERT_NULL(vector_add(c, b));
  vector_free(c);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_vector_add_basic);
  RUN_TEST(test_vector_add_null);
  RUN_TEST(test_vector_add_size_mismatch);
  return UNITY_END();
}
