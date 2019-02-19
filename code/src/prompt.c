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

// This function sets up the default prompt of ezsh
// Takes three char arrays: uname (the name of the current user), cwd (the name of the currently working directory), and hostname (the name of the machine they are working on)
// The function returns an empty char* so it may work in sync with the readline library
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


// This function runs a loop consisting of: read, tokenize, and execute
// This function takes no parameters
// This function is of type void, so it returns nothing
void ezshLoop(void) {
    char *line;
    char **args;
    int status;
    do {
        char cwd[1024];
        char hostname[1024];
        gethostname(hostname, 1024);
        getcwd(cwd, sizeof(cwd));
        char* uname = getlogin();
        line = readline(ezshPrompt(uname, cwd, hostname));
        if (line[0] != '!' || line[0] != '*') {
            add_history(line);
            addToHistory(line);
        }
        args = ezshSplitLine(line);
        status = ezshExecute(args);
        free(line);
        free(args);
    } while (status); 
}

// This function catches signals such as the `ctrl-C` signal, and then free's the line state and runs the prompt code again
// Take one parameter, a signal (such as `ctrl-C`)
// Returns the void type, meaning it returns nothing
void handler(int signal) {
    rl_free_line_state ();
    printf("\n");
    char cwd[1024];
    char hostname[1024];
    gethostname(hostname, 1024);
    getcwd(cwd, sizeof(cwd));
    char* uname = getlogin();
    ezshPrompt(uname,cwd, hostname);
}

// This main function watches for signals passed, binds the tab key for autocomplete, creates .ezsh files and runs the loop
// Returns type int, EXIT_SUCCESS 
int main(int argc, char **argv) {
    int keepRunning = 1;
    signal(SIGINT, handler);
    rl_bind_key('\t', rl_complete);
    createFiles();
    while (keepRunning) {
        ezshLoop();
    }
    return EXIT_SUCCESS;
}

