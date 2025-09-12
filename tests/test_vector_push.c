#include "layer_0/vector.h"
#include "unity.h"
#include "unity_internals.h"

static Vector *test;

void setUp(void) {
  test = new_vector(1);
  TEST_ASSERT_NOT_NULL(test);
}

void tearDown(void) {
  vector_free(test);
  test = NULL;
}

void test_vector_push_basic(void) {
  vector_data_t d = 12.0;

  vector_push(test, d);
  TEST_ASSERT_EQUAL_DOUBLE(12.0, test->data[0]);
  TEST_ASSERT_EQUAL_UINT(1, test->size);
  TEST_ASSERT_EQUAL_UINT(1, test->capacity);
}

void test_vector_push_negative(void) {
  vector_data_t d = -12.0;

  vector_push(test, d);
  TEST_ASSERT_EQUAL_DOUBLE(-12.0, test->data[0]);
  TEST_ASSERT_EQUAL_UINT(1, test->size);
  TEST_ASSERT_EQUAL_UINT(1, test->capacity);
}

void test_vector_push_doubling(void) {
  vector_data_t d = 2.56;

  vector_push(test, d);
  TEST_ASSERT_EQUAL_DOUBLE(2.56, test->data[0]);
  TEST_ASSERT_EQUAL_UINT(1, test->size);
  TEST_ASSERT_EQUAL_UINT(1, test->capacity);

  d = 3.2;
  vector_push(test, d);
  TEST_ASSERT_EQUAL_DOUBLE(3.2, test->data[1]);
  TEST_ASSERT_EQUAL_UINT(2, test->size);
  TEST_ASSERT_EQUAL_UINT(2, test->capacity);

  d = 4.2;
  vector_push(test, d);
  TEST_ASSERT_EQUAL_DOUBLE(4.2, test->data[2]);
  TEST_ASSERT_EQUAL_UINT(3, test->size);
  TEST_ASSERT_EQUAL_UINT(4, test->capacity);
}

void test_vector_push_null(void) {
  vector_data_t d = 3.12;

  vector_push(NULL, d);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_vector_push_basic);
  RUN_TEST(test_vector_push_negative);
  RUN_TEST(test_vector_push_doubling);
  RUN_TEST(test_vector_push_null);
  return UNITY_END();
}
