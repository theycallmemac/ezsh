#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./utils/explorer.h"

#define ARRAYSIZE(a) (sizeof(a))/sizeof(a[0])

int main(int argc, char *argv[]) {
    
    FILE *fptr;
    char command[50];
    char **currdir;
    char userInput[1];
    char user[10];
    
    /*ncurses Initial setup*/ 
    WINDOW * w_exp;
    initscr();
    w_exp = newwin( 20, 20, 1, 1);
    noecho();
    curs_set(FALSE);
    keypad(w_exp, TRUE);

start:
    /*Allocate memory for currdir*/
    if (( currdir = malloc( 100*sizeof( char* ))) == NULL){}
    for (int i = 0; i < 100; i++){
        if ((currdir[i] = malloc(100)) == NULL){
            perror("ezsh");
        }
    }
    
    strcpy(command, "/bin/ls");
    /*Revised ls that returns ttl file count*/
    int p = expls(fptr, command, currdir) -1;
    int i = 0;
    
    /*Current dir listings*/
    wrefresh(w_exp);
    wattron(w_exp, A_STANDOUT);
    for(i=0; i<100; i++){
        if( i == 0 ){ 
            wattron( w_exp, A_STANDOUT );
        }
        else {
            wattroff( w_exp, A_STANDOUT );
        sprintf(user ,"%s",  currdir[i]);
        mvwprintw( w_exp, i+1, 2, "%s", user);
        }
    }
        wrefresh(w_exp);

    i = 0;
    int ch = 0; //user input
    char * token;


    while(ch = wgetch(w_exp)){

        sprintf(user ,"%s",  currdir[i]);
        mvwprintw( w_exp, i+1, 2, "%s", user);
        switch( ch ) {
                case KEY_UP:
                            i--;
                            i = ( i<0 ) ? p : i;
                            break;
                case KEY_DOWN:
                            i++;
                            i = ( i>p) ? 0 : i;
                            break;
                case 0x0A: //Enter key (not numpad)
                            token = strtok(currdir[i], "\n"); //parsing for expls (removes newline)
                            chdir(currdir[i]);
                            wrefresh(w_exp);
                            goto start; //Jump to start but load new files
            }

        /*Update options accordingly after user input*/
            wattron( w_exp, A_STANDOUT);
            sprintf(user ,"%s",  currdir[i]);
            mvwprintw( w_exp, i+1, 2, "%s", user);
            wattroff(w_exp , A_STANDOUT);

    }
    endwin();
    return 0;
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