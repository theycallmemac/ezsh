#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <unistd.h>


// This function builds a path from the user HOME dir to the file type require for operation
// Takes a char pointer and returns the path built as a character pointer
char *getHome(char *name) {
    struct passwd *pw = getpwuid(getuid());
    char *PATH = pw->pw_dir;
    char hidden[20] = "/.ezsh/.ezsh.";
    strcat(hidden, name);
    strcat(PATH, hidden);
    return PATH;
}


// This function flags if an error was raised in opening the file
void errorFile(FILE *file) {
    if (file == NULL) { 
        printf("Cannot open file.\n"); 
        exit(0);
    } 
}


// This function colors output of the file 
// Line numbers are bold yellow, and the remainder of the text is white.
void colorOut(char *str, int lineNumber) {
    bold_yellow();
    printf("%d ", lineNumber);
    reset();
    printf("%s\n", str);
}


// This function opens a file for reading
// Takes the path to the file as a parameter and returns the FILE pointer from opening that file for reading
FILE *openFileRead(char *path) {
    FILE *file = fopen(path, "r");
    return file;
}


// This function opens a file for writing
// Takes the path to the file as a parameter and returns the FILE pointer from opening that file for writing
FILE *openFileWrite(char *path) {
    FILE *file = fopen(path, "w");
    return file;
}


// This function opens a file for appending
// Takes the path to the file as a parameter and returns the FILE pointer from opening that file for appending
FILE *openFileAppend(char *path) {
    FILE *file = fopen(path, "a");
    return file;
}

// This function shows the contents of the required file
// The function takes the FILE, a character point for building and comparison, and an integer. This all helps to tailor readable output.
void showFile(FILE *file, char *str, int lineNumber) {
    while(fgets(str, sizeof(str), file) != NULL) {
        fscanf(file,"%[^\n]", str);
        if (strcmp(str, "\n") == 0) {
            break;
        }
        colorOut(str, lineNumber);
        lineNumber++;
    }
    printf("\n");
}

// This function closes a file 
// The function take the FILE pointer as a paramter.
void closeFile(FILE *file) {
    fclose(file);
}


// This function appends a line of text to a file
// This function takes a FILE pointer and a character pointer.
void append(FILE *file, char *line) {
    fprintf(file, "%s\n", line);
}
