#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

#include "../../../cu/cu.h"
#include "../../../../src/utils/commands/cd.h"

TEST(test10) {
    char *line[2]  = {"cd", ".."};
    int x = changeDir(line);
    assertTrue(x == 0);
}

TEST(test11) { 
    char *line[2]  = {"cd"};
    int x = changeDir(line);
    assertTrue(x == 0);
}

TEST(test12) {
    const char *line[2]  = {"cd", "blah/blah"};
    int x = errorChangeDir(line);
    assertTrue(x == 1);
}

TEST(test13) {
    const char *PATH = changeHome();
    int x = system("cd $HOME");
    int y = changeDir(PATH);
    assertTrue(x == y);
}
