#include <stdlib.h>

void createFiles() {
    system("mkdir -p ~/.ezsh");
    system("cp .ezsh/.ezsh.conf ~/.ezsh/");
    system("cd ~/.ezsh && touch .ezsh.history && touch .ezsh.tty && cd ..");
}
