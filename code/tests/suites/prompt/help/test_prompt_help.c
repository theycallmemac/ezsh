#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

#include "../../../cu/cu.h"

TEST(test13) {
    char *line[2]  = {"help", "ls"};
    int x = getHelp(line);
    assertTrue(x == 0);
}

TEST(test14) { 
    char *line[2]  = {"help", "mkdir"};
    int x = getHelp(line);
    assertTrue(x == 0);
}

TEST(test15) {
    char *line[2]  = {"help", "fdisk"};
    int x = getHelp(line);
    assertTrue(x == 0);
}
