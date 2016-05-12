// Written by Simon Cahill
// Copyright (c) 2016
// All Right Reserved
// Copies and modifications of this file are prohibited and punishable by law,
// unless done with EXPRESS PERMISSION by the author of this file.

// Project includes
#include "systemio.h"
#include "words.h"

// System includes
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wininet.h>
#include <windows.h>
#include <windowsx.h>
#include <sys/param.h>

///////////////////////////////////////
/// \brief Creates the files containing
///         the words if necessary.
///         Returns a struct containing
///         the words for use in the
///         program.
///////////////////////////////////////
struct WordCategories getWords() {
    struct WordCategories words;
    char filePaths[4][128];
    bool filesExist = wordFileExists();

    // Dear Dennis Ritchie: COULDN'T HAVE MADE THIS ANY MORE F*CKN COMPLICATED, COULD YA?!
    strcpy(filePaths[0], getenv("USERPROFILE"));
    strcpy(filePaths[1], getenv("USERPROFILE"));
    strcpy(filePaths[2], getenv("USERPROFILE"));
    strcpy(filePaths[3], getenv("USERPROFILE"));

    strcat(filePaths[0], "\\.hangman\\words\\level_easy");
    strcat(filePaths[1], "\\.hangman\\words\\level_medium");
    strcat(filePaths[2], "\\.hangman\\words\\level_hard");
    strcat(filePaths[3], "\\.hangman\\words\\level_insane");

    if (!filesExist) {
        for (int i = 0; i < sizeof(filePaths) / sizeof(filePaths[0]); i++) {
                int result;
                char canonPath[256];
                switch (i) {
                    case 0:
                        // Level easy
                        _fullpath(canonPath, "..\\words\\level_easy", 265);
                        printf("%s...", canonPath);
                        if (access(&canonPath, F_OK) != -1) {
                            printf("Exists!\n");
                        } else {
                            printf("Doesn't exist!\n");
                        }
                        result = CopyFile(canonPath, filePaths[i], true);
                        printf("Copying to file %s", filePaths[i]);
                        if (result <= 0) {
                            printf("...FAILED!\n");
                        } else {
                            printf("...SUCCESS!\n");
                        }
                        break;
                    case 1:
                        // Level medium
                        _fullpath(canonPath, "..\\words\\level_medium", 265);
                        printf("%s...", canonPath);
                        if (access(&canonPath, F_OK) != -1) {
                            printf("Exists!\n");
                        } else {
                            printf("Doesn't exist!\n");
                        }
                        result = CopyFile(canonPath, filePaths[i], true);
                        printf("Copying to file %s", filePaths[i]);
                        if (result <= 0) {
                            printf("...FAILED!\n");
                        } else {
                            printf("...SUCCESS!\n");
                        }
                        break;
                    case 2:
                        // Level hard
                        _fullpath(canonPath, "..\\words\\level_hard", 265);
                        printf("%s...", canonPath);
                        if (access(&canonPath, F_OK) != -1) {
                            printf("Exists!\n");
                        } else {
                            printf("Doesn't exist!\n");
                        }
                        result = CopyFile(canonPath, filePaths[i], true);
                        printf("Copying to file %s", filePaths[i]);
                        if (result <= 0) {
                            printf("...FAILED!\n");
                        } else {
                            printf("...SUCCESS!\n");
                        }
                        break;
                    case 3:
                        // Level insane
                        _fullpath(canonPath, "..\\words\\level_insane", 265);
                        printf("%s...", canonPath);
                        if (access(&canonPath, F_OK) != -1) {
                            printf("Exists!\n");
                        } else {
                            printf("Doesn't exist!\n");
                        }
                        result = CopyFile(canonPath, filePaths[i], true);
                        printf("Copying to file %s", filePaths[i]);
                        if (result <= 0) {
                            printf("...FAILED!\n");
                        } else {
                            printf("...SUCCESS!\n");
                        }
                        break;
                    default:
                        // Oops.
                        break;
                }
        }
    }

    return words;
}
