#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

void pipeWrite(char* msg){
    int pipeFile;
    char * pipePath = "/tmp/ezshMsgPasser";
    pipeFile = open(pipePath, O_WRONLY);
    write(pipeFile, strtok(msg,"\n"), strlen(msg)+1);
    close(pipeFile);
}

void pipeRead(void){
    int pipeFile;
        char pwd[100];
        char *command = "cd";
        char * pipePath = "/tmp/ezshMsgPasser";
        while(1){
            pipeFile = open(pipePath, O_RDONLY);
            read(pipeFile, pwd, 100);
            printf("%s\n", pwd);
            chdir(pwd);
            close(pipeFile);
        }
        
}
