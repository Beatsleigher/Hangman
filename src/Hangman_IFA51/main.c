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
    showGameMenu();

    executeGame(wordCategories);

    // Restore saved console attrs. Saves us from getting warnings
    SetConsoleTextAttribute(hConsole, saved_attributes);

    return 0;
}
