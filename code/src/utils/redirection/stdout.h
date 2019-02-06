#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int redirectSTDOUT(char **args) {
    close(1); // Release fd no - 1
    if (fork() == 0)// Child process {
        int fd = fopen("stdout.txt", "w");

         dup2(fd, 1);   // make stdout go to file
         dup2(fd, 2);   // make stderr go to file - you may choose to not do this
                   // or perhaps send stderr to another file

         close(fd);     // fd no longer needed - the dup'ed handles are sufficient

         execvp("echo", &args[2]);
    }
    return 0;
}
