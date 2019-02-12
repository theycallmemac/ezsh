// Include definition of T1 test suite
#include "suites/tokenize/test_prompt_tokenize.h"
#include "suites/colorize/test_prompt_colorize.h"
#include "suites/execute/test_prompt_execute.h"
#include "suites/explorer/test_explorer_traversal.h"

// This struct contains all test suites
// We plan to test as much of this code as we can, so each test suite will be a separate directory.
TEST_SUITES {
    TEST_SUITE_ADD(T1), // add T1 test suite
    TEST_SUITE_ADD(T2), // add T2 test suite
    TEST_SUITE_ADD(T3), // add T3 test suite
    TEST_SUITE_ADD(T4), // add T3 test suite
    TEST_SUITES_CLOSURE
};

int main(int argc, char *argv[]) {
    // set up directory where are stored files with outputs from test suites
    CU_SET_OUT_PREFIX("regressions/");
    // run all test suites
    CU_RUN(argc, argv);
    return 0;
}
