// Written by Simon Cahill
// Copyright (c) 2016
// All Right Reserved
// Copies and modifications of this file are prohibited and punishable by law,
// unless done with EXPRESS PERMISSION by the author of this file.

//#include <userenv.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wininet.h>
#include <windows.h>
#include <windowsx.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

// Project includes
#include "systemio.h"

bool wordFileExists() {
    char filePaths[4][128];
    bool fileExists = false;

    // Dear Dennis Ritchie: COULDN'T HAVE MADE THIS ANY MORE F*CKN COMPLICATED, COULD YA?!
    strcpy(filePaths[0], getenv("USERPROFILE"));
    strcpy(filePaths[1], getenv("USERPROFILE"));
    strcpy(filePaths[2], getenv("USERPROFILE"));
    strcpy(filePaths[3], getenv("USERPROFILE"));

    strcat(filePaths[0], "\\.hangman\\words\\level_easy");
    strcat(filePaths[1], "\\.hangman\\words\\level_medium");
    strcat(filePaths[2], "\\.hangman\\words\\level_hard");
    strcat(filePaths[3], "\\.hangman\\words\\level_insane");

    for (int i = 0; i < sizeof(filePaths) / sizeof(filePaths[0]); i++) {
        //printf("%s...", filePaths[i]);
        if (access(filePaths[i], F_OK) != -1) {
            fileExists = true;
            //printf("Exists!\n");
        } else {
            fileExists = false;
            //printf("Doesn't exist!\n");
        }
    }

    return fileExists;

}

void saveWordsFile() {

}

void readWords(struct WordCategories *wordCats) {

}

void createDirectories() {

    char filePath[2][128];

    strcpy(filePath[0], getenv("USERPROFILE"));
    strcpy(filePath[1], getenv("USERPROFILE"));

    strcat(filePath[0], "\\.hangman\\");
    strcat(filePath[1], "\\.hangman\\words\\");

    for (int i = 0; i < sizeof(filePath) / sizeof(filePath[0]); i++) {
        //printf("Checking directory %s...", filePath[i]);
        struct stat info;

        if (stat(filePath[i], &info) != 0) {
            //printf("Doesn\'t exist! Will create...");
        } else if(info.st_mode & S_IFDIR) {
            //printf("Exists!\n");
            return;
        } else {
            //printf("Exists!\n");
            return;
        }

        if (_mkdir(filePath[i]) == 0) {
            //printf("SUCCESS!\n");
        } else {
            //printf("ERROR!\n");
        }

    }

}

int getConsoleXLen() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    return columns;
}
