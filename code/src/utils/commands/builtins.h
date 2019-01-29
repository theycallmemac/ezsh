#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int ezshCD(char **args);
int ezshHELP(char **args);
int ezshOPTIONS(char **args);
int ezshEXIT();

// some builtins and their functions
char *builtinStr[] = {
    "cd",
    "help",
    "options",
    "exit"
};

int (*builtinFunc[]) (char **) = {
    &ezshCD,
    &ezshHELP,
    &ezshOPTIONS,
    &ezshEXIT
};

int ezshNumBuiltins() {
    return sizeof(builtinStr) / sizeof(char *);
}
int ezshHELP(char **args) {
    if (args[1] == NULL) {
      fprintf(stderr, "ezsh: expected argument to \"help\"\n");
    } else {
       char buf[100];
       snprintf(buf, sizeof(buf), "echo && man %s | grep -A 1 NAME |  sed 's/^[ \t]*//;s/[ \t]*$//' | sed -n '1!p' && echo", args[1]);                                   
       system(buf); 
    }
    return 0;
}
int ezshOPTIONS(char **args) {
    if (args[1] == NULL) {
      fprintf(stderr, "ezsh: expected argument to \"options\"\n");
    } else {
       char buf[100];
       snprintf(buf, sizeof(buf), "echo && man %s | grep -A 40 DESCRIPTION |  sed 's/^[ \t]*//;s/[ \t]*$//' | sed -n '1!p' && echo", args[1]);                                   
       system(buf); 
    }
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
