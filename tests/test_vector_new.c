#include "layer_0/vector.h"
#include "unity.h"

void setUp(void) {}
void tearDown(void) {}

void test_vector_new(void) {
  Vector *v = vector_new(12);
  TEST_ASSERT_NOT_NULL(v);
  vector_free(v);
}

void test_vector_new_invalid(void) {
  Vector *v = vector_new(-2);
  TEST_ASSERT_NULL(v);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_vector_new);
  RUN_TEST(test_vector_new_invalid);
  return UNITY_END();
}
