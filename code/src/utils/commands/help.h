#include <stdlib.h>
#include <stdio.h>


// This function executes code to simply man page output of any program
// Returns nothing and takers tokenized command as parameter
int getHelp(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "ezsh: expected argument to \"help\"\n");
        return 1;
    } else {
        char command[100];
        snprintf(command, sizeof(command), "echo && man %s | grep -A 1 NAME | sed 's/^[ \t]*//;s/[ \t]*$//' | sed -n '1!p' | sed -n '1,1p'", args[1]);
        system(command);
        printf("\n");
        return 0;
    }
}
