#include <stdio.h>
#include <unistd.h>
#include <pwd.h>

// This function is invoked to check if changing to that directory is possible or not
// If it is, the action is executed
int errorChangeDir(char *dir) {
        int pipeFile;
        pipeFile = open("/tmp/prompt2exp", O_WRONLY);
        write(pipeFile, strtok(dir,"\n"), strlen(dir)+1);
        close(pipeFile);
    if (chdir(dir) != 0) {
        perror("ezsh");
        return 1;
    }   
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
        errorChangeDir(HOME);
    } else {
        errorChangeDir(args[1]);
    }
    return 0;
}
