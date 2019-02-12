#include "../../../cu/cu.h"
// Declarations of tests
TEST(test3);
TEST(test4);
TEST(test5);
TEST(test6);

// Collect tests into test suite
TEST_SUITE(T2) {
    TEST_ADD(test3),
    TEST_ADD(test4),
    TEST_ADD(test5),
    TEST_ADD(test6),
    TEST_SUITE_CLOSURE
};
