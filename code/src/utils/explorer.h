#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>

/* 
Input: FILE *ptr, bash command, string[]
Output: Int, pass by reference & number of elements  
*/
int expls(FILE *fp, char **currdir)
{

    strcpy(currdir[0], "..");
    char path[1024];
    fp = popen("/bin/ls", "r");
    if (fp == NULL)
    {
        exit(1);
    }
    int i = 1;
    while (fgets(path, sizeof(path) - 1, fp) != NULL)
    {
        strcpy(currdir[i], path);
        i++;
    }
    pclose(fp);
    return i;
}

char *exppwd(FILE *fp)
{
    char pwd[100];
    fp = popen("/bin/pwd", "r");
    char *path = (fgets(pwd, sizeof(pwd) - 1, fp));
    pclose(fp);
    return (strtok(path,"\n"));
}

/*
Input: file name
Output: bool
*/
_Bool isFile(const char *name)
{
    struct stat file_stat;
    stat(strtok(name, "\n"), &file_stat);
    int fileType = S_ISREG(file_stat.st_mode);
    if (fileType == 1)
    {
        return 1;
    }
    else
    {
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
    stat(strtok(name,"\n"), &dir_stat);
    int fileType = S_ISDIR(dir_stat.st_mode);
    if (fileType == 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/*
Create a file in the current directory: 
const char *fileName: Name of the file to be created
*/
void touch(const char *fileName)
{
    char newFile[100] = {"touch "};
    strcat(newFile, fileName);
    system(newFile);
}

/*
Allocate memory to a char** variable:
arrSize: How many strings to be allocated
strSize: Size of the largest string to be allocated
*/
char** mallocStrArr(int arrSize, int strSize){
    char** arr;
    arr = malloc(arrSize * sizeof(char*));
    for(int i = 0; i < arrSize; i++)
    {
        if ((arr[i]= malloc(strSize * sizeof(char*))) == NULL) {
            perror("ezsh memalloc fail");
        }
    }
    return arr;
}