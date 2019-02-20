#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./utils/explorer.h"

void main()
{

    const int MAXSIZE = 17;
    const int OPTIONS = 15;
    const int PADDINGTOP = 1;
    const int MARGINTOP = 3;

    const int FILEINDEX = 30;
    const int PWDY = 20;

    FILE *fptr;
    char command[50];
    char **currdir;
    char option[10];
    char pwd[100];
    char **display;

    /*ncurses Initial setup*/
    WINDOW *w_exp;
    WINDOW *w_command;
    WINDOW *w_info;
    initscr();
    w_exp = newwin(MAXSIZE, 40, MARGINTOP, 1);
    w_command = newwin(1, 30, 0, 5);
    w_info = newwin(3, 30,20,2);
    noecho();
    curs_set(FALSE);
    keypad(w_exp, TRUE);
    start_color();
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);

loadNewDir:
    system("");
    /*Allocate memory for currdir*/
    char *dirMsg = "YELL='\033[1;33m' && WHITE='\033[0m' && CDVAR='cd ' && echo ${YELL}'Command -->' ${WHITE}$CDVAR$PWD > $(tail -1 ~/.ezsh/.ezsh.tty)\n";
    system(dirMsg);
    
    currdir = malloc(100 * sizeof(char *));
    for (int i = 0; i < 100; i++)
    {
        if ((currdir[i] = malloc(1000)) == NULL)
        {
            perror("ezsh");
        }
    }

    strcpy(pwd, exppwd(fptr));

    /*Revised ls that returns ttl file count*/
    strcpy(command, "/bin/ls");
    int p = expls(fptr, command, currdir) - 1;
    //Track options section in currdir array (All files)
    int currSection = 0;
    int currPoint = 0;
    //Discern whether user wants to load next page or last page
    bool forward_flag = 1;

loadPage:
    wclear(w_exp);
    wrefresh(w_exp);
    currSection;
    int i;

    display = malloc(100 * sizeof(char *));
    for (int i = 0; i < 100; i++)
    {
        if ((display[i] = malloc(100)) == NULL)
        {
            perror("ezsh");
        }
    }


    /*Load next n OPTIONS on menu, set selected option to top file*/
    if (forward_flag)
    {
        i = 0;
        for (int j = 0; j < OPTIONS; j++)
        {
            strcpy(display[j], currdir[currSection]);
            currSection++;
        }
    }
    /*Set currSection back to last pages position, load n options
         set selected option to bottom file*/
    else
    {
        i = 14;
        currSection -= 30;
        forward_flag = 1;
        for (int j = 0; j < OPTIONS; j++)
        {
            strcpy(display[j], currdir[currSection]);
            currSection++;
        }
    }

resizeRefresh:
    /*Current dir listings*/
    for (int n = 0; n <= OPTIONS; n++)
    {
        wattron(w_exp, A_STANDOUT);
        wattroff(w_exp, A_STANDOUT);
        if (n == 0 && currPoint == 0)
        {
            wattron(w_exp, COLOR_PAIR(1));
        }
        else if (isFile(strtok(display[n], "\n")))
        {
            wattron(w_exp, COLOR_PAIR(2));
            wattroff(w_exp, A_BOLD);
        }
        else if (isDir(strtok(display[n], "\n")))
        {
            wattron(w_exp, COLOR_PAIR(1) | A_BOLD);
        }
        sprintf(option, "%s", display[n]);
        mvwprintw(w_exp, n + PADDINGTOP, 2, "%s", option);
    }

    /*Current location*/
    wattron(w_info, COLOR_PAIR(2));
    mvwprintw(w_info, 0, 0, "File: %d/%d", currPoint, p);
    wattron(w_exp, COLOR_PAIR(1));

    wrefresh(w_exp);
    wrefresh(w_info);
    int ch = 0; //user input
    char *token;

    while (ch = wgetch(w_exp))
    {
        sprintf(option, "%s", display[i]);
        mvwprintw(w_exp, i + PADDINGTOP, 2, "%s", option);
        wrefresh(w_command);
        switch (ch)
        {
        case KEY_UP:
            i--;
            currPoint--;
            if (i == -1 && currPoint == -1)
            {
                i = 0;
                currPoint = 0;
            }
            if (i == -1)
            {
                forward_flag = 0;
                goto loadPage;
            }
            break;
        case KEY_DOWN:
            i++;
            currPoint++;
            if ((i > (p % OPTIONS)) && (currPoint > p))
            {
                i = (p % OPTIONS);
                currPoint = p;
            }
            if (i == OPTIONS)
            {
                goto loadPage;
            }
            break;
        case 0x0A:                            //Enter key (not numpad)
            token = strtok(display[i], "\n"); //parsing for expls (removes newline)
            if (isDir(token) || strcmp(token, "..") == 0)
            {
                chdir(display[i]);
                //Reset win completely
                wclear(w_exp);
                wrefresh(w_exp);
                free(currdir);
                free(display);
                goto loadNewDir; //Jump to start but load new files
            }
            /*Open gedit in specified file*/
            else if (isFile(token) && !fork())
            {
                execlp("gedit", "gedit", token, NULL);
                break;
            }
        case KEY_RESIZE:
            wclear(w_exp);
            goto resizeRefresh;
        }

        /*Update options accordingly after option input*/
        
        wattron(w_command, COLOR_PAIR(3) | A_BOLD);
        if (isFile(strtok(display[i], "\n"))){
            mvwprintw(w_command, 0, 10, "Command: gedit %s", display[i]);
            wrefresh(w_command);
            wclear(w_command);
        }
        else if (isDir(strtok(display[i], "\n"))){
            mvwprintw(w_command, 0, 10, "Command: cd %s", display[i]);
            wrefresh(w_command);
            wclear(w_command);
        }

        wattron(w_exp, COLOR_PAIR(2));
        wattroff(w_exp, A_BOLD);
        wclear(w_info);
        mvwprintw(w_info, 0, 0, "File: %d/%d", currPoint, p);
        wattron(w_exp, A_STANDOUT);
        wrefresh(w_info);

        if (isFile(strtok(display[i], "\n")))
        {
            wattron(w_exp, COLOR_PAIR(2));
            wattroff(w_exp, A_BOLD);
        }
        else if (isDir(strtok(display[i], "\n")))
        {
            wattron(w_exp, COLOR_PAIR(1) | A_BOLD);
        }
        sprintf(option, "%s", display[i]);
        mvwprintw(w_exp, i + PADDINGTOP, 2, "%s", option);
        wattroff(w_exp, A_STANDOUT | A_UNDERLINE);
    }
    endwin();
}
