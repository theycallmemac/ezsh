#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>


#include "../explorer.h"
//  This function shows the entire log of directories the user has starred
// Returns void and parameters are void
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


// This function adds to our stars file
// Returns an int, zero, and takes the tokenized command as a parameter
int addStar(char *line) {
    char *name = "stars";
    char *PATH = getHome(name);
    FILE *stars = openFileAppend(PATH);

    errorFile(stars);
    char *pathway = realpath(line, NULL);
    if (!isDir(pathway)) {
        printf("%s", "That is not a directory. The star command can only be used on a directory.\n");
    } else {
        append(stars, pathway);
    }
    closeFile(stars);
    return 0;
}

int parseStars(char **args) {
    char stars[10] = "stars";
    char *filename = getHome(stars);
    FILE *star = openFileRead(filename);
    char fileLine[256];
    int countLine = 0;
    int status = 0;
    strrev(args[0]);
    int i = 0;
    int n = 1;
    int total = 0;

    char command[512];
    while (args[0][i] != '*') {
        int c = (args[0][i] - 48) * n;
        total += c;
        i++;
        n = n * 10;
    }
    strcat(command, "cd ");
    while (fgets(fileLine, sizeof(fileLine), star)) {
        if (total == countLine) {
            strcat(command, fileLine);
            char **words = ezshSplitLine(command);
            status = ezshExecute(words);
            break;
        }
        countLine++;
    }
    closeFile(star);
    return status;
}
