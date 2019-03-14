#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./utils/colour.h"

void main()
{
    char *commands[][10]= {
                        {"ls", "cd", "touch"},
                        {"cat", "gedit", "mkdir"},
                        {"cp", "help", "chmod"},
                        {"chown", "star", "history"}
                        };

    initscr();
    noecho();
    curs_set(FALSE);
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    attron(COLOR_PAIR(1) | A_BOLD);
    bold_green();
    while(1){
    
            mvprintw(1, 20, commands[0][0]);
            mvprintw(3, 20, commands[0][1]);
            mvprintw(5, 20, commands[0][2]);

            mvprintw(7,  20, commands[1][0]);
            mvprintw(9,  20, commands[1][1]);
            mvprintw(11, 20, commands[1][2]);

            mvprintw(1, 40, commands[2][0]);
            mvprintw(3, 40, commands[2][1]);
            mvprintw(5, 40, commands[2][2]);

            mvprintw(7,  40, commands[3][0]);
            mvprintw(9,  40, commands[3][1]);
            mvprintw(11, 40, commands[3][2]);
            refresh();
            attron(A_BLINK);
            mvprintw(20, 10, "Press 'CTRL^c' to exit");
            attroff(A_BLINK);
    }

}

