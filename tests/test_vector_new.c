#include "layer_0/vector.h"
#include "unity.h"

void setUp(void) {}
void tearDown(void) {}

void test_new_vector(void) {
  Vector *v = new_vector(12);
  TEST_ASSERT_NOT_NULL(v);
  vector_free(v);
}

void test_new_vector_invalid(void) {
  Vector *v = new_vector(-2);
  TEST_ASSERT_NULL(v);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_new_vector);
  RUN_TEST(test_new_vector_invalid);
  return UNITY_END();
}
