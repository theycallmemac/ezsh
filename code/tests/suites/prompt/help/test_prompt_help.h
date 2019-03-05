#include "../../../cu/cu.h"

// Declarations of tests
TEST(test13);
TEST(test14);
TEST(test15);

// Collect tests into test suite
TEST_SUITE(T5) {
    TEST_ADD(test13),
    TEST_ADD(test14),
    TEST_ADD(test15),
    TEST_SUITE_CLOSURE
};
