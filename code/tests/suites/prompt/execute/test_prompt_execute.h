#include "../../../cu/cu.h"
// Declarations of tests
TEST(test7);
TEST(test8);
TEST(test9);

// Collect tests into test suite
TEST_SUITE(T3) {
    TEST_ADD(test7),
    TEST_ADD(test8),
    TEST_ADD(test9),
    TEST_SUITE_CLOSURE
};
