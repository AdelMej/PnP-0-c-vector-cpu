#include "layer_0/vector.h"
#include "unity.h"

static Vector *test;

void setUp(void) {
  test = new_vector(1);
  TEST_ASSERT_NOT_NULL(test);
}

void tearDown(void) { vector_free(test); }

void test_vector_push_basic(void) {
  vector_data_t d = 12.0;

  vector_push(test, d);
  TEST_ASSERT_EQUAL_DOUBLE(12.0, test->data[0]);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_vector_push_basic);
  return UNITY_END();
}
