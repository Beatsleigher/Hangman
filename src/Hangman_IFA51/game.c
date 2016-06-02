// Written by Simon Cahill
// Copyright (c) 2016
// All Right Reserved
// Copies and modifications of this file are prohibited and punishable by law,
// unless done with EXPRESS PERMISSION by the author of this file.

// #DEFINES => Header

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
#include <time.h>
#include <string.h>

int showGameMenu() {
    clearScreen();
    printMainMenu(LEVEL_EASY);
    int charKey;
    selectedLevel = LEVEL_EASY;

    // Test code
//    printMessage("test", "This is a test!");
//    Sleep(2000);
//    printError("This is an error!");
//    clearScreen();
//    printMainMenu(LEVEL_EASY);

    // Read character. Wait for arrow keys and return.
    do {
        charKey = _getch();
//        printf("%i", charKey);
        if (charKey == UP_ARROW) {
            switch (selectedLevel) {
                case 0: // Level easy
                    selectedLevel = LEVEL_EASY;
                    break;
                case 1: // Level medium
                    printMainMenu(LEVEL_EASY);
                    selectedLevel = LEVEL_EASY;
                    break;
                case 2: // Level hard
                    printMainMenu(LEVEL_MEDIUM);
                    selectedLevel = LEVEL_MEDIUM;
                    break;
                case 3: // Level insane
                    printMainMenu(LEVEL_HARD);
                    selectedLevel = LEVEL_HARD;
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
                    printMainMenu(LEVEL_MEDIUM);
                    selectedLevel = LEVEL_MEDIUM;
                    break;
                case 1: // Level medium
                    printMainMenu(LEVEL_HARD);
                    selectedLevel = LEVEL_HARD;
                    break;
                case 2: // Level hard
                    printMainMenu(LEVEL_INSANE);
                    selectedLevel = LEVEL_INSANE;
                    break;
                case 3: // Level insane
                    selectedLevel = LEVEL_INSANE;
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
                    selectedLevel = LEVEL_EASY;
                    break;
                case 1: // Level medium
                    printMainMenu(LEVEL_EASY);
                    selectedLevel = LEVEL_EASY;
                    break;
                case 2: // Level hard
                    printMainMenu(LEVEL_MEDIUM);
                    selectedLevel = LEVEL_MEDIUM;
                    break;
                case 3: // Level insane
                    printMainMenu(LEVEL_HARD);
                    selectedLevel = LEVEL_HARD;
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
                    printMainMenu(LEVEL_MEDIUM);
                    selectedLevel = LEVEL_MEDIUM;
                    break;
                case 1: // Level medium
                    printMainMenu(LEVEL_HARD);
                    selectedLevel = LEVEL_HARD;
                    break;
                case 2: // Level hard
                    printMainMenu(LEVEL_INSANE);
                    selectedLevel = LEVEL_INSANE;
                    break;
                case 3: // Level insane
                    selectedLevel = LEVEL_INSANE;
                    break;
                default: // Error
                    printError("Error selecting level! Press ENTER to try again!");
                    printMainMenu(selectedLevel);
                    break;
            }
        } else if (charKey == PG_UP) {
            switch (selectedLevel) {
               case 0: // Level easy
                    selectedLevel = LEVEL_EASY;
                    break;
                case 1: // Level medium
                    printMainMenu(LEVEL_EASY);
                    selectedLevel = LEVEL_EASY;
                    break;
                case 2: // Level hard
                    printMainMenu(LEVEL_EASY);
                    selectedLevel = LEVEL_EASY;
                    break;
                case 3: // Level insane
                    printMainMenu(LEVEL_EASY);
                    selectedLevel = LEVEL_EASY;
                    break;
                default: // Error
                    printError("Error selecting level! Press ENTER to try again!");
                    printMainMenu(selectedLevel);
                    break;
            }
        } else if (charKey == PG_DWN) {
            switch (selectedLevel) {
               case 0: // Level easy
                    printMainMenu(LEVEL_INSANE);
                    selectedLevel = LEVEL_INSANE;
                    break;
                case 1: // Level medium
                    printMainMenu(LEVEL_INSANE);
                    selectedLevel = LEVEL_INSANE;
                    break;
                case 2: // Level hard
                    printMainMenu(LEVEL_INSANE);
                    selectedLevel = LEVEL_INSANE;
                    break;
                case 3: // Level insane
                    selectedLevel = LEVEL_INSANE;
                    break;
                default: // Error
                    printError("Error selecting level! Press ENTER to try again!");
                    printMainMenu(selectedLevel);
                    break;
            }
        } else if (charKey == E_KEY) {
            printMainMenu(LEVEL_EASY);
            selectedLevel = LEVEL_EASY;
        } else if (charKey == M_KEY) {
            printMainMenu(LEVEL_MEDIUM);
            selectedLevel = LEVEL_MEDIUM;
        } else if (charKey == H_KEY) {
            printMainMenu(LEVEL_HARD);
            selectedLevel = LEVEL_HARD;
        } else if (charKey == I_KEY) {
            printMainMenu(LEVEL_INSANE);
            selectedLevel = LEVEL_INSANE;
        } else if (charKey == ESC_KEY) {
            return QUIT_GAME;
        } else if (charKey == QUESTION_MARK_KEY) {
            return SHOW_HELP;
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
    char errorLines[5][60];// Show loading screen and load stuff for the game..
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
    srand(time(NULL));

    // Randomly choose a word, depending on the level selected.
    printStatusBarMsg("Randomly choosing a word...");
    Sleep(500);
    char randomWord[150];
    int randomIndex = rand() % 20;


//    printf("%d", randomIndex);
//    getchar();


    switch (selectedLevel) {
        case 0: // Level easy
            strcpy(randomWord, trim(toLower(words.easyWords[randomIndex])));
            //char *word = words.easyWords[randomIndex];
            //setCursorPosition(getConsoleLen() / 2 - strlen(word) / 2, getConsoleHeight() - 2);
            //printf("%i", randomIndex);
            printStatusBarMsg("A word has been selected!");
            Sleep(1000);
            printStatusBarMsg("Good luck!");
            break;
        case 1: // Level medium
            strcpy(randomWord, trim(toLower(words.mediumWords[randomIndex])));
            printStatusBarMsg("A word has been selected!");
            Sleep(1000);
            printStatusBarMsg("Good luck!");
            break;
        case 2: // level hard
            strcpy(randomWord, trim(toLower(words.hardWords[randomIndex])));
            printStatusBarMsg("A word has been selected!");
            Sleep(1000);
            printStatusBarMsg("Good luck!");
            break;
        case 3: // Level insane.
            strcpy(randomWord, trim(toLower(words.insaneWords[randomIndex])));
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

//    printCentre(randomWord, getConsoleHeight() - 3);
//    getchar();

    // Stuff for in-game display
    char errors[7][1];
    int amountOfErrors = 0;
    int typedChar = '\0';

    /** TODO: REMOVE THIS FROM CODE! **/
    //strcpy(randomWord, "testen");

    char correctLetters[strlen(randomWord)][1];
    int indexOfCorrectLetters = 0;


    /**
        Jump in to the game loop.
        This is where most of the magic happens.
        This loop will be continued until the user wants to quit the game.
     */


    printGameUI(selectedLevel, randomWord, amountOfErrors, typedChar, errors);

    /// Print stats
    printGameStats(amountOfErrors, errors);

    /// Print word placeholder
    printGameWordPlaceholder(randomWord);

    /// Show and start timer
    HANDLE timerHandle = CreateThread(NULL, 0, showTimeRemaining, selectedLevel, 0, NULL);

    while (runGame) {

        // Check if player won or lost before the game starts/continues
        if (amountOfErrors == 7) {
            runGame = false;
            // Player has lost.
            Sleep(2000);
            showGameOver();
            printCentre("Press [ ENTER ] to Continue", 2);
            getchar();
            break;
        }

        if (indexOfCorrectLetters == strlen(randomWord)) {
            runGame = false;
            // You have probably won?
            Sleep(500);
            printGameWonScreen();
            break;
        }

        char *foundChar;

        typedChar = getch();

//        char typedCharOutput[100];
//        sprintf(typedCharOutput, "Keycode: %d, Character: %c", typedChar, typedChar);
//        printBottomCentre(typedCharOutput);
//        continue;

        // Catch keys before parsing.
        // If key is invalid, continue loop
        switch (typedChar) {
            case 82: // INSERT
                continue;
            case 83: // DELETE
                continue;
            case 71: // POS 1
                continue;
            case 79: // END
                continue;
            case 73: // PG UP
                continue;
            case 81: // PG DOWN
                continue;
            case 47: // NUMPAD SLASH
                continue;
            case 42: // NUMPAD ASTERISK
                continue;
            case 45: // NUMPAD HYPHEN
                continue;
            case 43: // NUMPAD PLUS
                continue;
            case 13: // NUMPAD RETURN
                continue;
            case 273: // ESC
                runGame = false;
                continue;
            case 323: // SPACEBAR
                continue;
            case 72: // ARROW UP
                continue;
            case 75: // ARROW LEFT
                continue;
            case 80: // ARROW DOWN
                continue;
            case 77: // ARROW RIGHT
                continue;
            case 65: // F7
                continue;
            case 66: // F8
                continue;
            case 67: // F9
                continue;
            case 68: // F10
                continue;
            /** There is no need for a default case here. */
        }

        /**
            Check for valid input.
            If input is invalid (i.e.: not an alphabetical character),
            then skip the rest of the loop and start again.
         */
        if (!((typedChar >= 65 && typedChar <= 90) || (typedChar >= 97 && typedChar <= 122))) {
            continue;
        }

        foundChar = strchr(randomWord, typedChar);

        if (selectedLevel == LEVEL_INSANE) {

            if (foundChar != 0) {
                short xCoord = 0,
                      charPosition = (foundChar - randomWord) + 1;

//                char msg[50];
//                sprintf(msg, "Entered char: %c, Char index (word): %d, Char in word: %c, Correct chars: %d", typedChar, charPosition, randomWord[indexOfCorrectLetters], indexOfCorrectLetters);
//                printBottomCentre(msg);
//
//                Sleep(500);

                if (typedChar == randomWord[indexOfCorrectLetters]) {
//                    printBottomCentre("Entered correct letter!");

                    if (charPosition == 1) {
                        xCoord = (getConsoleLen() / 2 - strlen(randomWord)) + (foundChar - randomWord + 1);
                    } else if (charPosition == strlen(randomWord)) {
                        xCoord = (getConsoleLen() / 2 + strlen(randomWord) - 1);
                    } else {
                        xCoord = (getConsoleLen() / 2 - strlen(randomWord)) + ((foundChar - randomWord) * 2) + 1;
                    }

                    strcpy(correctLetters[indexOfCorrectLetters], foundChar);
                    indexOfCorrectLetters++;
                    setCursorPosition(xCoord, getConsoleHeight() - 2);
                    printf("%c", typedChar);
                    foundChar = strchr(foundChar + 1, typedChar);

//                    indexOfCorrectLetters++;
                } else {
//                    printBottomCentre("Entered INCORRECT letter!");
                    char err[10];
                    sprintf(err, "%c", typedChar);
                    strcpy(errors[amountOfErrors], err);
                    amountOfErrors++;
                    printGameStats(amountOfErrors, errors);
                    printHangman(amountOfErrors);
                }


            } else {
                char err[10];
                sprintf(err, "%c", typedChar);
                strcpy(errors[amountOfErrors], err);
                amountOfErrors++;
                printGameStats(amountOfErrors, errors);
                printHangman(amountOfErrors);
            }

            // Skip the rest of the loop
            continue;
        }

        if (foundChar != 0) {
            for (int i = 0; i < strlen(randomWord); i++) {
                if (foundChar == correctLetters[i]) {
                    continue;
                }
            }

            while (foundChar != 0) {
                short xCoord = 0;
                short charPosition = (foundChar - randomWord + 1);

                if (charPosition == 1) {
                    xCoord = (getConsoleLen() / 2 - strlen(randomWord)) + (foundChar - randomWord + 1);
                } else if (charPosition == strlen(randomWord)) {
                    xCoord = (getConsoleLen() / 2 + strlen(randomWord) - 1);
                } else {
                    xCoord = (getConsoleLen() / 2 - strlen(randomWord)) + ((foundChar - randomWord) * 2) + 1;
                }

                strcpy(correctLetters[indexOfCorrectLetters], foundChar);
                indexOfCorrectLetters++;
                setCursorPosition(xCoord, getConsoleHeight() - 2);
                printf("%c", typedChar);
                foundChar = strchr(foundChar + 1, typedChar);
            }
        } else {
            char err[10];
            sprintf(err, "%c", typedChar);
            strcpy(errors[amountOfErrors], err);
            amountOfErrors++;
            printGameStats(amountOfErrors, errors);
            printHangman(amountOfErrors);
        }

    }

}

bool isAnagram(const char *str1, const char *str2) {

    /*
     * Code from www.programmingsimplified.com/c/source-code/c-anagram-program.
     * Modified due to lacking readability...
     */

    int first[26] = { 0 },
        second[26] = { 0 },
        index = 0;

    while (str1[index] != '\0') {
        first[str1[index] - 'a']++;
        index++;
    }

    index = 0;

    while (str2[index] != '\0') {
        second[str2[index] - 'a']++;
        index++;
    }

    for (index = 0; index < 26; index++) {
        if (first[index] != second[index]) {
            return false;
        }
    }

    return true;
}

char* toLower(char *str) {
    for (int i = 0; i < strlen(str); i++) {
        char currentChar = str[i];
        currentChar = tolower(currentChar);
        str[i] = currentChar;
    }
    return str;
}

char* trim(char *str) {
    char *end;

  // Trim leading space
  while(isspace(*str)) {
    str++;
  }

  if(*str == 0) {  // All spaces?
    return str;
  }

  // Trim trailing space
  end = str + strlen(str) - 1;
  while(end > str && isspace(*end)) {
        end--;
  }

  // Write new null terminator
  *(end + 1) = 0;

  return str;

}

DWORD WINAPI showTimeRemaining(LPVOID data) {

    // Time remaining in seconds
    int timeRemaining = 0,
        timePlayed = 0,
        timeRemainingInMins = 0,
        timePlayedInMins = 0;

    switch (selectedLevel) {
        case LEVEL_EASY:
            timeRemaining = -1;
            break;
        case LEVEL_MEDIUM:

            timeRemaining = 120;
            break;
        case LEVEL_HARD:
            timeRemaining = 60;
            break;
        case LEVEL_INSANE:
            timeRemaining = 30;
            break;
        default:;
            // Stop game, return to game menu.
            char msg[2];
            strcpy(msg[0], "An error has occurred while loading the game!");
            strcpy(msg[1], "You will be returned to the main menu!");


            printMultilineMsg("ERROR LOADING GAME!", msg, 2);

            runGame = false;
    }

    if (!selectedLevel == LEVEL_EASY) {
        while (runGame && timeRemaining != 0) {
            timeRemaining--;
            char time[5];
            sprintf(time, "%02d:%02d", (timeRemaining / 60), (timeRemaining % 60));
            setCursorPosition(getConsoleLen() - 8, 2);
            printf(time);
            Sleep(1000);
        }

        if (timeRemaining == 0) {
            // TIME'S UP!
            runGame = false;
            showGameOver();
            printCentre("Press [ ENTER ] to Continue", 2);
            getchar();
        }
    } else {
        while (runGame) {
            timeRemaining++;
            char time[5];
            sprintf(time, "%02d:%02d", (timeRemaining / 60), (timeRemaining % 60));
            setCursorPosition(getConsoleLen() - 8, 2);
            printf(time);
            Sleep(1000);
        }
    }


    return 0;
}

// EOF
