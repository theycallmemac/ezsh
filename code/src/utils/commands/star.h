#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>


void showStars(void) {
    char *name = "stars";
    char *PATH = getHome(name);
    FILE *stars = openFileRead(PATH);

    errorFile(stars);

    char str[10000];
    int lineNumber = 1;

    showFile(stars, str, lineNumber);
    closeFile(stars);
}

int addStar(char *line) {
    char *name = "stars";
    char *PATH = getHome(name);
    FILE *stars = openFileAppend(PATH);

    errorFile(stars);

    append(stars, line);
    closeFile(stars);
    return 0;
}
