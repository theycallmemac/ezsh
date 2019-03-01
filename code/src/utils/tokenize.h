#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

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
char **getTokens(char **tokens, char *line, char *d) {
    int buffsize = EZSH_TOKEN_BUFFSIZE, position = 0;
    tokens = malloc(buffsize * sizeof(char*));
    checkAllocation(tokens);
    char *token;
    token = strtok(line, d);
    while (token != NULL) {
        tokens[position] = token;
        position++;
        if (position >= buffsize) {
            buffsize += EZSH_TOKEN_BUFFSIZE;
            tokens = realloc(tokens, buffsize * sizeof(char*));
            checkAllocation(tokens);
        }
        token = strtok(NULL, d);
    }
    tokens[position] = NULL;
    return tokens;
}


// This function tokenizes the line of input, one token at a time
// This function makes use of both checkAllocation and getTokens()
// The function takes a char* (line) and returns a char** (tokens)
char **ezshSplitLine(char *line) {
    int status;
    char **tokens;
    char **fTokens;
    if (strchr(line, '&')) {
        tokens = getTokens(tokens, line, "&");
        status = executeAnd(tokens);
        return fTokens;
    } else if (strchr(line, '|')) {
        tokens = getTokens(tokens, line, "|");
        status = executePipe(tokens);
        return fTokens;
     } else if (strchr(line, '>')) {
        tokens = getTokens(tokens, line, ">");
        status = redirectSTDOUT(tokens);
        return fTokens;   
    } else {
        tokens = getTokens(tokens, line, EZSH_TOKEN_DELIMITER);
        return tokens;
    }
}

