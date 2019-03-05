#include "../../../cu/cu.h"
// Declarations of tests
TEST(test16);
TEST(test17);
TEST(test18);

// Collect tests into test suite
TEST_SUITE(T6) {
    TEST_ADD(test16),
    TEST_ADD(test17),
    TEST_ADD(test18),
    TEST_SUITE_CLOSURE
};
