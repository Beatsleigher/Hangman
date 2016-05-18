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
#define PG_UP 73//22473
#define PG_DWN 81//22481
#define E_KEY 101
#define M_KEY 109
#define H_KEY 104
#define I_KEY 105
#define RETURN_KEY 0x0D

#define LEVEL_EASY

// Project includes
#include "game.h"
#include "ui.h"
#include "words.h"
#include "systemio.h"

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

    // Read character. Wait for arrow keys and return.
    do {
        charKey = _getch();
//        printf("%i", charKey);
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
        } else if (charKey == PG_UP) {
            switch (selectedLevel) {
               case 0: // Level easy
                    selectedLevel = 0;
                    break;
                case 1: // Level medium
                    printMainMenu(0);
                    selectedLevel = 0;
                    break;
                case 2: // Level hard
                    printMainMenu(0);
                    selectedLevel = 0;
                    break;
                case 3: // Level insane
                    printMainMenu(0);
                    selectedLevel = 0;
                    break;
                default: // Error
                    printError("Error selecting level! Press ENTER to try again!");
                    printMainMenu(selectedLevel);
                    break;
            }
        } else if (charKey == PG_DWN) {
            switch (selectedLevel) {
               case 0: // Level easy
                    printMainMenu(3);
                    selectedLevel = 3;
                    break;
                case 1: // Level medium
                    printMainMenu(3);
                    selectedLevel = 3;
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
        } else if (charKey == E_KEY) {
            printMainMenu(0);
            selectedLevel = 0;
        } else if (charKey == M_KEY) {
            printMainMenu(1);
            selectedLevel = 1;
        } else if (charKey == H_KEY) {
            printMainMenu(2);
            selectedLevel = 2;
        } else if (charKey == I_KEY) {
            printMainMenu(3);
            selectedLevel = 3;
        } else {
            /*printError("Error selecting level! Press ENTER to try again!");
            clearScreen();
            printMainMenu(selectedLevel);*/
            // On the other hand, if wrong input is detected, just ignore it...
        }
    } while (charKey != RETURN_KEY);

    return selectedLevel;
}

void executeGame(struct WordCategories words) {
    runGame = true;
    char errorLines[5][60];

    /**
        Jump in to the game loop.
        This is where most of the magic happens.
        This loop will be continued until the user wants to quit the game.
     */
    while (runGame) {

        // Show loading screen and load stuff for the game..
        showLoadingScreen();

        switch (selectedLevel) {
            case 0:
                printStatusBarMsg("Selected level \"Easy\"");
                Sleep(750);
                break;
            case 1:
                printStatusBarMsg("Selected level \"Medium\"");
                Sleep(750);
                break;
            case 2:
                printStatusBarMsg("Selected level \"Hard\"");
                Sleep(750);
                break;
            case 3:
                printStatusBarMsg("Selected level \"Insane\". I like you!");
                Sleep(750);
                break;
        }

        // Show status at the bottom of the screen.
        printStatusBarMsg("Seeding random number...");

        // Plant seed
        srand(468164894);

        // Randomly choose a word, depending on the level selected.
        printStatusBarMsg("Randomly choosing a word...");
        Sleep(500);
        char *randomWord;
        int randomIndex = rand() % 20;
        switch (selectedLevel) {
            case 0: // Level easy
                //strcpy(randomWord, words.easyWords[randomIndex]);
                printStatusBarMsg("A word has been selected!");
                Sleep(1000);
                printStatusBarMsg("Good luck!");
                break;
            case 1: // Level medium
                //strcpy(randomWord, words.mediumWords[rand() % 1200]);
                printStatusBarMsg("A word has been selected!");
                Sleep(1000);
                printStatusBarMsg("Good luck!");
                break;
            case 2: // level hard
                //strcpy(randomWord, words.hardWords[rand() % 1200]);
                printStatusBarMsg("A word has been selected!");
                Sleep(1000);
                printStatusBarMsg("Good luck!");
                break;
            case 3: // Level insane.
                //strcpy(randomWord, words.insaneWords[rand() % 1200]);
                printStatusBarMsg("A word has been selected!");
                Sleep(1000);
                printStatusBarMsg("Prepare to be defeated!");
                break;
            default:
                strcpy(errorLines[0], "An error has occurred.");
                strcpy(errorLines[1], "Could not locate the selected level!");
                strcpy(errorLines[2], "Will exit to main menu!");
                //printMultilineError(errorLines, 3);
        }

        printBottomCentre(randomWord);
        runGame = false;

    }
}
