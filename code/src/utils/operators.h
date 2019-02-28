#include <stdlib.h>

void executeAnd(char **args){
    int i;
    for(i = 0; i < 10; i++) {
        if (args[i] == NULL) {
            break;
        }
        char *arg = trim(args[i]);
        system(arg);
    }
}
