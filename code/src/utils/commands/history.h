#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <unistd.h>

#include "../files.h"


void showHistory(void) {
    char *name = "history";
    char *PATH = getHome(name);
    FILE *history = openFileRead(PATH);
 
    errorFile(history);

    char str[10000];
    int lineNumber = 1;

    showFile(history, str, lineNumber);
    closeFile(history);   
}

int addToHistory(char *line) {
    char *name = "history";
    char *PATH = getHome(name);
    FILE *history = openFileAppend(PATH);
    
    errorFile(history);

    append(history, line);
    closeFile(history);
    return 0;
}
