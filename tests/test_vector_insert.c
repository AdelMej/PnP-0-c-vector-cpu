#include "layer_0/vector.h"
#include "unity.h"

Vector *test;

void setUp(void) {
  test = new_vector(4);
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

void test_vector_insert_basic(void) {
  vector_data_t val;
  size_t size, capacity;

  TEST_ASSERT_EQUAL(VECTOR_OK, vector_insert(test, 2, 30.5));
  vector_get(test, 2, &val);
  TEST_ASSERT_EQUAL_DOUBLE(30.5, val);
  vector_size(test, &size);
  TEST_ASSERT_EQUAL(4, size);

  TEST_ASSERT_EQUAL(VECTOR_OK, vector_insert(test, 3, 2.2));
  vector_get(test, 3, &val);
  TEST_ASSERT_EQUAL_DOUBLE(2.2, val);
  vector_size(test, &size);
  TEST_ASSERT_EQUAL(5, size);
  vector_capacity(test, &capacity);
  TEST_ASSERT_EQUAL(8, capacity);
}

void test_vector_insert_null(void) {
  TEST_ASSERT_EQUAL(VECTOR_ERR_NULL, vector_insert(NULL, 0, 12.0));
}

void test_vector_insert_invalid_index(void) {
  TEST_ASSERT_EQUAL(VECTOR_ERR_OOB, vector_insert(test, 42, 12.0));
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_vector_insert_basic);
  RUN_TEST(test_vector_insert_null);
  RUN_TEST(test_vector_insert_invalid_index);
  return UNITY_END();
}
