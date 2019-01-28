#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./utils/explorer.h"

int main()
{
    FILE *fptr;
    char command[50];
    char **currdir;
    char userInput[1];

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
            char userDir[50];
            scanf("%s",userDir);
            expcd(userDir);
        }
        else {
            printf("Nothing hit\n");
        }
    }
    return 0;
}