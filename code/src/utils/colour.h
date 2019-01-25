#include <stdio.h>

char* red(){
    printf("\033[0;31m");
    return "\\33[0;31m";
}

char* bold_red(){
    printf("\33[1;31m");
    return "\\33[1;31m";
}

char* green(){
    printf("\33[0;32m");
    return "\\33[0;32m";
}

char* bold_green(){
    printf("\33[1;32m");
    return "\\33[1;32m";
}

char* yellow(){
    printf("\33[0;33m");
    return "\\33[0;33m";
}

char* bold_yellow(){
    printf("\33[1;33m");
    return "\\33[1;33m";
}

char* blue(){
    printf("\33[0;34m");
    return "\\33[0;34m";
}

char* bold_blue(){
    printf("\33[1;34m");
    return "\\33[1;34m";
}

char* magenta(){
    printf("\33[0;35m");
    return "\\33[0;35m";
}

char* bold_magenta(){
    printf("\33[1;35m");
    return "\\33[1;35m";
}

char* cyan(){
    printf("\33[0;36m");
    return "\\33[0;36m";
}

char* bold_cyan(){
    printf("\33[1;36m");
    return "\\33[1;36m";
}

char* reset(){
    printf("\33[0m");
    return "\\33[0m";
}
