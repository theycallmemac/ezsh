#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

#include "../../../cu/cu.h"

TEST(test10) {
    char line[2]  = "..";
    int x = tryChangeDir(line);
    assertTrue(x == 0);
}

TEST(test11) { 
    int x = tryChangeDir("../..");
    assertTrue(x == 0);
}

TEST(test12) {
    char *line[3]  = {"cd", "blah/blah"};
    int x = tryChangeDir(line);
    assertTrue(x == 1);
}

