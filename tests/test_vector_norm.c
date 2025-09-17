#include "Unity/unity_internals.h"
#include "layer_0/vector.h"
#include "unity.h"
#include <math.h>

Vector *v;

void setUp(void) {
  v = vector_new(4);
  TEST_ASSERT_NOT_NULL(v);

  // Push some initial values
  vector_push(v, 3.0);
  vector_push(v, 4.0);
}

void tearDown(void) { vector_free(v); }

void test_vector_norm_basic(void) {
  vector_data_t result;
  TEST_ASSERT_EQUAL(VECTOR_OK, vector_norm(v, &result));
  TEST_ASSERT_DOUBLE_WITHIN(1e-9, 5.0, result); // sqrt(3^2 + 4^2) = 5
}
void test_vector_norm_null(void) {
  vector_data_t result;
  TEST_ASSERT_EQUAL(VECTOR_ERR_NULL, vector_norm(NULL, &result));
  TEST_ASSERT_EQUAL(VECTOR_ERR_NULL, vector_norm(v, NULL));
}

void test_vector_norm_empty(void) {
  vector_clear(v);
  vector_data_t result;
  TEST_ASSERT_EQUAL(VECTOR_OK, vector_norm(v, &result));
  TEST_ASSERT_EQUAL_DOUBLE(0.0, result);
}

void test_vector_norm_negative(void) {
  vector_clear(v);
  vector_push(v, -3.0);
  vector_push(v, -4.0);
  vector_data_t result;
  TEST_ASSERT_EQUAL(VECTOR_OK, vector_norm(v, &result));
  TEST_ASSERT_DOUBLE_WITHIN(1e-9, 5.0, result); // sqrt((-3)^2 + (-4)^2) = 5
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_vector_norm_basic);
  RUN_TEST(test_vector_norm_empty);
  RUN_TEST(test_vector_norm_null);
  RUN_TEST(test_vector_norm_negative);
  return UNITY_END();
}
