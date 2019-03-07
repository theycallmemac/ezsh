#include "../../../cu/cu.h"
// Declarations of tests
TEST(test19);
TEST(test20);

// Collect tests into test suite
TEST_SUITE(T7) {
    TEST_ADD(test19),
    TEST_ADD(test20),
    TEST_SUITE_CLOSURE
};
