#include <stdlib.h>

int executeAnd(char **args){
    int i;
    for(i = 0; i < 10; i++) {
        if (args[i] == NULL) {
            break;
        }
        char *arg = trim(args[i]);
        system(arg);
    }
    return 0;
}

int executePipe(char **args){
    int i;
    char cmd[100];
    for(i = 0; i < 10; i++) {
        if (args[i] == NULL) {
            break;
        }
        strcat(cmd, args[i]);
        if (args[i+1] == NULL) {
            system(cmd);
        }
        strcat(cmd, "|");
    }
    return 0;
}


int redirectSTDOUT(char **args){
    int i;
    char cmd[100];
    for(i = 0; i < 10; i++) {
        if (args[i] == NULL) {
            break;
        }
        strcat(cmd, args[i]);
        if (args[i+1] == NULL) {
            system(cmd);
        }
        strcat(cmd, ">");
    }
    return 0;
}

