// Include definition of T1 test suite
#include "suites/prompt/tokenize/test_prompt_tokenize.h"
#include "suites/prompt/colorize/test_prompt_colorize.h"
#include "suites/prompt/execute/test_prompt_execute.h"
#include "suites/prompt/cd/test_prompt_cd.h"
#include "suites/prompt/help/test_prompt_help.h"
#include "suites/prompt/files/test_prompt_files.h"
#include "suites/prompt/strings/test_prompt_strings.h"


// This struct contains all test suites
// We plan to test as much of this code as we can, so each test suite will be a separate directory.
TEST_SUITES {
    TEST_SUITE_ADD(T1), // add T1 test suite
    TEST_SUITE_ADD(T2), // add T2 test suite
    TEST_SUITE_ADD(T3), // add T3 test suite
    TEST_SUITE_ADD(T4), // add T4 test suite
    TEST_SUITE_ADD(T5), // add T5 test suite
    TEST_SUITE_ADD(T6), // add T6 test suite
    TEST_SUITE_ADD(T7), // add T7 test suite
    TEST_SUITES_CLOSURE
};

int main(int argc, char *argv[]) {
    // set up directory where are stored files with outputs from test suites
    CU_SET_OUT_PREFIX("regressions/");
    // run all test suites
    CU_RUN(argc, argv);
    return 0;
}
