#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(B64) {
  RUN_TEST_CASE(B64, B64Encode_EncodesCorrectlyWritesCorrectResult);
  RUN_TEST_CASE(B64, B64Encode_SrcIsEmpty_KeepsSamePointerInDest);
  RUN_TEST_CASE(B64, B64Encode_EncodesCorrectlyReturnsCorrectLength); 
  RUN_TEST_CASE(B64, B64Encode_NULLPassedAsSrc_NULLWrittenToDest);
  RUN_TEST_CASE(B64, B64Encode_NULLPassedAsSrc_ReturnsZeroLength);
  RUN_TEST_CASE(B64, B64EncodeToString_EncodesCorrectlyWritesCorrectResult); 
  RUN_TEST_CASE(B64, B64EncodeToString_SrcIsEmpty_ResultsInEmptyStringInDest);
  RUN_TEST_CASE(B64, B64EncodeToString_SrcIsEmpty_ReturnsZero);
  RUN_TEST_CASE(B64, B64EncodeToString_EncodesCorrectlyReturnsCorrectLength);
  RUN_TEST_CASE(B64, B64EncodeToString_NULLPassedAsSrc_NULLWrittenToDest);
  RUN_TEST_CASE(B64, B64EncodeToString_NULLPassedAsSrc_ReturnsNegOne);
}
