// Written by Simon Cahill
// Copyright (c) 2016
// All Right Reserved
// Copies and modifications of this file are prohibited and punishable by law,
// unless done with EXPRESS PERMISSION by the author of this file.

// #DEFINES
#define UP_ARROW 72//22472//0x26
#define DOWN_ARROW 80//22480//0x28
#define W_KEY 119//0x57
#define S_KEY 115//0x53
#define RETURN_KEY 0x0D

#define LEVEL_EASY

// Project includes
#include "game.h"
#include "ui.h"

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
#include <conio.h>

int showGameMenu() {
    printMainMenu(0);
    int charKey;
    selectedLevel = 0;

    // Test code
//    printMessage("test", "This is a test!");
//    Sleep(2000);
//    printError("This is an error!");
//    clearScreen();
//    printMainMenu(0);

    // Read character. Wait for arrow keys.
    do {
        charKey = _getch();
        //printf("%i", charKey);
        if (charKey == UP_ARROW) {
            switch (selectedLevel) {
                case 0: // Level easy
                    selectedLevel = 0;
                    break;
                case 1: // Level medium
                    printMainMenu(0);
                    selectedLevel = 0;
                    break;
                case 2: // Level hard
                    printMainMenu(1);
                    selectedLevel = 1;
                    break;
                case 3: // Level insane
                    printMainMenu(2);
                    selectedLevel = 2;
                    break;
                default: // Error
                    printError("Error selecting level! Press ENTER to try again!");
                    clearScreen();
                    printMainMenu(selectedLevel);
                    break;
            }
        } else if (charKey == DOWN_ARROW) {
            switch (selectedLevel) {
                case 0: // Level easy
                    printMainMenu(1);
                    selectedLevel = 1;
                    break;
                case 1: // Level medium
                    printMainMenu(2);
                    selectedLevel = 2;
                    break;
                case 2: // Level hard
                    printMainMenu(3);
                    selectedLevel = 3;
                    break;
                case 3: // Level insane
                    selectedLevel = 3;
                    break;
                default: // Error
                    printError("Error selecting level! Press ENTER to try again!");
                    clearScreen();
                    printMainMenu(selectedLevel);
                    break;
            }
        } else if (charKey == W_KEY) {
            switch (selectedLevel) {
                case 0: // Level easy
                    selectedLevel = 0;
                    break;
                case 1: // Level medium
                    printMainMenu(0);
                    selectedLevel = 0;
                    break;
                case 2: // Level hard
                    printMainMenu(1);
                    selectedLevel = 1;
                    break;
                case 3: // Level insane
                    printMainMenu(2);
                    selectedLevel = 2;
                    break;
                default: // Error
                    printError("Error selecting level! Press ENTER to try again!");
                    clearScreen();
                    printMainMenu(selectedLevel);
                    break;
            }
        } else if (charKey == S_KEY) {
            switch (selectedLevel) {
               case 0: // Level easy
                    printMainMenu(1);
                    selectedLevel = 1;
                    break;
                case 1: // Level medium
                    printMainMenu(2);
                    selectedLevel = 2;
                    break;
                case 2: // Level hard
                    printMainMenu(3);
                    selectedLevel = 3;
                    break;
                case 3: // Level insane
                    selectedLevel = 3;
                    break;
                default: // Error
                    printError("Error selecting level! Press ENTER to try again!");
                    printMainMenu(selectedLevel);
                    break;
            }
        } else {
            /*printError("Error selecting level! Press ENTER to try again!");
            clearScreen();
            printMainMenu(selectedLevel);*/
            // On the other hand, if wrong input is detected, just ignore it...
        }
    } while (charKey != RETURN_KEY);

    return selectedLevel;
}

void executeGame() {
    while (runGame) {

    }
}
