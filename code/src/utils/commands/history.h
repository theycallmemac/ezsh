#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <unistd.h>


#include "../files.h"
#include "../strings.h"


// This function shows the entire history of the user (what they have entered at the prompt)
// Returns void and parameters are void
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


// This function adds to our history file
// Returns an int, zero, and takes the tokenized command as a parameter
int addToHistory(char *line) {
    char *name = "history";
    char *PATH = getHome(name);
    FILE *history = openFileAppend(PATH);
    
    errorFile(history);

    append(history, line);
    closeFile(history);
    return 0;
}


int parseHistory(char **args) {
    char history[10] = "history";
    char *filename = getHome(history);
    FILE *hist = openFileRead(filename);
    char fileLine[32];
    int countLine = 0;
    int status = 0;


    strrev(args[0]);


    int i = 0;
    int n = 1;
    int total = 0;
    while (args[0][i] != '!') {
        int c = (args[0][i] - 48) * n;
        total += c;
        i++;
        n = n * 10;
    }
    while (fgets(fileLine, sizeof(fileLine), hist)) {
        char **words = ezshSplitLine(fileLine);
        if (total == countLine) {
            status = ezshExecute(words);
            free(words);
            break;
        }
        countLine++;
    }
    closeFile(hist);
    return status;
}
