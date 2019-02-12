#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../../cu/cu.h"
#include "../../../../src/utils/colour.h"

#define MAGENTA "\\33[1;35m"
#define CYAN  "\\33[1;36m"
#define GREEN "\\33[1;32m"
#define WHITE "\\33[0m"

TEST(test3) {
    char *magenta  = bold_magenta();
    assertEquals(0, strcmp(MAGENTA, magenta));
}

TEST(test4) {
    char *cyan  = bold_cyan();
    assertEquals(0, strcmp(CYAN, cyan));
}

TEST(test5) {
    char *green  = bold_green();
    assertEquals(0, strcmp(GREEN, green));
}

TEST(test6) {
    char *white  = reset();
    assertEquals(0, strcmp(WHITE, white));
}

