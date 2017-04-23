#include "unity.h"
#include "unity_fixture.h"
#include "b64/b64.h"

TEST_GROUP(B64);

TEST_SETUP(B64) {}
TEST_TEAR_DOWN(B64) {}

TEST(B64, B64Encode_EncodesCorrectlyWritesCorrectResult) {
  uint8_t *result = NULL;
  const char *first = "f";
  const size_t first_size = 1;
  const uint8_t first_expected[] = {0x5a, 0x67, 0x3d, 0x3d};
  const size_t first_expected_size = 4;
  b64_encode((const uint8_t*)first, first_size, &result);
  TEST_ASSERT_EQUAL_UINT8_ARRAY(first_expected, result, first_expected_size);
  const char *second = "fo";
  const size_t second_size = 2;
  const uint8_t second_expected[] = {0x5a, 0x6d, 0x38, 0x3d};
  const size_t second_expected_size = 4;
  b64_encode((const uint8_t*)second, second_size, &result);
  TEST_ASSERT_EQUAL_UINT8_ARRAY(second_expected, result, second_expected_size);
  const char *third = "foo";
  const size_t third_size = 3;
  const uint8_t third_expected[] = {0x5a, 0x6d, 0x39, 0x76};
  const size_t third_expected_size = 4;
  b64_encode((const uint8_t*)third, third_size, &result);
  TEST_ASSERT_EQUAL_UINT8_ARRAY(third_expected, result, third_expected_size);
  const char *fourth = "foob";
  const size_t fourth_size = 4;
  const uint8_t fourth_expected[] = {0x5a, 0x6d, 0x39, 0x76, 0x59, 0x67, 0x3d,
    0x3d};
  const size_t fourth_expected_size = 8;
  b64_encode((const uint8_t*)fourth, fourth_size, &result);
  TEST_ASSERT_EQUAL_UINT8_ARRAY(fourth_expected, result, fourth_expected_size);
  const char *fifth = "fooba";
  const size_t fifth_size = 5;
  const uint8_t fifth_expected[] = {0x5a, 0x6d, 0x39, 0x76, 0x59, 0x6d, 0x45,
    0x3d};
  const size_t fifth_expected_size = 8;
  b64_encode((const uint8_t*)fifth, fifth_size, &result);
  TEST_ASSERT_EQUAL_UINT8_ARRAY(fifth_expected, result, fifth_expected_size);
  const char *sixth = "foobar";
  const size_t sixth_size = 6;
  const uint8_t sixth_expected[] = {0x5a, 0x6d, 0x39, 0x76, 0x59, 0x6d, 0x46,
    0x79};
  const size_t sixth_expected_size = 8;
  b64_encode((const uint8_t*)sixth, sixth_size, &result);
  TEST_ASSERT_EQUAL_UINT8_ARRAY(sixth_expected, result, sixth_expected_size);
}

TEST(B64, B64Encode_SrcIsEmpty_KeepsSamePointerInDest) {
  uint8_t dummy[] = {0x42};
  uint8_t *result = dummy;
  const uint8_t src[] = {};
  const size_t src_length = 0;
  b64_encode(src, src_length, &result);
  TEST_ASSERT_POINTERS_EQUAL(dummy, result);
}

TEST(B64, B64Encode_EncodesCorrectlyReturnsCorrectLength) {
  uint8_t *result = NULL;
  size_t result_length;
  const char *first = "f";
  const size_t first_size = 1;
  const size_t first_expected_size = 4;
  result_length = b64_encode((const uint8_t*)first, first_size, &result);
  TEST_ASSERT_EQUAL_UINT16(first_expected_size, result_length);
  const char *second = "fo";
  const size_t second_size = 2;
  const size_t second_expected_size = 4;
  result_length = b64_encode((const uint8_t*)second, second_size, &result);
  TEST_ASSERT_EQUAL_UINT16(second_expected_size, result_length);
  const char *third = "foo";
  const size_t third_size = 3;
  const size_t third_expected_size = 4;
  result_length = b64_encode((const uint8_t*)third, third_size, &result);
  TEST_ASSERT_EQUAL_UINT16(third_expected_size, result_length);
  const char *fourth = "foob";
  const size_t fourth_size = 4;
  const size_t fourth_expected_size = 8;
  result_length = b64_encode((const uint8_t*)fourth, fourth_size, &result);
  TEST_ASSERT_EQUAL_UINT16(fourth_expected_size, result_length);
  const char *fifth = "fooba";
  const size_t fifth_size = 5;
  const size_t fifth_expected_size = 8;
  result_length = b64_encode((const uint8_t*)fifth, fifth_size, &result);
  TEST_ASSERT_EQUAL_UINT16(fifth_expected_size, result_length);
  const char *sixth = "foobar";
  const size_t sixth_size = 6;
  const size_t sixth_expected_size = 8;
  result_length = b64_encode((const uint8_t*)sixth, sixth_size, &result);
  TEST_ASSERT_EQUAL_UINT16(sixth_expected_size, result_length);
}

TEST(B64, B64Encode_NULLPassedAsSrc_NULLWrittenToDest) {
  uint8_t dummy[] = { 0x42 };
  uint8_t *result = dummy;
  const char *src = NULL;
  b64_encode((const uint8_t*)src, 0, &result);
  TEST_ASSERT_NULL(result);
}

TEST(B64, B64Encode_NULLPassedAsSrc_ReturnsZeroLength) {
  uint8_t dummy[] = { 0x42 };
  uint8_t *result = dummy;
  const char *src = NULL;
  size_t result_length = b64_encode((const uint8_t*)src, 0, &result);
  TEST_ASSERT_EQUAL_UINT16(0, result_length);
}

TEST(B64, B64EncodeToString_EncodesCorrectlyWritesCorrectResult) {
  char *result = NULL;
  const char *first = "f";
  const size_t first_size = 1;
  const char *first_expected = "Zg==";
  b64_encode_to_string((const uint8_t*)first, first_size, &result);
  TEST_ASSERT_EQUAL_STRING(first_expected, result);
  const char *second = "fo";
  const size_t second_size = 2;
  const char *second_expected = "Zm8=";
  b64_encode_to_string((const uint8_t*)second, second_size, &result);
  TEST_ASSERT_EQUAL_STRING(second_expected, result);
  const char *third = "foo";
  const size_t third_size = 3;
  const char *third_expected = "Zm9v";
  b64_encode_to_string((const uint8_t*)third, third_size, &result);
  TEST_ASSERT_EQUAL_STRING(third_expected, result);
  const char *fourth = "foob";
  const size_t fourth_size = 4;
  const char *fourth_expected = "Zm9vYg==";
  b64_encode_to_string((const uint8_t*)fourth, fourth_size, &result);
  TEST_ASSERT_EQUAL_STRING(fourth_expected, result);
  const char *fifth = "fooba";
  const size_t fifth_size = 5;
  const char *fifth_expected = "Zm9vYmE=";
  b64_encode_to_string((const uint8_t*)fifth, fifth_size, &result);
  TEST_ASSERT_EQUAL_STRING(fifth_expected, result);
  const char *sixth = "foobar";
  const size_t sixth_size = 6;
  const char *sixth_expected = "Zm9vYmFy";
  b64_encode_to_string((const uint8_t*)sixth, sixth_size, &result);
  TEST_ASSERT_EQUAL_STRING(sixth_expected, result);
}

TEST(B64, B64EncodeToString_SrcIsEmpty_ResultsInEmptyStringInDest) {
  char *dummy = "42";
  char *result = dummy;
  const uint8_t src[] = {};
  const size_t src_length = 0;
  b64_encode_to_string(src, src_length, &result);
  TEST_ASSERT_EQUAL_STRING("", result);
}

TEST(B64, B64EncodeToString_SrcIsEmpty_ReturnsZero) {
  char *dummy = "42";
  char *result = dummy;
  const uint8_t src[] = {};
  const size_t src_length = 0;
  size_t result_size = b64_encode_to_string(src, src_length, &result);
  TEST_ASSERT_EQUAL_UINT16(0, result_size);
}

TEST(B64, B64EncodeToString_EncodesCorrectlyReturnsCorrectLength) {
  char *result = NULL;
  size_t result_size;
  const char *first = "f";
  const size_t first_size = 1;
  const size_t first_expected_size = 4;
  result_size = b64_encode_to_string((const uint8_t*)first, first_size, 
      &result);
  TEST_ASSERT_EQUAL_UINT16(first_expected_size, result_size);
  const char *second = "fo";
  const size_t second_size = 2;
  const size_t second_expected_size = 4;
  result_size = b64_encode_to_string((const uint8_t*)second, second_size, 
      &result);
  TEST_ASSERT_EQUAL_UINT16(second_expected_size, result_size);
  const char *third = "foo";
  const size_t third_size = 3;
  const size_t third_expected_size = 4;
  result_size = b64_encode_to_string((const uint8_t*)third, third_size, 
      &result);
  TEST_ASSERT_EQUAL_UINT16(third_expected_size, result_size);
  const char *fourth = "foob";
  const size_t fourth_size = 4;
  const size_t fourth_expected_size = 8;
  result_size = b64_encode_to_string((const uint8_t*)fourth, fourth_size, 
      &result);
  TEST_ASSERT_EQUAL_UINT16(fourth_expected_size, result_size);
  const char *fifth = "fooba";
  const size_t fifth_size = 5;
  const size_t fifth_expected_size = 8;
  result_size = b64_encode_to_string((const uint8_t*)fifth, fifth_size, 
      &result);
  TEST_ASSERT_EQUAL_UINT16(fifth_expected_size, result_size);
  const char *sixth = "foobar";
  const size_t sixth_size = 6;
  const size_t sixth_expected_size = 8;
  result_size = b64_encode_to_string((const uint8_t*)sixth, sixth_size, 
      &result);
  TEST_ASSERT_EQUAL_UINT16(sixth_expected_size, result_size);
}

TEST(B64, B64EncodeToString_NULLPassedAsSrc_NULLWrittenToDest) {
  char *dummy = "42";
  char *result = dummy;
  const char *src = NULL;
  b64_encode_to_string((const uint8_t*)src, 0, &result);
  TEST_ASSERT_NULL(result);
}

TEST(B64, B64EncodeToString_NULLPassedAsSrc_ReturnsNegOne) {
  char *dummy = "42";
  char *result = dummy;
  const char *src = NULL;
  size_t result_length = b64_encode_to_string((const uint8_t*)src, 0, &result);
  TEST_ASSERT_EQUAL_UINT16(-1, result_length);
}
