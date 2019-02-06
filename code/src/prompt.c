#include <stdlib.h>
#include <stdio.h> 
#include <signal.h>

#include <sys/types.h>
#include <pwd.h>

#include <readline/readline.h>
#include <readline/history.h>

#include "utils/colour.h"
#include "utils/tokenize.h"
#include "utils/execute.h"
#include "utils/systemFiles.h"

char *ezshPrompt(char uname[], char cwd[], char hostname[]) {
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
    return "";
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
        // call the readline function, which takes the ezshPrompt function as a parameter
        line = readline(ezshPrompt(uname, cwd, hostname));
        //line = ezshReadLine(input);
        //if (strcmp(line, "") == 1) {
            add_history(line);
            addToHistory(line);
        //}
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

void handler(int sig) {
    rl_free_line_state ();
    printf("\n");
    char cwd[1024];
    // sets size of 1024 for hostname
    char hostname[1024];
    // get size of hostname and load into variable
    gethostname(hostname, 1024);
    // load size of cwd into cwd
    getcwd(cwd, sizeof(cwd));
    // get logged in user
    char* uname = getlogin();
    ezshPrompt(uname,cwd, hostname);
}

int main(int argc, char **argv) {
    // the above paramters load configs if they exist
    signal(SIGINT, handler);
    rl_bind_key('\t', rl_complete);
    createFiles();
    while (keepRunning) {
        ezshLoop();
    }
    // exit shell
    return EXIT_SUCCESS;
}

