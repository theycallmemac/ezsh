#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

#include "../../../cu/cu.h"

TEST(test16) {
    char line[10] = "./Makefile";
    FILE *x = openFileRead(line);
    assertFalse(x == NULL);
}

TEST(test17) {
    char line[10] = "./Makefile";
    FILE *x = openFileWrite(line);
    assertFalse(x == NULL);
}

TEST(test18) {
    char line[10] = "./Makefile";
    FILE *x = openFileAppend(line);
    assertFalse(x == NULL);
}

