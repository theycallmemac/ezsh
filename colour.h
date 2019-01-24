#include <stdio.h>

void red(){
    printf("\033[0;31m");
}
void bold_red(){
    printf("\33[1;31m");
}
void green(){
    printf("\33[0;32m");
}
void bold_green(){
    printf("\33[1;32m");
}
void yellow(){
    printf("\33[0;33m");
}
void bold_yellow(){
    printf("\33[1;33m");
}
void blue(){
    printf("\33[0;34m");
}
void bold_blue(){
    printf("\33[1;34m");
}
void magenta(){
    printf("\33[0;35m");
}
void bold_magenta(){
    printf("\33[1;35m");
}
void cyan(){
    printf("\33[0;36m");
}
void bold_cyan(){
    printf("\33[1;36m");
}
void reset(){
    printf("\33[0m");
}
