#include "layer_0/vector.h"
#include "unity.h"

Vector *test;

void setUp(void) {
  test = vector_new(5);
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

void test_vector_copy_basic(void) {
  Vector *copy = vector_copy(test);
  TEST_ASSERT_NOT_NULL(copy);
  TEST_ASSERT_EQUAL_UINT(test->size, copy->size);
  TEST_ASSERT_EQUAL_UINT(test->capacity, copy->capacity);
  for (size_t i = 0; i < test->size; ++i) {
    TEST_ASSERT_EQUAL_DOUBLE(test->data[i], copy->data[i]);
  }
  vector_free(copy);
}

void test_vector_copy_null(void) { TEST_ASSERT_NULL(vector_copy(NULL)); }

void test_vector_clear_null(void) {
  TEST_ASSERT_EQUAL(VECTOR_ERR_NULL, vector_clear(NULL));
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_vector_copy_basic);
  RUN_TEST(test_vector_copy_null);
  return UNITY_END();
}
