#include <stdlib.h>

// This function simply creates the ezsh config files and other files used by the shell
// Takes no paramters and returns void
void createFiles() {
    system("mkdir -p ~/.ezsh");
    system("cp .ezsh/.ezsh.conf ~/.ezsh/");
    system("cd ~/.ezsh && touch .ezsh.history && touch .ezsh.tty && cd ..");
}
