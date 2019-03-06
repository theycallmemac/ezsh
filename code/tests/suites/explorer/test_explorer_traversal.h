#include "../../cu/cu.h"
// Declarations of tests
TEST(test1);
TEST(test2);
TEST(test3);
TEST(test4);
TEST(test5);
TEST(test6);
TEST(test7);

// Collect tests into test suite
TEST_SUITE(T1) {
    TEST_ADD(test1),
    TEST_ADD(test2),
    TEST_ADD(test3),
    TEST_ADD(test4),
    TEST_ADD(test5),
    TEST_ADD(test6),
    TEST_ADD(test7),
    TEST_SUITE_CLOSURE
};
