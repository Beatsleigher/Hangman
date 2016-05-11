// Written by Simon Cahill
// Copyright (c) 2016
// All Right Reserved
// Copies and modifications of this file are prohibited and punishable by law,
// unless done with EXPRESS PERMISSION by the author of this file.

// Project includes
#include "systemio.h"
#include <windows.h>

///////////////////////////////////////
/// \brief Declare type, as to make
///         programming easier.
///////////////////////////////////////
typedef struct WordCategories WordCategories;

///////////////////////////////////////
/// \brief Method template
///////////////////////////////////////
struct WordCategories getWords();

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
                switch (i) {
                    case 0:
                        // Level easy
                        CopyFile(".\\level_easy", filePaths[i], true);
                        break;
                    case 1:
                        // Level medium
                        CopyFile(".\\level_medium", filePaths[i], true);
                        break;
                    case 2:
                        // Level hard
                        CopyFile(".\\level_hard", filePaths[i], true);
                        break;
                    case 3:
                        // Level insane
                        CopyFile(".\\level_insane", filePaths[i], true);
                        break;
                    default:
                        // Oops.
                        break;
                }
        }
    }
}
