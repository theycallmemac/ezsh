#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <pwd.h>
#include <readline/readline.h>
#include <readline/history.h>

#include <pthread.h>
#include <fcntl.h>

#include "utils/colour.h"
#include "utils/tokenize.h"
#include "utils/execute.h"
#include "utils/operations.h"
#include "utils/systemFiles.h"

#define EXP2PROMPT "/tmp/exp2prompt"
#define PROMPT2EXP "/tmp/prompt2exp"


// This function sets up the default prompt of ezsh
// Takes three char arrays: uname (the name of the current user), cwd (the name of the currently working directory), and hostname (the name of the machine they are working on)
// The function returns an empty char* so it may work in sync with the readline library
char *ezshPrompt(char uname[], char cwd[], char hostname[])
{
    printf("╭─ ");
    bold_magenta();
    printf("%s ", uname);
    reset();
    printf("%s ", "at");
    bold_cyan();
    printf("%s ", hostname);
    reset();
    printf("%s ", "in");
    bold_green();
    printf("%s\n", cwd);
    reset();
    printf("╰ ");
    return "";
}

void pipeReadexp()
{
    int fd;
    char str[100];
    int f = 0;
    while (1)
    {
        fd = open(EXP2PROMPT, O_RDONLY);
        read(fd, str, 100);
        if(chdir(str)==0){
            if(f == 0){
                char cwd[1024];
                char hostname[1024];
                gethostname(hostname, 1024);
                getcwd(cwd, sizeof(cwd));
                char *uname = getlogin();
                printf("\n");
                ezshPrompt(uname, cwd, hostname);
            } else
            {
                f = 1;
            }
            
        }
        close(fd);
    }
}
// This function runs a loop consisting of: read, tokenize, and execute
// This function takes no parameters
// This function is of type void, so it returns nothing
void ezshLoop(void)
{
    char *line;
    char **args;
    int status;
    pthread_t msglstnr;
    int msg;
    msg = pthread_create(&msglstnr, NULL, pipeReadexp, NULL);
    char *dirMsg;
    do {
        dirMsg = (char *)malloc(300);
        char cwd[1024];
        char hostname[1024];
        gethostname(hostname, 1024);
        getcwd(cwd, sizeof(cwd));
        char *uname = getlogin();
        line = readline(ezshPrompt(uname, cwd, hostname));
        if (line[0] != '!' || line[0] != '*')
        {
            add_history(line);
            addToHistory(line);
        }
        args = ezshSplitLine(line);
        status = ezshExecute(args);
        strcat(dirMsg, "YELL='\033[1;33m' && WHITE='\033[0m'&& echo ${YELL}'Command -->' ${WHITE}");
        for (int i = 0; i < 200; i++)
        {
            if (args[i] == NULL)
            {
                break;
            }
            strcat(dirMsg, args[i]);
            strcat(dirMsg, " ");
        }
        strcat(dirMsg, "> $(tail -1 ~/.ezsh/.ezsh.tty)\n");
        system(dirMsg);
        free(dirMsg);
        free(line);
        free(args);
    } while(status);
    
}

// This function catches signals such as the `ctrl-C` signal, and then free's the line state and runs the prompt code again
// Take one parameter, a signal (such as `ctrl-C`)
// Returns the void type, meaning it returns nothing
void handler(int signal)
{
    char cwd[1024];
    char hostname[1024];
    gethostname(hostname, 1024);
    getcwd(cwd, sizeof(cwd));
    char *uname = getlogin();
    char *currentLine;
    currentLine = rl_copy_text(0, rl_end);
    rl_replace_line("", 0);
    rl_redisplay();
    printf("\n");
    rl_set_prompt(ezshPrompt(uname, cwd, hostname));
    rl_redisplay();
    free(currentLine);
}

// This main function watches for signals passed, binds the tab key for autocomplete, creates .ezsh files and runs the loop
// Returns type int, EXIT_SUCCESS
int main(int argc, char **argv)
{
    int keepRunning = 1;

    mkfifo(PROMPT2EXP, 0666);

    signal(SIGINT, handler);
    rl_bind_key('\t', rl_complete);
    checkFiles();
    while (keepRunning)
    {
        ezshLoop();
    }
    return EXIT_SUCCESS;
}
