#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

#include "../../../cu/cu.h"

TEST(test10) {
    char *line[3]  = {"cd", ".."};
    int x = changeDir(line);
    assertTrue(x == 0);
}

TEST(test11) { 
    char *line[2]  = {"cd"};
    int x = changeDir(line);
    assertTrue(x == 0);
}

TEST(test12) {
    char *line[3]  = {"cd", "blah/blah"};
    int x = errorChangeDir(line);
    assertTrue(x == 1);
}

