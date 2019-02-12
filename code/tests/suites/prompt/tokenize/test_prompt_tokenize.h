#include "../../../cu/cu.h"
// Declarations of tests
TEST(test1);
TEST(test2);

// Collect tests into test suite
TEST_SUITE(T1) {
    TEST_ADD(test1),
    TEST_ADD(test2),
    TEST_SUITE_CLOSURE
};
