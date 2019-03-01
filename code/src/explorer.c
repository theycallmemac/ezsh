#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h> 

#include "./utils/explorer.h"
#include "./utils/commands/cd.h"

void pipeWrite(char* msg){
    int pipeFile;
    char * pipePath = "/tmp/ezshMsgPasser";
    pipeFile = open(pipePath, O_WRONLY);
    write(pipeFile, msg, strlen(msg)+1);
    close(pipeFile);
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
    char **currdir;
    char option[10];
    char macroOption[10];
    char pwd[100];
    char newDirPath[100];
    char newEntry[80];
    char **display;

    char shortcut[3][10] = {"MKDIR", "HOME", "TOUCH"};

    /*ncurses Initial setup*/
    WINDOW *w_exp;
    WINDOW *w_command;
    WINDOW *w_info;
    WINDOW *w_macros;
    WINDOW *w_form;
    WINDOW *w_help;
    
    int p;
    int pipeFile;
    char * pipePath = "/tmp/ezshMsgPasser";
    mkfifo(pipePath, 0666);

loadNewDir:
    initscr();

    /*Allocate memory for currdir*/
    currdir = mallocStrArr(100, 100);

    p = expls(fptr, "/bin/ls", currdir) - 1;
    w_exp = newwin(p + 2, 100, MARGINTOP, 1); //Interactive file explorer(Center; left)
    w_command = newwin(2, 30, 0, 21);         //Command required to execute(Top; right)
    w_info = newwin(8, 50, 20, 2);            //Info on FE(Bottom; left)
    w_macros = newwin(3, 20, 0, 3);           //QuickCommands(Top; left)
    w_form = newwin(1, 60, 20, 2);
    w_help = newwin(50, 100, 0, 2);

    noecho();
    curs_set(FALSE);
    keypad(w_exp, TRUE);
    start_color();

    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_MAGENTA, COLOR_BLACK);

    /*MessagePassing to prompt*/
    system("");
    char *dirMsg = "YELL='\033[1;33m' && WHITE='\033[0m' && CDVAR='cd ' && echo ${YELL}'Command -->' ${WHITE}$CDVAR$PWD > $(tail -1 ~/.ezsh/.ezsh.tty)\n";
    system(dirMsg);

    strcpy(pwd, exppwd(fptr));
    pipeWrite(strtok(pwd,"\n"));

    /*Revised ls that returns ttl file count*/
    //Track options section in currdir array (All files)
    int currSection = 0;
    int currPoint = 0;
    //Discern whether user wants to load next page or last page
    bool forward_flag = 1;


loadPage:
    wclear(w_exp);
    refresh();

    currSection;
    int optionIndex;

    display = mallocStrArr(100, 100);

    /*Load next n OPTIONS on menu, set selected option to top file*/
    if (forward_flag)
    {
        optionIndex = 0;
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
        optionIndex = 14;
        currSection -= 30;
        forward_flag = 1;
        for (int j = 0; j < OPTIONS; j++)
        {
            strcpy(display[j], currdir[currSection]);
            currSection++;
        }
    }

/*Reload windows on resizing of terminal*/
resizeRefresh:
    /*Current dir listings*/
    for (int n = 0; n <= OPTIONS; n++)
    {
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

    /*Current position in directory*/
    wattron(w_command, COLOR_PAIR(3) | A_BOLD);
    wattron(w_macros, A_BOLD | A_UNDERLINE);
    mvwprintw(w_info, 0, 0, "File: %d/%d", currPoint, p);
    mvwprintw(w_info, 1, 0, "%s", pwd);
    mvwprintw(w_info, 2, 0, "Press 'h' for help");
    mvwprintw(w_command, 0, 0, "Command:");

    /*QuickCommand Menu*/
    for (int optionIndex = 0; optionIndex < 3; optionIndex++)
    {
        if (optionIndex != 0)
        {
            wattroff(w_macros, A_STANDOUT);
            sprintf(macroOption, "%s", shortcut[optionIndex]);
            mvwprintw(w_macros, 0, optionIndex * 6, "%s", macroOption);
        }
    }

    refresh();

    int ch = 0;        //user input
    char *token;       //Store Parsed string
    int topOption = 0; //Quick Command option
    int commandFlag;   //What menu to display command from

    do
    {
        sprintf(macroOption, "%s", shortcut[topOption]);
        mvwprintw(w_macros, 0, topOption * 6, "%s", macroOption);

        sprintf(option, "%s", display[optionIndex]);
        mvwprintw(w_exp, optionIndex + PADDINGTOP, 2, "%s", option);

        refresh();
        switch (ch)
        {
        case KEY_UP:
            optionIndex--;
            currPoint--;
            commandFlag = 0;
            if (optionIndex == -1 && currPoint == -1)
            {
                optionIndex = 0;
                currPoint = 0;
            }
            if (optionIndex == -1)
            {
                forward_flag = 0;

                goto loadPage;
            }
            break;
        case KEY_DOWN:
            optionIndex++;
            currPoint++;
            commandFlag = 0;
            if ((optionIndex > (p % OPTIONS)) && (currPoint > p))
            {
                optionIndex = (p % OPTIONS);
                currPoint = p;
            }
            if (optionIndex == OPTIONS)
            {

                goto loadPage;
            }
            break;

        case 0x9: //Tab Key
            topOption++;
            commandFlag = 1;
            topOption = (topOption > 2) ? 0 : topOption;
            break;
        case 0x20: //SpaceBar
            if (topOption == 0)
            {
                wclear(w_command);
                mvwprintw(w_command, 0, 0, "Command: mkdir 'Directory'");
                wrefresh(w_command);
                wattron(w_form, COLOR_PAIR(4));
                echo();
                token = strtok(pwd, "\n");
                strcpy(newDirPath, token);
                mvwprintw(w_form, 0, 0, "New Directory: ");
                wgetstr(w_form, newEntry);
                strcat(newDirPath, "/");
                strcat(newDirPath, newEntry);
                mkdir(newDirPath, 0777);
                noecho();
                wclear(w_form);
                wrefresh(w_form);
                free(currdir);
                free(display);
                goto loadNewDir;
            }
            else if (topOption == 1)
            {
                chdir(changeHome());
                free(currdir);
                free(display);
                goto loadNewDir;
            }
            else if (topOption == 2)
            {
                wclear(w_command);
                mvwprintw(w_command, 0, 0, "Command: touch 'fileName'");
                wrefresh(w_command);
                wattron(w_form, COLOR_PAIR(4));
                echo();
                mvwprintw(w_form, 0, 0, "New File: ");
                wgetstr(w_form, newEntry);
                touch(newEntry);
                noecho();
                wclear(w_form);
                wrefresh(w_form);
                free(currdir);
                free(display);
                goto loadNewDir;
            }
        case 0x72:
            token = strtok(display[optionIndex], "\n"); //parsing for expls (removes newline)
            char remF[100];
            char answer[10];

            if (isDir(token))
            {
                wclear(w_command);
                mvwprintw(w_command, 0, 0, "Command: rm -rf %s", display[optionIndex]);
                wrefresh(w_command);
                strcpy(remF, "rm -rf ");
                strcat(remF, token);
                wattron(w_form, COLOR_PAIR(4));
                echo();
                mvwprintw(w_form, 0, 0, "Type 'YeS' to delete %s or 'no' to exit. ", token);
                wgetstr(w_form, answer);
                noecho();
                if (strcmp(answer, "YeS") == 0)
                {
                    system(remF);
                }
                else
                {
                    free(currdir);
                    free(display);
                    goto loadNewDir;
                }
                free(currdir);
                free(display);
                goto loadNewDir; //Jump to start but load new files
            }
            else if (isFile(token))
            {
                wclear(w_command);
                mvwprintw(w_command, 0, 0, "Command: rm %s", display[optionIndex]);
                wrefresh(w_command);
                strcpy(remF, "rm ");
                strcat(remF, token);
                wattron(w_form, COLOR_PAIR(4));
                echo();
                mvwprintw(w_form, 0, 0, "Type 'YeS' to delete %s or 'no' to exit. ", token);
                wgetstr(w_form, answer);
                noecho();
                if (strcmp(answer, "YeS") == 0)
                {
                    system(remF);
                }
                else
                {
                    free(currdir);
                    free(display);
                    goto loadNewDir;
                }
            }
            free(currdir);
            free(display);
            goto loadNewDir; //Jump to start but load new files

        case 0x0A:                                      //Enter key (not numpad)
            token = strtok(display[optionIndex], "\n"); //parsing for expls (removes newline)
            if (isDir(token) || strcmp(token, "..") == 0)
            {
                chdir(display[optionIndex]);
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

        case 0x68: // Hex for 'h'; display help screen
            clear();
            refresh();
            wclear(w_help);
            wattron(w_help, COLOR_PAIR(1) | A_BOLD);
            mvwprintw(w_help, 2, 2, "File Explorer:");
            wattroff(w_help, COLOR_PAIR(1) | A_BOLD);
            mvwprintw(w_help, 4, 2, "-Use the UP and Down Arrows to navigate the FileExplorer");
            mvwprintw(w_help, 6, 2, "-Press Enter to open current FileExplorer Option");

            wattron(w_help, COLOR_PAIR(1) | A_BOLD);
            mvwprintw(w_help, 9, 2, "Quick Commands:");
            wattroff(w_help, COLOR_PAIR(1) | A_BOLD);
            mvwprintw(w_help, 11, 2, "-Use the TAB to cycle through top menu");
            mvwprintw(w_help, 13, 2, "-Press SpaceBar to execute current top menu option");
            mvwprintw(w_help, 15, 2, "-Press 'r' to delete a File or Directory");
            wattron(w_help, A_BLINK);
            mvwprintw(w_help, 20, 0, "Press 'q' to quit helpscreen");
            wattroff(w_help, A_BLINK);
            wrefresh(w_help);
            while (ch = wgetch(w_help))
            {
                if (ch == 0x71)
                {
                    /* code */
                    wclear(w_help);
                    wrefresh(w_help);
                    free(currdir);
                    free(display);
                    goto loadNewDir;
                }
            }
        }

        /*Update options accordingly after option input*/

        wattron(w_macros, A_STANDOUT);
        sprintf(option, "%s", shortcut[topOption]);
        mvwprintw(w_macros, 0, topOption * 6, "%s", option);
        wattroff(w_macros, A_STANDOUT);
        wrefresh(w_macros);

        //What command to display in top right based of flag
        if (commandFlag == 0)
        {
            if (isFile(strtok(display[optionIndex], "\n")))
            {
                mvwprintw(w_command, 0, 0, "Command: gedit %s", display[optionIndex]);
                wrefresh(w_command);
                wclear(w_command);
            }
            else if (isDir(strtok(display[optionIndex], "\n")))
            {
                mvwprintw(w_command, 0, 0, "Command: cd %s", display[optionIndex]);
                wrefresh(w_command);
                wclear(w_command);
            }
        }
        else if (commandFlag == 1)
        {
            if (topOption == 0)
            {
                mvwprintw(w_command, 0, 0, "Command: mkdir 'DirectoryName'");
                wrefresh(w_command);
                wclear(w_command);
            }
            else if (topOption == 1)
            {
                mvwprintw(w_command, 0, 0, "Command: $HOME");
                wrefresh(w_command);
                wclear(w_command);
            }
            else if (topOption == 2)
            {
                mvwprintw(w_command, 0, 0, "Command: touch 'fileName'");
                wrefresh(w_command);
                wclear(w_command);
            }
        }

        //Update and ensure File/Directory style stays consistent
        wattron(w_exp, COLOR_PAIR(2));
        wattroff(w_exp, A_BOLD);
        wclear(w_info);
        mvwprintw(w_info, 0, 0, "File: %d/%d", currPoint, p);
        mvwprintw(w_info, 1, 0, "%s", pwd);
        wattron(w_info, A_BLINK | A_BOLD | COLOR_PAIR(3));
        mvwprintw(w_info, 2, 0, "Press 'h' for help");
        wattroff(w_info, A_BLINK | A_BOLD);
        wattron(w_info, COLOR_PAIR(2));
        wattron(w_exp, A_STANDOUT);
        wrefresh(w_info);

        if (isFile(strtok(display[optionIndex], "\n")))
        {
            wattron(w_exp, COLOR_PAIR(2));
            wattroff(w_exp, A_BOLD);
        }
        else if (isDir(strtok(display[optionIndex], "\n")))
        {
            wattron(w_exp, COLOR_PAIR(1) | A_BOLD);
        }
        sprintf(option, "%s", display[optionIndex]);
        mvwprintw(w_exp, optionIndex + PADDINGTOP, 2, "%s", option);
        wattroff(w_exp, A_STANDOUT | A_UNDERLINE);
    } while (ch = wgetch(w_exp));
}
