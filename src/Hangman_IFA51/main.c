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

int main() {

    char *welcome = "Welcome to Hangman";
    char *by = "By Simon C., Patrick M., Sergey S.";

    //printXYCentre(welcome);
    printCentre(by, getConsoleHeight() / 2);

    printBottomCentre("Initializing... please wait...");

    printProgressBar(20, 0);

    // Create directories needed by the program
    createDirectories();

    printProgressBar(50, 20);

    // Check if word files exist.
    struct WordCategories wordCategories;
    wordCategories = getWords();

    printProgressBar(75, 50);

    clearBottomLine();
    printBottomCentre("Memchecks in progress...");

    for (int i = 0; i < sizeof(wordCategories.easyWords) / sizeof(wordCategories.easyWords[0]); i++) {
        printRight(wordCategories.easyWords[i], 3);
        char index[5000];
        sprintf(index, "%i", i);
        printRight(index, 4);
        //Sleep(1000);
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
    int levelSelection = showGameMenu();

    return 0;
}
