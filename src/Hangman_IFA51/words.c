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
                char statusMsg[256];

                clearBottomLine();

                switch (i) {
                    case 0:
                        // Level easy
                        _fullpath(canonPath, "..\\words\\level_easy", 265); // "Implicit declaration". BULLSHIT. It's located in stdlib.h!
                        //s//printf(statusMsg, "%s...", canonPath);
                        //printBottomCentre(statusMsg);
                        if (access(canonPath, F_OK) != -1) {
                            ////printf("Exists!\n");
                        } else {
                            //printf("Doesn't exist!\n");
                        }
                        result = CopyFile(canonPath, filePaths[i], true);
                        //printf("Copying to file %s", filePaths[i]);
                        if (result <= 0) {
                            //printf("...FAILED!\n");
                        } else {
                            //printf("...SUCCESS!\n");
                        }
                        break;
                    case 1:
                        // Level medium
                        _fullpath(canonPath, "..\\words\\level_medium", 265); // Same here
                        //s//printf(statusMsg, "%s...", canonPath);
                        //printBottomCentre(statusMsg);
                        if (access(canonPath, F_OK) != -1) {
                            //printf("Exists!\n");
                        } else {
                            //printf("Doesn't exist!\n");
                        }
                        result = CopyFile(canonPath, filePaths[i], true);
                        //printf("Copying to file %s", filePaths[i]);
                        if (result <= 0) {
                            //printf("...FAILED!\n");
                        } else {
                            //printf("...SUCCESS!\n");
                        }
                        break;
                    case 2:
                        // Level hard
                        _fullpath(canonPath, "..\\words\\level_hard", 265);
                        //s//printf(statusMsg, "%s...", canonPath);
                        //printBottomCentre(statusMsg);
                        if (access(canonPath, F_OK) != -1) {
                            //printf("Exists!\n");
                        } else {
                            //printf("Doesn't exist!\n");
                        }
                        result = CopyFile(canonPath, filePaths[i], true);
                        //printf("Copying to file %s", filePaths[i]);
                        if (result <= 0) {
                            //printf("...FAILED!\n");
                        } else {
                            //printf("...SUCCESS!\n");
                        }
                        break;
                    case 3:
                        // Level insane
                        _fullpath(canonPath, "..\\words\\level_insane", 265);
                        //s//printf(statusMsg, "%s...", canonPath);
                        //printBottomCentre(statusMsg);
                        if (access(canonPath, F_OK) != -1) {
                            //printf("Exists!\n");
                        } else {
                            //printf("Doesn't exist!\n");
                        }
                        result = CopyFile(canonPath, filePaths[i], true);
                        //printf("Copying to file %s", filePaths[i]);
                        if (result <= 0) {
                            //printf("...FAILED!\n");
                        } else {
                            //printf("...SUCCESS!\n");
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
        char *read;
        int index = 0;
        char wordContainer[5000][150];

        printRight(filePaths[i], 3);

        fPointer = fopen(filePaths[i], "r");
        if (fPointer == NULL) {
            printError("Error occurred while opening file!");
            exit(0x002);
        }

        // Re-coding.
        // Apparently the fucker doesn't work...
        // (c) Iron@Stackoverflow.com
        int maximumLineLength = 128;
        char *lineBuffer = (char *)malloc(sizeof(char) * maximumLineLength);

        if (lineBuffer == NULL) {
            printError("Error allocating memory for line buffer.");
            exit(0x003);
        }

        char ch = getc(fPointer);
        int count = 0;

        do {
            while ((ch != '\n') && (ch != EOF)) {
                if (count == maximumLineLength) {
                    maximumLineLength += 128;
                    lineBuffer = realloc(lineBuffer, maximumLineLength);
                    if (lineBuffer == NULL) {
                        printError("Error reallocating space for line buffer.");
                        exit(0x004);
                    }
                }
                lineBuffer[count] = ch;
                count++;

                ch = getc(fPointer);
            }

            lineBuffer[count] = '\0';
            char line[count + 1];
            strncpy(line, lineBuffer, (count + 1));
            free(lineBuffer);
            const char *constLine = line;

            // Test code
            printRight(constLine, 6);
            Sleep(750);
            clearLine(6);
        } while (ch != EOF);



        fclose(fPointer);

    }

    return words;
}
