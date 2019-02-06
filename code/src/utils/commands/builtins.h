#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

int ezshCD(char **args);
int ezshHELP(char **args);
int ezshHISTORY(char **args);
int ezshEXIT();

// some builtins and their functions
char *builtinStr[] = {
    "cd",
    "help",
    "history",
    "exit"
};


int (*builtinFunc[]) (char **) = {
    &ezshCD,
    &ezshHELP,
    &ezshHISTORY,
    &ezshEXIT
};

int ezshNumBuiltins() {
    return sizeof(builtinStr) / sizeof(char *);
}

int ezshHISTORY(char **args) {
    showHistory();  
    return 0;
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

int ezshCD(char **args) {
    if (args[1] == NULL) {
        struct passwd *pw = getpwuid(getuid());
        const char *HOME = pw->pw_dir;
        if (chdir(HOME) != 0) {
            perror("ezsh");
        }
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
