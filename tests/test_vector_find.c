#include "layer_0/vector.h"
#include "unity.h"
#include "unity_internals.h"
#include <math.h>

Vector *test;

static int is_even(vector_data_t elem) { return fmod(elem, 2.0) == 0.0; }

static int is_negative(vector_data_t elem) { return elem < 0; }
void setUp(void) {
  test = vector_new(12);
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

void test_vector_find_even_number(void) {
  ssize_t idx = vector_find(test, is_even);

  TEST_ASSERT_EQUAL_INT(1, idx); // 4 is at index 2
}

void test_vector_find_negative_number(void) {
  vector_set(test, 2, -2.0);
  ssize_t idx = vector_find(test, is_negative);

  TEST_ASSERT_EQUAL_INT(2, idx); // -10 is at index 1
}

void test_vector_find_no_match(void) {
  vector_set(test, 1, 5.0);
  ssize_t idx = vector_find(test, is_even);

  TEST_ASSERT_EQUAL_INT(-1, idx); // no even numbers
}

void test_vector_find_null_vector(void) {
  ssize_t idx = vector_find(NULL, is_even);
  TEST_ASSERT_EQUAL(-1, idx);
}

void test_vector_find_null_function(void) {
  ssize_t idx = vector_find(test, NULL);
  TEST_ASSERT_EQUAL(-1, idx);
}

void test_vector_find_empty_vector(void) {
  vector_clear(test);
  ssize_t idx = vector_find(test, is_even);

  TEST_ASSERT_EQUAL_INT(-1, idx); // nothing to match
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_vector_find_negative_number);
  RUN_TEST(test_vector_find_even_number);
  RUN_TEST(test_vector_find_no_match);
  RUN_TEST(test_vector_find_null_vector);
  RUN_TEST(test_vector_find_null_function);
  RUN_TEST(test_vector_find_empty_vector);
  return UNITY_END();
}
