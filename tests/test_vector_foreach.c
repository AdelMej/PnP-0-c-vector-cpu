#include "layer_0/vector.h"
#include "unity.h"

Vector *test;

static double sum;

static void add_to_sum(vector_data_t *elem) { sum += *elem; }

void setUp(void) {
  test = new_vector(12);
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

void test_vector_foreach_basic(void) {
  sum = 0; // reset before test
  TEST_ASSERT_EQUAL_INT(VECTOR_OK, vector_foreach(test, add_to_sum));
  TEST_ASSERT_EQUAL_DOUBLE(6.0, sum); // 1 + 2 + 3 from setup
}

void test_vector_foreach_null(void) {
  TEST_ASSERT_EQUAL_INT(VECTOR_ERR_NULL, vector_foreach(NULL, NULL));
  TEST_ASSERT_EQUAL_INT(VECTOR_ERR_NULL, vector_foreach(test, NULL));
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_vector_foreach_basic);
  RUN_TEST(test_vector_foreach_null);
  return UNITY_END();
}
