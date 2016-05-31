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

//    showGameOver();
//    return 0;

    // Set window size
    setConsoleSize(160, 40);

    char *by = "By Simon C., Patrick M.";
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
//    printMessage("Test Message", "This is a test");
//    printMessage("Descriptive Message", "You can print up to sixty (60) characters in such a message!"); // I SWEAR THIS IS A COINCIDENCE!
//    char messageLines[5][60];
//    sprintf(messageLines[0], "Even messages with multiple lines are supported!");
//    sprintf(messageLines[1], "You can add up to 5 lines, each with up to 60 characters!"); // This one is pure coincidence! Really!
//    sprintf(messageLines[2], "By using sprintf(), you can even format the text!");
//    sprintf(messageLines[3], "Th%i %i %i f%irm%itt%id %ixt", 15, 15, 4, 0, 4, 3, 73);
//    sprintf(messageLines[4], "The possibilities are endless!");
//    printMultilineMsg("Descriptive Message", messageLines, 5);
//    return 0;



    /** BEGIN: TEST CODE */
    ///printHelp(TOPIC_GENERAL);
    ///getchar();
    ///return 0;

///    printf("%d", 81 % 54);
///    return 0;

    /** END: TEST CODE */

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
        if (/*wordCategories.easyWords[i] == NULL || */wordCategories.easyWords[i] == "" || sizeof(wordCategories.easyWords[i]) < 1) {
            errorCount++;
        }
        //Sleep(1000);
    }

    for (int i = 0; i < sizeof(wordCategories.mediumWords) / sizeof(wordCategories.mediumWords[0]); i++) {
        if (/*wordCategories.mediumWords[i] == NULL || */wordCategories.mediumWords[i] == "" || sizeof(wordCategories.mediumWords[i]) < 1) {
            errorCount++;
        }
        //Sleep(1000);
    }

    for (int i = 0; i < sizeof(wordCategories.hardWords) / sizeof(wordCategories.hardWords[0]); i++) {
        if (/*wordCategories.easyWords[i] == NULL || */wordCategories.easyWords[i] == "" || sizeof(wordCategories.easyWords[i]) < 1) {
            errorCount++;
        }
        //Sleep(1000);
    }

    for (int i = 0; i < sizeof(wordCategories.easyWords) / sizeof(wordCategories.easyWords[0]); i++) {
        if (/*wordCategories.easyWords[i] == NULL || */wordCategories.easyWords[i] == "" || sizeof(wordCategories.easyWords[i]) < 1) {
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
    ///printWelcomeScreen();

    // Wait for user input, then open menu
    ///printCentre("Hit [ ENTER ] to continue!", (getConsoleHeight() / 2) + 5);
    ///getchar();


    // Clear screen and send user to main menu
//    clearScreen();
//    showGameMenu();
//
//    executeGame(wordCategories);

    // When game exits, go to main menu.
    // Don't show complete intro again.
    // Make it look like a real game.
    int result = -5; // Some random value
    while ((result = showGameMenu()) != QUIT_GAME) {
        if (result == SHOW_HELP) {
            clearScreen();
            int charKey = 0;
            int selectedTopic = TOPIC_GENERAL;

            printHelp(selectedTopic, false);

            do {
                charKey = getch();

                if (charKey == UP_ARROW) {
                    switch (selectedTopic) {
                        case TOPIC_GENERAL:
                            // Do nothing
                            break;
                        case TOPIC_LEVEL_SELECTION:
                            printHelpMenu((selectedTopic = TOPIC_GENERAL));
                            break;
                        case TOPIC_GAMEPLAY:
                            printHelpMenu((selectedTopic = TOPIC_LEVEL_SELECTION));
                            break;
                        case TOPIC_LEVEL_EASY:
                            printHelpMenu((selectedTopic = TOPIC_GAMEPLAY));
                            break;
                        case TOPIC_LEVEL_MEDIUM:
                            printHelpMenu((selectedTopic = TOPIC_LEVEL_EASY));
                            break;
                        case TOPIC_LEVEL_HARD:
                            printHelpMenu((selectedTopic = TOPIC_LEVEL_MEDIUM));
                            break;
                        case TOPIC_LEVEL_INSANE:
                            printHelpMenu((selectedTopic = TOPIC_LEVEL_HARD));
                            break;
                        default:

                            break;
                    }
                } else if (charKey == DOWN_ARROW) {
                    switch (selectedTopic) {
                        case TOPIC_GENERAL:
                            printHelpMenu((selectedTopic = TOPIC_LEVEL_SELECTION));
                            break;
                        case TOPIC_LEVEL_SELECTION:
                            printHelpMenu((selectedTopic = TOPIC_GAMEPLAY));
                            break;
                        case TOPIC_GAMEPLAY:
                            printHelpMenu((selectedTopic = TOPIC_LEVEL_EASY));
                            break;
                        case TOPIC_LEVEL_EASY:
                            printHelpMenu((selectedTopic = TOPIC_LEVEL_MEDIUM));
                            break;
                        case TOPIC_LEVEL_MEDIUM:
                            printHelpMenu((selectedTopic = TOPIC_LEVEL_HARD));
                            break;
                        case TOPIC_LEVEL_HARD:
                            printHelpMenu((selectedTopic = TOPIC_LEVEL_INSANE));
                            break;
                        case TOPIC_LEVEL_INSANE:
                            // Do nothing
                            break;
                        default:

                            break;
                    }
                } else if (charKey == RETURN_KEY) {
                    printHelpText(selectedTopic);
                } else {
                    // Nothing to do, really...
                }

            } while (charKey != ESC_KEY);
            continue;
        } else {
            executeGame(wordCategories);
        }
    }

    // Print farewell, exit program.
    printGoodBye();

    // Restore saved console attrs. Saves us from getting warnings
    SetConsoleTextAttribute(hConsole, saved_attributes);

    return 0;
}
