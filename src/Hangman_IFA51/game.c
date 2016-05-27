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
        printf("%i", charKey);
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
    switch (selectedLevel) {
        case 0: // Level easy
            strcpy(randomWord, trim(toLower(words.easyWords[randomIndex])));
            char *word = words.easyWords[randomIndex];
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

    printCentre(randomWord, getConsoleHeight() - 3);
    getchar();

    // Stuff for in-game display
    char errors[7][1];
    int amountOfErrors = 0;
    char typedChar = "\0";

    /** TODO: REMOVE THIS FROM CODE! **/
    //strcpy(randomWord, "testen");

    char correctLetters[sizeof(randomWord)][1];
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

    while (runGame) {

        // Check if player won or lost before the game starts/continues
        if (amountOfErrors == 7) {
            // Player has lost.
            Sleep(2000);
            showGameOver();
            printCentre("Press [ ENTER ] to Continue", 2);
            getchar();
            runGame = false;
            break;
        }

        if (indexOfCorrectLetters == strlen(randomWord)) {
            // You have probably won?
            Sleep(500);
            printGameWonScreen();
            runGame = false;
            break;
        }

        char *foundChar;

        typedChar = getch();

        /**
            Check for valid input.
            If input is invalid (i.e.: not an alphabetical character),
            then skip the rest of the loop and start again.
         */
        if (!((typedChar >= 65 && typedChar <= 90) || (typedChar >= 97 && typedChar <= 122))) {
            continue;
        }

        foundChar = strchr(randomWord, typedChar);

        if (foundChar != 0) {
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

                //strcat(correctLetters[charPosition], foundChar);
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

// EOF
