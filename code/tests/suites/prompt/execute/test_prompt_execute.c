#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

#include "../../../cu/cu.h"
#include "../../../../src/utils/execute.h"

TEST(test7) {
    char *line[3]  = {"mkdir", "testDir"};
    int x = ezshExecute(line);
    assertTrue(x == 1);
    assertTrue(access("./testDir/", F_OK) == 0);
}

TEST(test8) { 
    char *line[3]  = {"rmdir", "testDir"};
    int x = ezshExecute(line);
    assertTrue(x == 1);
    assertTrue(access("./testDir/", F_OK) != 0);
}

TEST(test9) {
    char *line[1]  = {""};
    int x = ezshExecute(line);
    assertTrue(x == 1);
}
