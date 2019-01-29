#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
/* Input: FILE *ptr, bash command, string[]
Output: Void, pass by reference  
*/
void expls(FILE *fp, char * command, char **currdir){

    char path[1024];
    fp = popen(command, "r");
    if (fp == NULL){
        exit(1);
    }

    int i = 0;
    while(fgets(path, sizeof(path)-1, fp) != NULL){
        strcpy(currdir[i],path);
        i++;
    }
    pclose(fp);
    free(fp);
}

void expcd(char * dir){
    chdir(dir);
}