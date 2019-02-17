#include <stdio.h>

// prints and returns char* ansi red
char* red(){
    printf("\033[0;31m");
    return "\\33[0;31m";
}


// prints and returns char* bold ansi red
char* bold_red(){
    printf("\33[1;31m");
    return "\\33[1;31m";
}


// prints and returns char* ansi green
char* green(){
    printf("\33[0;32m");
    return "\\33[0;32m";
}


// prints and returns char* bold ansi green
char* bold_green(){
    printf("\33[1;32m");
    return "\\33[1;32m";
}


// prints and returns char* ansi yellow
char* yellow(){
    printf("\33[0;33m");
    return "\\33[0;33m";
}


// prints and returns char* bold ansi yellow
char* bold_yellow(){
    printf("\33[1;33m");
    return "\\33[1;33m";
}


// prints and returns char* ansi blue
char* blue(){
    printf("\33[0;34m");
    return "\\33[0;34m";
}


// prints and returns char* bold ansi blue
char* bold_blue(){
    printf("\33[1;34m");
    return "\\33[1;34m";
}


// prints and returns char* ansi magenta
char* magenta(){
    printf("\33[0;35m");
    return "\\33[0;35m";
}


// prints and returns char* bold ansi magenta
char* bold_magenta(){
    printf("\33[1;35m");
    return "\\33[1;35m";
}

// prints and returns char* ansi cyan
char* cyan(){
    printf("\33[0;36m");
    return "\\33[0;36m";
}


// prints and returns char* bold bold ansi cyan
char* bold_cyan(){
    printf("\33[1;36m");
    return "\\33[1;36m";
}


// prints and returns ansi white, which is know as resetting the color palette
char* reset(){
    printf("\33[0m");
    return "\\33[0m";
}
