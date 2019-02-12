#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../../cu/cu.h"
#include "../../../src/utils/explorer.h"

static const char PATH[] = "./staticTestDir";

TEST(test1) {
    char **files;
    if (( files = malloc( 100*sizeof( char* ))) == NULL){}
        for (int i = 0; i < 100; i++){
            if ((files[i] = malloc(100)) == NULL){
                perror("ezsh");
            }
        }
    strcpy(files[0], "file.txt\n");
    strcpy(files[1], "testDir\n");

    chdir(PATH);
    FILE *fp;
    char **dirFiles;

    if (( dirFiles = malloc( 100*sizeof( char* ))) == NULL){}
        for (int i = 0; i < 100; i++){
            if ((dirFiles[i] = malloc(100)) == NULL){
                perror("ezsh");
            }
        }

    bool isEqual = true;
    expls(fp, "/bin/ls", dirFiles);
    for(int i = 0; i <= 1; i++) {
        if (strcmp(files[i], dirFiles[i])== 1){
            isEqual = false;
            break;
        }
    }
    assertTrue(isEqual);
}
TEST(test2) {
    char **files;
    if (( files = malloc( 100*sizeof( char* ))) == NULL){}
        for (int i = 0; i < 100; i++){
            if ((files[i] = malloc(100)) == NULL){
                perror("ezsh");
            }
        }

    strcpy(files[0], "notAFile.txt");
    strcpy(files[1], "notADir");
    chdir(PATH);
    FILE *fp;
    char **dirFiles;
    if (( dirFiles = malloc( 100*sizeof( char* ))) == NULL){}
        for (int i = 0; i < 100; i++){
            if ((dirFiles[i] = malloc(100)) == NULL){
                perror("ezsh");
            }
        }

    expls(fp, "/bin/ls", dirFiles);
    bool isEqual = true;
    for(int i = 0; i <= 1; i++) {
        if (strcmp(files[i], dirFiles[i]) != 0){
            isEqual = false;
            break;
        }
    }
    assertFalse(isEqual);
}
