#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../cu/cu.h"
#include "../../../src/utils/execute.h"

TEST(test8) {
    char *line[2]  = {"mkdir", "testDir"};
    int x = ezshExecute(line);
    assertTrue(x == 1);
    assertTrue(access("./testDir/", F_OK) == 0);
}

TEST(test9) { 
    char *line[2]  = {"rmdir", "testDir"};
    int x = ezshExecute(line);
    assertTrue(x == 1);
    assertTrue(access("./testDir/", F_OK) != 0);
}

TEST(test10) {
    char *line[1]  = {""};
    int x = ezshExecute(line);
    assertTrue(x == 1);
}
