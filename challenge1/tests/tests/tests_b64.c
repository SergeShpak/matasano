#include "unity.h"
#include "unity_fixture.h"
#include "b64.h"

TEST_GROUP(B64);

TEST_SETUP(B64) {}
TEST_TEAR_DOWN(B64) {}

TEST(B64, Add_Correct) {
  int first = 5;
  int second = 6;
  int result = add(first, second);
  TEST_ASSERT_EQUAL_INT(11, result);
}
