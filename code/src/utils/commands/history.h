#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <unistd.h>


#include "../files.h"


//  This function shows the entire history of the user (what they have entered at the prompt)
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
