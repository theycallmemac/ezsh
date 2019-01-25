#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int ezshCD(char **args);
int ezshHELP();
int ezshEXIT();

// some builtins and their functions
char *builtinStr[] = {
    "cd",
    "help",
    "exit"
};

int (*builtinFunc[]) (char **) = {
    &ezshCD,
    &ezshHELP,
    &ezshEXIT
};

int ezshNumBuiltins() {
    return sizeof(builtinStr) / sizeof(char *);
}
int ezshHELP() {
    int i;
    printf("James McDermott & Connor Mulready's ezsh\n");
    printf("You can type regular commands and their arguments, followed by the return key.\n");
    printf("The following list of commands are built in to ezsh:\n");

    for (i = 0; i < ezshNumBuiltins(); i++) {
      printf(" --> %s\n", builtinStr[i]);
    }

    printf("Use the man command for information on other programs.\n");
    return 0;
}
int ezshCD(char **args) {
    if (args[1] == NULL) {
      fprintf(stderr, "ezsh: expected argument to \"cd\"\n");
    } else {
      if (chdir(args[1]) != 0) {
        perror("ezsh");
      }
    }
    return 1;
}


int ezshEXIT() {
    exit(0);
}
