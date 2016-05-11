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
        /*printf("%s...", filePaths[i]);
        if (access(filePaths[i], F_OK) != -1) {
            fileExists = true;
            printf("Exists!\n");
        } else {
            fileExists = false;
            printf("Doesn't exist!\n");
        }*/
    }

    return fileExists;

}

//void downloadWordsFile() {
//    InternetOpen();                   // OBSOLETE
//}

void saveWordsFile() {

}

void readWords(struct WordCategories *wordCats) {

}
