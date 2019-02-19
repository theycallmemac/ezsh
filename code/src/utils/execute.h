#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>


#include "commands/builtins.h"

// This function is called when the process id is zero
// This gives the child process control
void childProcess(char **args) {
    if (execvp(args[0], args) == -1) {
        perror("ezsh");
    }
    exit(EXIT_FAILURE);
}


// This function is called when the process id is less than zero
// This gives an error message
void errorProcess(char **args) {
    perror("ezsh");
}


// This function is called when the process id is greater than zero
// This gives the parent process control
void parentProcess(char **args, pid_t pid, int status) {
    do {
        pid_t wpid;
        wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
}


// This function decides which process function will be called: childProcess, errorProcess or parentProcess
// Returns the void type and takes char** args (arguments tokenized from the line), pid_t pid (the pid of the process forked), and and integer status (used later to control the loop in parentProcess)
void determineProcess(char **args, pid_t pid, int status) {
    if (pid == 0) {
        childProcess(args);
    } else if (pid < 0) {
        errorProcess(args);
    } else {
        parentProcess(args, pid, status);
    }
}


// This function forks the process executed and calls determineProcess() to decide who controls it
int ezshLaunch(char **args) {
    pid_t pid;
    int status;
    pid = fork();
    determineProcess(args, pid, status);
    return 1;
}

// This function executes the command an it's arguments (char **args) 
// It then calls ezshLaunch() for process control
int ezshExecute(char **args) {
    int itr;
    if (args[0] == NULL) {
        return 1;
     }
    if (args[0][0] == '!') {
        parseHistory(args);
        return 0;
    }
    if (args[0][0] == '*') {
        parseStars(args);
        return 0;
    }
    for (itr = 0; itr < ezshNumBuiltins(); itr++) {
        if (strcmp(args[0], builtinStr[itr]) == 0) {
            return (*builtinFunc[itr])(args);
        }
    }
    return ezshLaunch(args);
}
