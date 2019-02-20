#include <stdlib.h>
#include <unistd.h>

void checkFiles() {
    if (access( "~/.ezsh/.ezsh.conf", F_OK ) != -1 && access( "~/.ezsh/.ezsh.tty", F_OK ) != -1 && access( "~/.ezsh/.ezsh.history", F_OK ) != -1 && access( "~/.ezsh/.ezsh.stars", F_OK ) != -1) {
        system("");
    } else {
        createFiles();
}
    
}

// This function simply creates the ezsh config files and other files used by the shell
// Takes no paramters and returns void
void createFiles() {
    system("mkdir -p ~/.ezsh");
    system("cp ~/.ezsh/.ezsh.conf ~/.ezsh/ 2> /dev/null");
    system("cp .ezsh/.ezsh.tty ~/.ezsh/");
    system("cp .ezsh/.ezsh.history ~/.ezsh/");
    system("cp .ezsh/.ezsh.stars ~/.ezsh/");
}
