#include "../../cu/cu.h"
// Declarations of tests
TEST(test8);
TEST(test9);
TEST(test10);

// Collect tests into test suite
TEST_SUITE(T3) {
    TEST_ADD(test8),
    TEST_ADD(test9),
    TEST_ADD(test10),
    TEST_SUITE_CLOSURE
};
