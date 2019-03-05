#include "../../../cu/cu.h"

// Declarations of tests
TEST(test10);
TEST(test11);
TEST(test12);

// Collect tests into test suite
TEST_SUITE(T4) {
    TEST_ADD(test10),
    TEST_ADD(test11),
    TEST_ADD(test12),
    TEST_SUITE_CLOSURE
};
