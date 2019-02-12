#include <stdio.h>
#include <stdlib.h>
#define EZSH_READLINE_BUFFSIZE 1024
char *ezshReadLine(void) {
    // declaring variables used in scope of ezshReadLine
    int buffsize = EZSH_READLINE_BUFFSIZE;
    int position = 0;
    char *buffer = malloc(sizeof(char) * buffsize);
    int c;

    // if there is nothing allocated
    if (!buffer) {
        fprintf(stderr, "ezsh: allocation error occurreed\n");
        exit(EXIT_FAILURE);
    }

    while (1) {
        // read a char (though this is stored as an integer)
        // this is cause end of file is an integer, and to check it, you need an integer
        // this took me a long time to figure out, please dont change this without good reason
        // no seriously, DONT >.>
        c = getchar();
        // if end of file, replace it with a null char and return
        // otherwise add char to existing string
        if (c == EOF || c == '\n') {
            buffer[position] = '\0';
            return buffer;
        } else {
            buffer[position] = c;
        }
        position++;
        // this is where reallocation occurs
        // this checks whether or not
        // if text read in exceeds buffer, reallocate
        if (position >= buffsize) {
            buffsize += EZSH_READLINE_BUFFSIZE;
            buffer = realloc(buffer, buffsize);
            if (!buffer) {
                fprintf(stderr, "ezsh: allocation error occurred\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}
