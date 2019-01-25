#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define EZSH_TOKEN_BUFFSIZE 64
#define EZSH_TOKEN_DELIMITER " \t\r\n\a"
char **ezshSplitLine(char *line) {
    // declare some variables, using definitions from above
    int buffsize = EZSH_TOKEN_BUFFSIZE, position = 0;
    char **tokens = malloc(buffsize * sizeof(char*));
    char *token;
    // exits if tokens not allocated
    if (!tokens) {
        fprintf(stderr, "ezsh: allocation error occurred\n");
        exit(EXIT_FAILURE);
    }
    // strtok takes a char array called line and the possible delimiters defined above
    // this returns a pointer to the first token
    token = strtok(line, EZSH_TOKEN_DELIMITER);
    // while loop runs until a token is found to be of null value
    while (token != NULL) {
        // adding tokens to an array of character pointers
        tokens[position] = token;
        position++;
        //
        if (position >= buffsize) {
            // here we dynamically expand the array of pointers being used
            buffsize += EZSH_TOKEN_BUFFSIZE;
            tokens = realloc(tokens, buffsize * sizeof(char*));
            // again, checking for errors with the allocation
            if (!tokens) {
                fprintf(stderr, "ezsh: allocation error occurred\n");
                exit(EXIT_FAILURE);
            }
        }
        // gets the next token
        token = strtok(NULL, EZSH_TOKEN_DELIMITER);
    }
    // set the final element of the array to the null value
    tokens[position] = NULL;
    // return the delimited tokens
    return tokens;
}
