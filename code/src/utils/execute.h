#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#include "commands/builtins.h"

int ezshLaunch(char **args) {
    pid_t pid;
    int status;
    pid = fork();
    if (pid == 0) {
        // child process control
        if (execvp(args[0], args) == -1) {
            perror("ezsh");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        // if there's an error forking
        perror("ezsh");
    } else {
        // control for parent process
        do {
            pid_t wpid;
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
  return 1;
}

int ezshExecute(char **args) {
  int itr;

  if (args[0] == NULL) {
    // An empty command was entered.
    return 1;
  }

  for (itr = 0; itr < ezshNumBuiltins(); itr++) {
    if (strcmp(args[0], builtinStr[itr]) == 0) {
      return (*builtinFunc[itr])(args);
    }
  }

  return ezshLaunch(args);
}
