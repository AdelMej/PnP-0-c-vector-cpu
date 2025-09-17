#include "Unity/unity_internals.h"
#include "layer_0/vector.h"
#include "unity.h"

Vector *a;
Vector *b;

void setUp(void) {
  a = vector_new(3);
  b = vector_new(3);
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

/* Basic multiplication */
void test_vector_mul_basic(void) {
  Vector *res = vector_mul(a, b);
  TEST_ASSERT_NOT_NULL(res);
  TEST_ASSERT_EQUAL_DOUBLE(4.0, res->data[0]);
  TEST_ASSERT_EQUAL_DOUBLE(-2.0, res->data[1]);
  TEST_ASSERT_EQUAL_DOUBLE(6.0, res->data[2]);
  vector_free(res);
}

/* Null pointer handling */
void test_vector_mul_null(void) {
  TEST_ASSERT_NULL(vector_mul(NULL, b));
  TEST_ASSERT_NULL(vector_mul(a, NULL));
  TEST_ASSERT_NULL(vector_mul(NULL, NULL));
}

/* Size mismatch handling */
void test_vector_mul_size_mismatch(void) {
  Vector *c = vector_new(2);
  TEST_ASSERT_NOT_NULL(c);
  TEST_ASSERT_NULL(vector_mul(a, c));
  TEST_ASSERT_NULL(vector_mul(c, b));
  vector_free(c);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_vector_mul_basic);
  RUN_TEST(test_vector_mul_null);
  RUN_TEST(test_vector_mul_size_mismatch);
  return UNITY_END();
}
