#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>

/* 
Input: FILE *ptr, bash command, string[]
Output: Void, pass by reference  
*/
int expls(FILE *fp, char * command, char **currdir){

    char path[1024];
    fp = popen(command, "r");
    if (fp == NULL){
        exit(1);
    }

    int i = 1;
    strcpy(currdir[0], "..");
    while(fgets(path, sizeof(path)-1, fp) != NULL){
        strcpy(currdir[i],path);
        i++;
    }
    pclose(fp);
    free(fp);
    return i;
}
/* chdir alias
Input: char* directory
*/
void expcd(char * dir){
    chdir(dir);
}

/*
Input: file name
Output: bool
*/
_Bool isFile(const char *name)
{
    struct stat file_stat;
    stat(name, &file_stat);
    int fileType = S_ISREG(file_stat.st_mode);
    if(fileType == 1){
        return 1;
    } else {
        return 0;
    }
}

/*
Input: file name
Output: bool
*/
_Bool isDir(const char *name)
{
    struct stat dir_stat;
    stat(name, &dir_stat);
    int fileType = S_ISDIR(dir_stat.st_mode);
    if(fileType == 1){
        return 1;
    } else {
        return 0;
    }
}