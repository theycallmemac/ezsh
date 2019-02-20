#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./utils/explorer.h"

    void draw_borders(WINDOW * win)
    {
        int x, y, i;
        getmaxyx(win, y, x);
        mvwprintw(win, 0, 0, "+");
        mvwprintw(win, y - 1, 0, "+");
        mvwprintw(win, 0, x - 1, "+");
        mvwprintw(win, y - 1, x - 1, "+");
        for (i = 1; i < (y - 1); i++)
        {
            mvwprintw(win, i, 0, "|");
            mvwprintw(win, i, x - 1, "|");
        }
        for (i = 1; i < (x - 1); i++)
        {
            mvwprintw(win, 0, i, "-");
            mvwprintw(win, y - 1, i, "-");
        }
    }
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
    char macroOption[10];
    char pwd[100];
    char newDirPath[100];
    char newDirName[80];
    char **display;

    char shortcut[3][10] = {"MKDIR", "HOME", "STAR"};

    /*ncurses Initial setup*/
    WINDOW *w_exp;
    WINDOW *w_command;
    WINDOW *w_info;
    WINDOW *w_macros;
    initscr();
    w_exp = newwin(MAXSIZE, 40, MARGINTOP, 1);
    w_command = newwin(1, 30, 0, 21);
    w_info = newwin(8, 30, 20, 2);
    w_macros = newwin(3, 20, 0, 3);
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
    wrefresh(w_command);
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
    wattron(w_exp, COLOR_PAIR(1)); 
    wattron(w_info, COLOR_PAIR(2)); 
    wattron(w_command, COLOR_PAIR(3) | A_BOLD);
    wattron(w_macros, A_BOLD | A_UNDERLINE);
    mvwprintw(w_info, 0, 0, "File: %d/%d", currPoint, p);
    mvwprintw(w_info, 1, 0, "%s", pwd);
    mvwprintw(w_command, 0, 0, "Command:");
    for(int i=0; i<3; i++){
        if(i==0){
            wattron(w_macros, A_STANDOUT);
        } else {
            wattroff(w_macros, A_STANDOUT);
            sprintf(macroOption, "%s", shortcut[i]);
            mvwprintw(w_macros, 0,i*5, "%s", macroOption);
        }
    }
    wrefresh(w_exp); 
    wrefresh(w_info); 
    wrefresh(w_command);
    wrefresh(w_macros);

    int ch = 0; //user input
    char *token;
    int topOption = 0;
    int commandFlag;

    while (ch = wgetch(w_exp))
    {
        sprintf(macroOption, "%s", shortcut[topOption]);
        mvwprintw(w_macros, 0, topOption*5, "%s", macroOption);
        wrefresh(w_macros);

        sprintf(option, "%s", display[i]);
        mvwprintw(w_exp, i + PADDINGTOP, 2, "%s", option);
        wrefresh(w_command);
        switch (ch)
        {
        case KEY_UP:
            i--;
            currPoint--;
            commandFlag = 0;
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
            commandFlag = 0;
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
        
        case 0x9:
            topOption++;
            commandFlag = 1;
            topOption = (topOption > 2) ? 0: topOption;
            break;
        case 0x20:
            if (topOption == 0) {
                /* code */
                echo();
                token = strtok(pwd, "\n");
                strcpy(newDirPath, token);
                getstr(newDirName);
                token = strtok(newDirName, "\n");
                strcat(newDirPath, "/");
                strcat(newDirPath, newDirName);
                mvwprintw(w_info,5,0,"%s", newDirPath);
                wrefresh(w_info);
                wclear(w_macros);
                mkdir(newDirPath, 0777);
                noecho();
                goto loadNewDir;
                break;
            }
            

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

        wattron(w_macros, A_STANDOUT);
        sprintf(option, "%s", shortcut[topOption]);
        mvwprintw(w_macros, 0, topOption*5, "%s", option);
        wattroff(w_macros, A_STANDOUT);
        wrefresh(w_macros);
        
        wattron(w_command, COLOR_PAIR(3) | A_BOLD);
        if (commandFlag == 0)
        {
            if (isFile(strtok(display[i], "\n")))
            {
                mvwprintw(w_command, 0, 0, "Command: gedit %s", display[i]);
                wrefresh(w_command);
                wclear(w_command);
            }
            else if (isDir(strtok(display[i], "\n")))
            {
                mvwprintw(w_command, 0, 0, "Command: cd %s", display[i]);
                wrefresh(w_command);
                wclear(w_command);
            }
        }
        else if (commandFlag == 1){
            if (topOption == 0)
            {
                mvwprintw(w_command, 0, 0, "Command: mkdir 'DirectoryName'");
                wrefresh(w_command);
                wclear(w_command);
            }
            else if (topOption == 1)
            {
                mvwprintw(w_command, 0, 0, "Command: Gnoblin");
                wrefresh(w_command);
                wclear(w_command);
            }
            else if(topOption == 2)
            {
                mvwprintw(w_command, 0, 0, "Command: GNOME");
                wrefresh(w_command);
                wclear(w_command);
            }
        }

        wattron(w_exp, COLOR_PAIR(2));
        wattroff(w_exp, A_BOLD);
        wclear(w_info);
        mvwprintw(w_info, 0, 0, "File: %d/%d", currPoint, p);
        mvwprintw(w_info, 1, 0, "%s", pwd);
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
