#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "./utils/explorer.h"

int main()
{
    FILE *fptr;
    char command[50];
    char **currdir;
    char userInput[1];

    initscr();
    while(1){
        scanf("%s", userInput);
        
        if(strcmp("ls",userInput)==0){
            /*Allocate memory for currdir*/
            if (( currdir = malloc( 100*sizeof( char* ))) == NULL){}
                for (int i = 0; i < 100; i++){
                    if ((currdir[i] = malloc(100)) == NULL){
                        perror("ezsh");
                        }
                }
            /*char array of char arrays*/
            strcpy(command, "/bin/ls");
            expls(fptr, command, currdir);
            for(int i=0; i<100; i++){
                printf("%s", currdir[i]);
            }
        }
        else if(strncmp("cd",userInput,2)==0){
            char userDir[100];
            scanf("%s",userDir);
            
            /*If directory chdir*/
            if(isDir(userDir) == 1){
                printf("Is dir: %d\n",isDir(userDir));
                chdir(userDir);
            }
            /*If file do nothing */
            else if(isFile(userDir) == 1){
                printf("Is file: %d\n",isFile(userDir));
            }
        }
        else {
            printf("Nothing hit\n");
        }
    }
    return 0;
}
