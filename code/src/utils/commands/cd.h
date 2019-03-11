#include <stdio.h>
#include <unistd.h>
#include <pwd.h>
#include <fcntl.h>


void sendMessage(char *dir) {
        int pipeFile;
        pipeFile = open("/tmp/prompt2exp", O_WRONLY);
        write(pipeFile, strtok(dir,"\n"), strlen(dir)+1);
        close(pipeFile);
}

// This function is invoked to check if changing to that directory is possible or not
// If it is, the action is executed
int tryChangeDir(char *dir) {
    sendMessage(dir);
    if (chdir(dir) != 0) {
        perror("ezsh");
        return 1;
    }
    return 0; 
}

// This function gets the users home directory when cd is passed no arguments
// Takes nothing as a parameter and returns a constant character point
const char *changeHome(void) {
    struct passwd *pw = getpwuid(getuid());
    const char *HOME = pw->pw_dir;
    return HOME;
}


// This function is used to determine if a directory change is possible
// Takes the tokenized command (char ** args) and returns void type
int changeDir(char **args) {
    if (args[1] == NULL) {
        const char *HOME = changeHome();
        tryChangeDir(HOME);
        sendMessage(HOME);
    } else {
        tryChangeDir(args[1]);
    }
    return 0;
}
