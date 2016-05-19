// Written by Simon Cahill
// Copyright (c) 2016
// All Rights Reserved
// Copies and modifications of this file are prohibited and punishable by law,
// unless done with EXPRESS PERMISSION by the author of this file.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <winioctl.h>

// Project includes
#include "main.h"
#include "systemio.h"
#include "words.h"
#include "ui.h"
#include "game.h"

int main() {

    // Clear screen at very beginning to ensure clean output
    system("cls");

    char *by = "By Simon C., Patrick M., Sergey S.";
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    //printXYCentre(welcome);
    printCentre(by, getConsoleHeight() / 2);

    printBottomCentre("Initializing... please wait...");

    // Save current attributes
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    // Set console code page
//    SetConsoleOutputCP(CP_UTF8); // BIG NOPE

    // Set console window
    SetConsoleTitle("Hangman");

    // Set more console attributes
//    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
    // Easier solution
    system("color 0a"); // Set console colour to black background, light green text

    printProgressBar(20, 0);

    // Testing
    printMessage("Test Message", "This is a test");
    printMessage("Descriptive Message", "You can print up to sixty (60) characters in such a message!"); // I SWEAR THIS IS A COINCIDENCE!
    char messageLines[5][60];
    sprintf(messageLines[0], "");
    printMultilineMsg("Descriptive Message", messageLines);

    // Create directories needed by the program
    createDirectories();

    printProgressBar(50, 20);

    // Check if word files exist.
    struct WordCategories wordCategories;
    wordCategories = getWords();
    loadedWords = wordCategories;

    printProgressBar(75, 50);

    clearBottomLine();
    printBottomCentre("Memchecks in progress...");

    // Check for loading errors
    int errorCount = 0;
    for (int i = 0; i < sizeof(wordCategories.easyWords) / sizeof(wordCategories.easyWords[0]); i++) {
        if (wordCategories.easyWords[i] == NULL || wordCategories.easyWords[i] == "" || sizeof(wordCategories.easyWords[i] < 1)) {
            errorCount++;
        }
        //Sleep(1000);
    }

    for (int i = 0; i < sizeof(wordCategories.mediumWords) / sizeof(wordCategories.mediumWords[0]); i++) {
        if (wordCategories.mediumWords[i] == NULL || wordCategories.mediumWords[i] == "" || sizeof(wordCategories.mediumWords[i] < 1)) {
            errorCount++;
        }
        //Sleep(1000);
    }

    for (int i = 0; i < sizeof(wordCategories.hardWords) / sizeof(wordCategories.hardWords[0]); i++) {
        if (wordCategories.easyWords[i] == NULL || wordCategories.easyWords[i] == "" || sizeof(wordCategories.easyWords[i] < 1)) {
            errorCount++;
        }
        //Sleep(1000);
    }

    for (int i = 0; i < sizeof(wordCategories.easyWords) / sizeof(wordCategories.easyWords[0]); i++) {
        if (wordCategories.easyWords[i] == NULL || wordCategories.easyWords[i] == "" || sizeof(wordCategories.easyWords[i] < 1)) {
            errorCount++;
        }
        //Sleep(1000);
    }

    // If more than three errors are detected, show an error!
    if (errorCount >= 3) {
        char message[5][60];
        strcpy(message[0], "An error has occurred while loading words!");
        strcpy(message[1], "You may continue playing Hangman,");
        strcpy(message[2], "however some more errors may occur!");
        strcpy(message[3], "It is recommended you restart Hangman!");
        printMultilineError(message, 5);
    }

    printProgressBar(100, 75);

    Sleep(2000);
    clearScreen();
    printWelcomeScreen();

    // Wait for user input, then open menu
    printCentre("Hit [ ENTER ] to continue!", (getConsoleHeight() / 2) + 5);
    getchar();

    // Clear screen and send user to main menu
    clearScreen();
    showGameMenu();

    executeGame(wordCategories);

    // Restore saved console attrs. Saves us from getting warnings
    SetConsoleTextAttribute(hConsole, saved_attributes);

    return 0;
}
