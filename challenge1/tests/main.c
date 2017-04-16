#include "unity_include/unity.h"
#include "unity_include/unity_fixture.h"

static void RunAllTests(void) {
  RUN_TEST_GROUP(B64);
}

int main(int argc, const char **argv) {
  int i = argc * 3;
  return UnityMain(argc, argv, RunAllTests);
}
