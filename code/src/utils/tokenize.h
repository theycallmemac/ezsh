#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define EZSH_TOKEN_BUFFSIZE 64
#define EZSH_TOKEN_DELIMITER " \t\r\n\a"


// This function checks if allocation occured properly
// If not it exits on EXIT_FAILURE
void checkAllocation(char **tokens) {
    if (!tokens) {
        fprintf(stderr, "ezsh: allocation error occurred\n");
        exit(EXIT_FAILURE);
    }
}

// This function gets a token from the line provided
// The function returns said token, and takes a char* as a parameter
char *getToken(char *line) {
    char *token = strtok(line, EZSH_TOKEN_DELIMITER);
    return token;
}


// This function tokenizes the line of input, one token at a time
// This function makes use of both checkAllocation and getTokens()
// The function takes a char* (line) and returns a char** (tokens)
char **ezshSplitLine(char *line) {
    int buffsize = EZSH_TOKEN_BUFFSIZE, position = 0;
    char **tokens = malloc(buffsize * sizeof(char*));
    char *token;
    checkAllocation(tokens);
    token = getToken(line);
    while (token != NULL) {
        tokens[position] = token;
        position++;
        if (position >= buffsize) {
            buffsize += EZSH_TOKEN_BUFFSIZE;
            tokens = realloc(tokens, buffsize * sizeof(char*));
            checkAllocation(tokens);
        }
        token = getToken(NULL);
    }
    tokens[position] = NULL;
    return tokens;
}
