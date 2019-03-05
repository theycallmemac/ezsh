#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../../cu/cu.h"
#include "../../../../src/utils/tokenize.h"
#include "../../../../src/utils/operations.h"

TEST(test1) {
    char **args;
    char line[80] = "cd /var/www";
    char str[80] = "cd /var/www";
    args = ezshSplitLine(line);
    const char s[2] = " ";
    char *token;

    token = strtok(str, s);
    int count = 0;
    while( token != NULL ) {
        int value = (strcmp(token, args[count]));
        assertEquals(value, 0);
        count++;
        token = strtok(NULL, s);
    }
    free(args);
}


TEST(test2) {
    char **args;
    char line[80] = "ls -alR /etc";
    char str[80] = "ls -alR /etc";
    args = ezshSplitLine(line);
    const char s[2] = " ";
    char *token;

    token = strtok(str, s);
    int count = 0;
    while( token != NULL ) {
        int value = (strcmp(token, args[count]));
        assertEquals(value, 0);
        count++;
        token = strtok(NULL, s);
    }
    free(args);
}
