#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>


#include "cd.h"
#include "help.h"
#include "history.h"
#include "star.h"


// Define functions to be loaded into builtinFunc
int ezshCD(char **args);
int ezshHELP(char **args);
int ezshHISTORY(char **args);
int ezshSTAR(char **args);
int ezshINFO(char **args);
int ezshSAVE();
int ezshEXIT();


// Store commands in here
// These should be what is ran at the prompt when you wish to execute such functionality
char *builtinStr[] = {
    "cd",
    "help",
    "history",
    "star",
    "info",
    "save",
    "exit"
};


// Store builtin functions here
// These functions should be listed in order with their counterparts in the builtinStr above
int (*builtinFunc[]) (char **) = {
    &ezshCD,
    &ezshHELP,
    &ezshHISTORY,
    &ezshSTAR,
    &ezshINFO,
    &ezshSAVE,
    &ezshEXIT
};


// This function returns the number of builtin commands ezh has
int ezshNumBuiltins() {
    return sizeof(builtinStr) / sizeof(char *);
}


// ezshHISTORY is the function called from prompt.c when you use `history`
// This calls showHistory() from history.h
int ezshHISTORY(char **args) {
    showHistory();  
    return 0;
}


// ezshHELP is the function called from prompt.c when you use `help`
// This calls getHELP() from help.h
int ezshHELP(char **args) {
    getHelp(args);
    return 0;
}


// ezshCD is the function called from prompt.c when you use `cd`
// This calls changeDir from cd.h
int ezshCD(char **args) {
    changeDir(args);
    return 1;
}


int ezshINFO(char **args) {
    system("~/.info");
    return 1;
}

// ezshSAVE is the function called from prompt.c when you use `save`
// This makes the shell exit on a zero code
int ezshSAVE() {
    char line[20] =  "tmux detach";
    char **saveShell = ezshSplitLine(line);
    int status = ezshExecute(saveShell);
    free(saveShell);
    exit(status);
}


// ezshSTAR is the function called from prompt.c when you use `star`
// This calls showStars() from star.h
int ezshSTAR(char **args) {
    if (args[1] == NULL) {
        showStars();  
    } else {
        addStar(args[1]);
    }
    return 0;
}


// ezshEXIT is the function called from prompt.c when you use `exit`
// This makes the shell exit on a zero code
int ezshEXIT() {
    char line[20] =  "tmux kill-session";
    char **exitShell = ezshSplitLine(line);
    int status = ezshExecute(exitShell);
    free(exitShell);
    exit(status);
}
