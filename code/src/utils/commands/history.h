#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>

void showHistory() {
    struct passwd *pw = getpwuid(getuid());
    char *PATH = pw->pw_dir;
    strcat(PATH, "/.ezsh/.ezsh.history");
    FILE *history = fopen(PATH, "r");
    if (history == NULL) { 
        printf("Cannot open file \n"); 
        exit(0);
    } 
    char str[1000];
    int lineNumber = 1;
    while(fgets(str,sizeof(str),history) != NULL) {
        fscanf(history,"%[^\n]", str);
        if (strcmp(str, "\n") == 0) {
            break;
        }
        bold_yellow();
        printf("%d ", lineNumber);
        reset();
        printf("%s\n", str);
        lineNumber++;
    }
    printf("\n");
    fclose(history); 
}

int addToHistory(char *line) {
    struct passwd *pw = getpwuid(getuid());
    char *PATH = pw->pw_dir;
    strcat(PATH, "/.ezsh/.ezsh.history");
    FILE *history = fopen(PATH, "a");
    if (history == NULL) { 
        printf("Cannot open file \n"); 
        exit(0);
    } 
    fprintf(history, "%s\n", line); 
    fclose(history);
    return 0;
}
