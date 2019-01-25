#include <stdlib.h>
#include <signal.h>
#include "utils/colour.h"
#include "utils/readline.h"
#include "utils/tokenize.h"
#include "utils/execute.h"

void ezshPrompt(char uname[], char cwd[], char hostname[]) {
    printf("╭─ ");
    bold_magenta();
    printf("%s ", uname);
    reset();
    printf("%s " , "at");
    bold_cyan();
    printf("%s " , hostname);
    reset();
    printf("%s " , "in");
    bold_green();
    printf("%s\n", cwd);
    reset();
    printf("╰ ");
}

void ezshLoop(void) {
    // declare variables needed
    char *line;
    char **args;
    int status;
    
    do {
        // this sets a size of 1024 for the current working directory
        char cwd[1024];
        // sets size of 1024 for hostname
        char hostname[1024];
        // get size of hostname and load into variable
        gethostname(hostname, 1024);
        // load size of cwd into cwd
        getcwd(cwd, sizeof(cwd));
        // get logged in user
        char* uname = getlogin();
        // pass info to function which handles prompt design
        ezshPrompt(uname, cwd, hostname); 
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
    // returned from ezsh_execute function
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
