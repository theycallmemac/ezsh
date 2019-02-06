#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

struct localVariable {
    const char* Name;
    const char* String;
};

int setLocalHOME(const char* HOME) {
    struct passwd *pw = getpwuid(getuid());
    HOME = pw->pw_dir;
    struct localVariable v1 = {"HOME", HOME};
    printf("%s\n", v1.String);
    return 0;
}



int getLocalHOME(const char* HOME) {
     
}


void getLocal(char* name){
    struct localVariable v1 = {"HOME", HOME};
    if (strcmp("HOME", name) == 0) {
        getLocalHOME("");
    }
}

void setLocal(char* name, char* desc){
    if (strcmp("HOME", name) == 0) {
        setLocalHOME(desc);
    }
}
char localStr[] = {
    "HOME"
};

int ezshNumLocals() {
    return sizeof(localStr) / sizeof(char *) + 1;
}

