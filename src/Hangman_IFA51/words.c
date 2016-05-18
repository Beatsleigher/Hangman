// Written by Simon Cahill
// Copyright (c) 2016
// All Right Reserved
// Copies and modifications of this file are prohibited and punishable by law,
// unless done with EXPRESS PERMISSION by the author of this file.

#define _GNU_SOURCE

// Project includes
#include "systemio.h"
#include "words.h"
#include "ui.h"

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
                        _fullpath(canonPath, "..\\words\\level_easy", 265); // "Implicit declaration". BULLSHIT. It's located in stdlib.h!
                        //printf("%s...", canonPath);
                        if (access(canonPath, F_OK) != -1) {
                            //printf("Exists!\n");
                        } else {
                            //printf("Doesn't exist!\n");
                        }
                        result = CopyFile(canonPath, filePaths[i], true);
                        //printf("Copying to file %s", filePaths[i]);
                        if (result <= 0) {
                            printf("...FAILED!\n");
                        } else {
                            printf("...SUCCESS!\n");
                        }
                        break;
                    case 1:
                        // Level medium
                        _fullpath(canonPath, "..\\words\\level_medium", 265); // Same here
                        //printf("%s...", canonPath);
                        if (access(canonPath, F_OK) != -1) {
                            //printf("Exists!\n");
                        } else {
                            //printf("Doesn't exist!\n");
                        }
                        result = CopyFile(canonPath, filePaths[i], true);
                        //printf("Copying to file %s", filePaths[i]);
                        if (result <= 0) {
                            printf("...FAILED!\n");
                        } else {
                            printf("...SUCCESS!\n");
                        }
                        break;
                    case 2:
                        // Level hard
                        _fullpath(canonPath, "..\\words\\level_hard", 265);
                        //printf("%s...", canonPath);
                        if (access(canonPath, F_OK) != -1) {
                            //printf("Exists!\n");
                        } else {
                            //printf("Doesn't exist!\n");
                        }
                        result = CopyFile(canonPath, filePaths[i], true);
                        //printf("Copying to file %s", filePaths[i]);
                        if (result <= 0) {
                            printf("...FAILED!\n");
                        } else {
                            printf("...SUCCESS!\n");
                        }
                        break;
                    case 3:
                        // Level insane
                        _fullpath(canonPath, "..\\words\\level_insane", 265);
                        //printf("%s...", canonPath);
                        if (access(canonPath, F_OK) != -1) {
                            //printf("Exists!\n");
                        } else {
                            //printf("Doesn't exist!\n");
                        }
                        result = CopyFile(canonPath, filePaths[i], true);
                        //printf("Copying to file %s", filePaths[i]);
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

    // Read files
    for (int i = 0; i < sizeof(filePaths) / sizeof(filePaths[0]); i++) {

        FILE *fPointer;
        char *line = NULL;
        char *read;
        int index = 0;
        char wordContainer[5000][150];

        //printRight(filePaths[i], 3);

        fPointer = fopen(filePaths[i], "r");
        if (fPointer == NULL) {
            printf("Error occurred while opening file!");
            exit(0x002);
        }

        switch (i) {
            case 0:
                while (fgets(line, 256, fPointer) != NULL) {
                        if (line == NULL) {
                            printRight("ERROR: LINE IS NULL!", 4);
                            char lineMsg[150];
                            sprintf(lineMsg, "Line: %i", index);
                            printRight(lineMsg, 5);
                        } else {
                            strcpy(wordContainer[index], line);
                            printf(wordContainer[index]);
                        }
                        index++;
                }
                for (int i = 0; i < sizeof(words.easyWords) / sizeof(words.easyWords[0]); i++) {
                    strcpy(words.easyWords[i], wordContainer[i]);
                }
                break;
            case 1:
                while ((read = fgets(line, 256, fPointer)) != NULL) {
                        if (line == NULL) {
                            printRight("ERROR: LINE IS NULL!", 4);
                            char lineMsg[150];
                            sprintf(lineMsg, "Line: %i", index);
                            printRight(lineMsg, 5);
                        } else {
                            strcpy(wordContainer[index], line);
                            printf(wordContainer[index]);
                        }
                        index++;
                }
                for (int i = 0; i < sizeof(words.mediumWords) / sizeof(words.mediumWords[0]); i++) {
                    strcpy(words.mediumWords[i], wordContainer[i]);
                }
                break;
            case 2:
                while ((read = fgets(line, 256, fPointer)) != NULL) {
                        if (line == NULL) {
                            printRight("ERROR: LINE IS NULL!", 4);
                            char lineMsg[150];
                            sprintf(lineMsg, "Line: %i", index);
                            printRight(lineMsg, 5);
                        } else {
                            strcpy(wordContainer[index], line);
                            printf(wordContainer[index]);
                        }
                        index++;
                }
                for (int i = 0; i < sizeof(words.hardWords) / sizeof(words.hardWords[0]); i++) {
                    strcpy(words.hardWords[i], wordContainer[i]);
                }
                break;
            case 3:
                while ((read = fgets(line, 256, fPointer)) != NULL) {
                        if (line == NULL) {
                            printRight("ERROR: LINE IS NULL!", 4);
                            char lineMsg[150];
                            sprintf(lineMsg, "Line: %i", index);
                            printRight(lineMsg, 5);
                        } else {
                            strcpy(wordContainer[index], line);
                            printf(wordContainer[index]);
                        }
                        index++;
                }
                for (int i = 0; i < sizeof(words.insaneWords) / sizeof(words.insaneWords[0]); i++) {
                    strcpy(words.insaneWords[i], wordContainer[i]);
                }
                break;
            default:
                break;
        }

        fclose(fPointer);

    }

    return words;
}
