#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./utils/colour.h"

void main()
{
    const int YAXIS =20;
    const int XAXIS =40;

    const int TOTAL = 4;
    char *commands[][10]= {
                        {"ls", "cd", "touch"},
                        {"cat", "gedit", "mkdir"},
                        {"cp", "echo", "chmod"},
                        {"chown", "custom1", "custom2"}
                        };

    WINDOW *w_commands;
    initscr();
    w_commands = newwin(YAXIS, XAXIS, 1,1);
    noecho();
    curs_set(FALSE);
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    wattron(w_commands, COLOR_PAIR(1) | A_BOLD);
    bold_green();

    while(1){
            mvwprintw(w_commands,1, 12, commands[0][0]);
            mvwprintw(w_commands,3, 12, commands[0][1]);
            mvwprintw(w_commands,5, 12, commands[0][2]);

            mvwprintw(w_commands,7,  12, commands[1][0]);
            mvwprintw(w_commands,9,  12, commands[1][1]);
            mvwprintw(w_commands,11, 12, commands[1][2]);

            mvwprintw(w_commands,1, 30, commands[2][0]);
            mvwprintw(w_commands,3, 30, commands[2][1]);
            mvwprintw(w_commands,5, 30, commands[2][2]);

            mvwprintw(w_commands,7,  30, commands[3][0]);
            mvwprintw(w_commands,9,  30, commands[3][1]);
            mvwprintw(w_commands,11, 30, commands[3][2]);
        }
}

