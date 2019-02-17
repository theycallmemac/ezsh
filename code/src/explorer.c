#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./utils/explorer.h"

void main() {
    
    const int MAXSIZE = 20;
    const int OPTIONS = 15;

    FILE *fptr;
    char command[50];
    char **currdir;
    char userInput[1];
    char user[10];
    char *display[100];
    char pwd[200];
    
    /*ncurses Initial setup*/ 
    WINDOW * w_exp;
    initscr();
    w_exp = newwin( MAXSIZE, 50, 1, 1);
    noecho();
    curs_set(FALSE);
    keypad(w_exp, TRUE);
    start_color();
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);

loadNewDir:
    /*Allocate memory for currdir*/
    currdir = malloc( 100*sizeof( char* ));
    for (int i = 0; i < 100; i++){
        if ((currdir[i] = malloc(100)) == NULL){
            perror("ezsh");
        }
    }

    strcpy(pwd,exppwd(fptr));
    
    /*Revised ls that returns ttl file count*/
    strcpy(command, "/bin/ls");
    int p = expls(fptr, command, currdir)-1;
    //Track users section in currdir array (All files)
    int currSection = 0;
    int currPoint = 0;
    //Discern whether user wants to load next page or last page
    bool forward_flag = 1;

loadPage:
    wclear(w_exp);
    wrefresh(w_exp);
    currSection;
    int i;
    
    for (int i = 0; i < 100; i++){
        if ((display[i] = malloc(100)) == NULL){
            perror("ezsh");
        }
    }
    
    //Load next 15 entries on menu, set selected option to top file
    if(forward_flag){
        i = 0;
        for(int j=0; j<OPTIONS; j++){
            strcpy(display[j],currdir[currSection]);
            currSection++;
        }
    //Set currSection back to last pages position, load 15 entries, set selected option to bottom file
    } else {
        i = 14;
        currSection -= 30;
        forward_flag = 1;
        for(int j=0; j<OPTIONS; j++){
            strcpy(display[j],currdir[currSection]);
            currSection++;
            }
    }
    wattroff(w_exp, A_BOLD);
    wattron(w_exp, A_UNDERLINE | COLOR_PAIR(2));
    mvwprintw(w_exp, 0,2,pwd);
    wattroff(w_exp, A_UNDERLINE);
    /*Current dir listings*/
    for(int n=0; n<=OPTIONS; n++){
            wattron(w_exp, A_STANDOUT);
            wattroff( w_exp, A_STANDOUT );
            if(n == 0 && currPoint == 0){
                wattron(w_exp,COLOR_PAIR(1));
            }
            else if(isFile(strtok(display[n], "\n"))){
                wattron(w_exp,COLOR_PAIR(2));
                wattroff(w_exp, A_BOLD);
            }else if(isDir(strtok(display[n], "\n"))){
                wattron(w_exp,COLOR_PAIR(1)| A_BOLD);
            }
            sprintf(user ,"%s",  display[n]);
            mvwprintw( w_exp, n+1, 2, "%s", user);
    }
    wrefresh(w_exp);

    int ch = 0; //user input
    char * token;

    while(ch = wgetch(w_exp)){
        sprintf(user ,"%s",  display[i]);
        mvwprintw( w_exp, i+1, 2, "%s", user);
        switch( ch ) {
                case KEY_UP:
                            i--;
                            currPoint--;
                            if(i == -1 && currPoint == -1){
                                i = 0;
                                currPoint = 0;
                            }
                            if (i == -1 ) {
                                forward_flag = 0;
                                goto loadPage;
                            }
                            break;
                case KEY_DOWN:
                            i++;
                            currPoint++;
                            if((i > (p%OPTIONS)) && (currPoint > p)){
                                i = (p%OPTIONS);
                                currPoint = p;
                            }
                            if(i == OPTIONS){
                                goto loadPage;
                            }
                            break;
                case 0x0A: //Enter key (not numpad)
                            token = strtok(display[i], "\n"); //parsing for expls (removes newline)
                            chdir(display[i]);
                            //Reset screen completely
                            wclear(w_exp);
                            wrefresh(w_exp);
                            goto loadNewDir; //Jump to start but load new files
            }

        /*Update options accordingly after user input*/
            wattron( w_exp, A_STANDOUT);
            if(isFile(strtok(display[i], "\n"))){
                wattron(w_exp,COLOR_PAIR(2));
                wattroff(w_exp, A_BOLD);
            } else if(isDir(strtok(display[i], "\n"))){
                wattron(w_exp,COLOR_PAIR(1)| A_BOLD);
            }
            sprintf(user ,"%s",  display[i]);
            mvwprintw( w_exp, i+1, 2, "%s", user);
            wattroff(w_exp , A_STANDOUT);

    }
    endwin();
}

    //     while(1){            
    //     scanf("%s", userInput);
        
    //     if(strcmp("ls",userInput)==0){
    //         /*Allocate memory for currdir*/
    //         if (( currdir = malloc( 100*sizeof( char* ))) == NULL){}
    //             for (int i = 0; i < 100; i++){
    //                 if ((currdir[i] = malloc(100)) == NULL){
    //                     perror("ezsh");
    //                     }
    //             }
    //         /*char array of char arrays*/
    //         strcpy(command, "/bin/ls");
    //         expls(fptr, command, currdir);
    //         for(int i=0; i<100; i++){
    //             printf("%s", currdir[i]);
    //         }
    //     }
    //     else if(strncmp("cd",userInput,2)==0){
    //         char userDir[100];
    //         scanf("%s",userDir);
            
    //         /*If directory chdir*/
    //         if(isDir(userDir) == 1){
    //             printf("Is dir: %d\n",isDir(userDir));
    //             chdir(userDir);
    //         }
    //         /*If file do nothing */
    //         else if(isFile(userDir) == 1){
    //             printf("Is file: %d\n",isFile(userDir));
    //         }
    //     }
    //     else {
    //         printf("Nothing hit\n");
    //     }