#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

void pipeWrite(char* msg, char* filePath){
    int pipeFile;
    pipeFile = open(filePath, O_WRONLY);
    write(pipeFile, strtok(msg,"\n"), strlen(msg)+1);
    close(pipeFile);
}

void pipeReadexp(void){
    int pipeFile;
        char pwd[100];
        while(1){
            pipeFile = open("/tmp/exp2prompt", O_RDONLY);
            read(pipeFile, pwd, 100);
            printf("%s\n", pwd);
            chdir(pwd);
            close(pipeFile);
        }  
}

// void pipeReadprompt(void){
//     int pipeFile;
//         char pwd[100];
//         char pathy[200];
//         while(1){
//             pipeFile = open("/tmp/prompt2exp", O_RDONLY);
//             read(pipeFile, pwd, 100);
//             chdir(pwd);
//             close(pipeFile);
//         }  
// }