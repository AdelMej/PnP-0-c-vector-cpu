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

  vector_push(a, 10.0);
  vector_push(a, 20.0);
  vector_push(a, 30.0);

  vector_push(b, 2.0);
  vector_push(b, 4.0);
  vector_push(b, 5.0);
}

void tearDown(void) {
  vector_free(a);
  vector_free(b);
}

void test_vector_div_basic(void) {
  Vector *result = vector_div(a, b);
  TEST_ASSERT_NOT_NULL(result);

  TEST_ASSERT_EQUAL_DOUBLE(5.0, result->data[0]);
  TEST_ASSERT_EQUAL_DOUBLE(5.0, result->data[1]);
  TEST_ASSERT_EQUAL_DOUBLE(6.0, result->data[2]);

  vector_free(result);
}

void test_vector_div_null(void) {
  TEST_ASSERT_NULL(vector_div(NULL, b));
  TEST_ASSERT_NULL(vector_div(a, NULL));
  TEST_ASSERT_NULL(vector_div(NULL, NULL));
}

void test_vector_div_size_mismatch(void) {
  Vector *c = new_vector(2);
  vector_push(c, 1.0);
  vector_push(c, 2.0);

  TEST_ASSERT_NULL(vector_div(a, c));
  TEST_ASSERT_NULL(vector_div(c, a));

  vector_free(c);
}

void test_vector_div_zero(void) {
  Vector *x = new_vector(3);
  Vector *y = new_vector(3);
  x->data[0] = 1.0;
  x->data[1] = 2.0;
  x->data[2] = 3.0;
  y->data[0] = 1.0;
  y->data[1] = 0.0;
  y->data[2] = 2.0;

  Vector *result = vector_div(x, y);
  TEST_ASSERT_NULL(result);

  vector_free(x);
  vector_free(y);
}

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_vector_div_basic);
  RUN_TEST(test_vector_div_null);
  RUN_TEST(test_vector_div_size_mismatch);
  RUN_TEST(test_vector_div_zero);

  return UNITY_END();
}
