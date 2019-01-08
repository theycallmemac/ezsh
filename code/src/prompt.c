#include <stdlib.h>
#include <signal.h>

#include "utils/readline.h"
#include "utils/tokenize.h"
#include "utils/execute.h"

void ezshLoop(void) {
    // declare variables needed
    char *line;
    char **args;
    int status;
    
    do {
        // this is our prompt here
        // this sets a size of 1024 for the current workind directory
        char cwd[1024];
        // load size of cwd into cwd
        getcwd(cwd, sizeof(cwd));
        char* uname = getlogin();
        // use it in the prompt
        printf("%s: %s |---> ", uname, cwd);
        // call the readline function
        line = ezshReadLine();
        // split line into arguments
        args = ezshSplitLine(line);
        // return status variable so the code knows when to exit
        status = ezshExecute(args);
        free(line);
        free(args);
    } while (status); 
    // the do while loop allows checking of the current status variable 
    //returned from ezsh_execute function
}

static volatile int keepRunning = 1;

int main() {
    // the above paramters load configs if they exist
    // loop to run commands
    while (keepRunning) {
        ezshLoop();
    }
    // exit shell
    return EXIT_SUCCESS;
}

