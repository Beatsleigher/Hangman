// Written by Simon Cahill
// Copyright (c) 2016
// All Right Reserved
// Copies and modifications of this file are prohibited and punishable by law,
// unless done with EXPRESS PERMISSION by the author of this file.

// Project includes
#include "ui.h"
#include "systemio.h"
#include "words.h"

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
#include <conio.h>

int getConsoleLen() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    return columns;
}

int getConsoleHeight() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int rows;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    return rows;
}

COORD getCoord(short x, short y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    return coord;
}

void setCursorPosition(short x, short y) {
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), getCoord(x, y));
}

void printCentre(char *str, short yCoord) {
    setCursorPosition(((short)getConsoleLen() / 2 - strlen(str) / 2), yCoord);
    printf(str);
}

void printRight(char *str, short yCoord) {
    setCursorPosition(getConsoleLen() - strlen(str), yCoord);
    printf(str);
}

void printXYCentre(char *str) {
    int x = getConsoleLen() / 2 - strlen(str) / 2;
    int y = (getConsoleHeight() / 2) - 1;
    setCursorPosition(x, y);
    printf(str);
}

void printTopCentre(char *str) {
    int x = getConsoleLen() / 2 - strlen(str) / 2;
    int y = getConsoleHeight() - getConsoleHeight() + 1;
    setCursorPosition(x, y);
    printf(str);
}

void printBottomCentre(char *str) {
    int x = getConsoleLen() / 2 - strlen(str) / 2;
    int y = getConsoleHeight() - 1;
    setCursorPosition(x, y);
    printf(str);
    setCursorPosition(0, getConsoleHeight() - 2);
}

void printProgressBar(int percent, int startFrom) {
    percent = getConsoleLen() / 100 * percent;
    for (int i = startFrom; i < percent + 1; i++) {
            Sleep(50);
        setCursorPosition(i, getConsoleHeight() - getConsoleHeight());
        printf("\u00b2"); // TODO: Figure out how to print dark shade...
    }
}

void clearScreen() {
    for (int i = 0; i != getConsoleHeight(); i++) {
        for (int j = 0; j != getConsoleLen(); j++) {
            setCursorPosition((short)j, (short)i);
            printf(" ");
        }
    }
}

void clearLine(short row) {
    for (int i = 0; i != getConsoleLen(); i++) {
        setCursorPosition(i, row);
        printf(" ");
    }
}

void clearColumn(short col) {
    for (int i = 0; i != getConsoleHeight(); i++) {
        setCursorPosition(col, i);
        printf(" ");
    }
}

void clearTopLine() {
    clearLine(getConsoleHeight() - getConsoleHeight());
}

void clearBottomLine() {
    clearLine(getConsoleHeight() - 1);
    setCursorPosition(0, getConsoleHeight() - 2);
}

void cinematicClear() {
    for (int i = 0; i != getConsoleHeight(); i++) {
        for (int j = 0; j != getConsoleLen(); j++) {
            setCursorPosition((short)j, (short)i);
            printf(" ");
            Sleep(5);
        }
        //Sleep(250);
    }
}

void printWelcomeScreen() {


    char l1[93] = "M\"\"MMM\"\"MMM\"\"M MM\"\"\"\"\"\"\"\"`M M\"\"MMMMMMMM MM'\"\"\"\"'YMM MMP\"\"\"\"\"YMM M\"\"\"\"\"`'\"\"\"`YM MM\"\"\"\"\"\"\"\"`M ",
         l2[93] = "M  MMM  MMM  M MM  mmmmmmmM M  MMMMMMMM M' .mmm. `M M' .mmm. `M M  mm.  mm.  M MM  mmmmmmmM ",
         l3[93] = "M  MMP  MMP  M M`      MMMM M  MMMMMMMM M  MMMMMooM M  MMMMM  M M  MMM  MMM  M M`      MMMM ",
         l4[93] = "M  MM'  MM' .M MM  MMMMMMMM M  MMMMMMMM M  MMMMMMMM M  MMMMM  M M  MMM  MMM  M MM  MMMMMMMM ",
         l5[93] = "M  `' . '' .MM MM  MMMMMMMM M  MMMMMMMM M. `MMM' .M M. `MMM' .M M  MMM  MMM  M MM  MMMMMMMM ",
         l6[93] = "M    .d  .dMMM MM        .M M         M MM.     .dM MMb     dMM M  MMM  MMM  M MM        .M ",
         l7[93] = "MMMMMMMMMMMMMM MMMMMMMMMMMM MMMMMMMMMMM MMMMMMMMMMM MMMMMMMMMMM MMMMMMMMMMMMMM MMMMMMMMMMMM ",

          l8[24] = "M\"\"\"\"\"\"\"\"M MMP\"\"\"\"\"YMM ",
          l9[24] = "Mmmm  mmmM M' .mmm. `M ",
         l10[24] = "MMMM  MMMM M  MMMMM  M ",
         l11[24] = "MMMM  MMMM M  MMMMM  M ",
         l12[24] = "MMMM  MMMM M. `MMM' .M ",
         l13[24] = "MMMM  MMMM MMb     dMM ",
         l14[24] = "MMMMMMMMMM MMMMMMMMMMM ",

         l15[91] = "M\"\"MMMMM\"\"MM MMP\"\"\"\"\"\"\"MM M\"\"\"\"\"\"\"`YM MM'\"\"\"\"\"`MM M\"\"\"\"\"`'\"\"\"`YM MMP\"\"\"\"\"\"\"MM M\"\"\"\"\"\"\"`YM ",
         l16[91] = "M  MMMMM  MM M' .mmmm  MM M  mmmm.  M M' .mmm. `M M  mm.  mm.  M M' .mmmm  MM M  mmmm.  M ",
         l17[91] = "M         `M M         `M M  MMMMM  M M  MMMMMMMM M  MMM  MMM  M M         `M M  MMMMM  M ",
         l18[91] = "M  MMMMM  MM M  MMMMM  MM M  MMMMM  M M  MMM   `M M  MMM  MMM  M M  MMMMM  MM M  MMMMM  M ",
         l19[91] = "M  MMMMM  MM M  MMMMM  MM M  MMMMM  M M. `MMM' .M M  MMM  MMM  M M  MMMMM  MM M  MMMMM  M ",
         l20[91] = "M  MMMMM  MM M  MMMMM  MM M  MMMMM  M MM.     .MM M  MMM  MMM  M M  MMMMM  MM M  MMMMM  M ",
         l21[91] = "MMMMMMMMMMMM MMMMMMMMMMMM MMMMMMMMMMM MMMMMMMMMMM MMMMMMMMMMMMMM MMMMMMMMMMMM MMMMMMMMMMM ";

    short centre = (getConsoleHeight() / 2) - 1;
    int sleepLen = 5;

    // Print WELCOME
    setCursorPosition(getConsoleLen() / 2 - 93 / 2, centre);
    for (int i = 0; i < 93; i++) {
        printf("%c", l4[i]);
        Sleep(sleepLen);
    }
    setCursorPosition(getConsoleLen() / 2 - 93 / 2, centre - 1);
    for (int i = 0; i < 93; i++) {
        printf("%c", l3[i]);
        Sleep(sleepLen);
    }
    setCursorPosition(getConsoleLen() / 2 - 93 / 2, centre + 1);
    for (int i = 0; i < 93; i++) {
        printf("%c", l5[i]);
        Sleep(sleepLen);
    }
    setCursorPosition(getConsoleLen() / 2 - 93 / 2, centre - 2);
    for (int i = 0; i < 93; i++) {
        printf("%c", l2[i]);
        Sleep(sleepLen);
    }
    setCursorPosition(getConsoleLen() / 2 - 93 / 2, centre + 2);
    for (int i = 0; i < 93; i++) {
        printf("%c", l6[i]);
        Sleep(sleepLen);
    }
    setCursorPosition(getConsoleLen() / 2 - 93 / 2, centre - 3);
    for (int i = 0; i < 93; i++) {
        printf("%c", l1[i]);
        Sleep(sleepLen);
    }
    setCursorPosition(getConsoleLen() / 2 - 93 / 2, centre + 3);
    for (int i = 0; i < 93; i++) {
        printf("%c", l7[i]);
        Sleep(sleepLen);
    }

    // Wait half a sec, then clear WELCOME line by line
    Sleep(500);
    clearScreen();

    // Print TO
    setCursorPosition(getConsoleLen() / 2 - 24 / 2, centre);
    for (int i = 0; i < 24; i++) {
        printf("%c", l11[i]);
        Sleep(sleepLen);
    }
    setCursorPosition(getConsoleLen() / 2 - 24 / 2, centre - 1);
    for (int i = 0; i < 24; i++) {
        printf("%c", l10[i]);
        Sleep(sleepLen);
    }
    setCursorPosition(getConsoleLen() / 2 - 24 / 2, centre + 1);
    for (int i = 0; i < 24; i++) {
        printf("%c", l12[i]);
        Sleep(sleepLen);
    }
    setCursorPosition(getConsoleLen() / 2 - 24 / 2, centre - 2);
    for (int i = 0; i < 24; i++) {
        printf("%c", l9[i]);
        Sleep(sleepLen);
    }
    setCursorPosition(getConsoleLen() / 2 - 24 / 2, centre + 2);
    for (int i = 0; i < 24; i++) {
        printf("%c", l13[i]);
        Sleep(sleepLen);
    }
    setCursorPosition(getConsoleLen() / 2 - 24 / 2, centre - 3);
    for (int i = 0; i < 24; i++) {
        printf("%c", l8[i]);
        Sleep(sleepLen);
    }
    setCursorPosition(getConsoleLen() / 2 - 24 / 2, centre + 3);
    for (int i = 0; i < 24; i++) {
        printf("%c", l14[i]);
        Sleep(sleepLen);
    }

    // Wait half a sec, then clear TO line by line
    Sleep(500);
    clearScreen();

    // Print HANGMAN
    setCursorPosition(getConsoleLen() / 2 - 91 / 2, centre);
    for (int i = 0; i < 91; i++) {
        printf("%c", l18[i]);
        Sleep(sleepLen);
    }
    setCursorPosition(getConsoleLen() / 2 - 91 / 2, centre - 1);
    for (int i = 0; i < 91; i++) {
        printf("%c", l17[i]);
        Sleep(sleepLen);
    }
    setCursorPosition(getConsoleLen() / 2 - 91 / 2, centre + 1);
    for (int i = 0; i < 91; i++) {
        printf("%c", l19[i]);
        Sleep(sleepLen);
    }
    setCursorPosition(getConsoleLen() / 2 - 91 / 2, centre - 2);
    for (int i = 0; i < 91; i++) {
        printf("%c", l16[i]);
        Sleep(sleepLen);
    }
    setCursorPosition(getConsoleLen() / 2 - 91 / 2, centre + 2);
    for (int i = 0; i < 91; i++) {
        printf("%c", l20[i]);
        Sleep(sleepLen);
    }
    setCursorPosition(getConsoleLen() / 2 - 91 / 2, centre - 3);
    for (int i = 0; i < 91; i++) {
        printf("%c", l15[i]);
        Sleep(sleepLen);
    }
    setCursorPosition(getConsoleLen() / 2 - 91 / 2, centre + 3);
    for (int i = 0; i < 91; i++) {
        printf("%c", l21[i]);
        Sleep(sleepLen);
    }

    // Wait half a sec, then clear HANGMAN line by line
    Sleep(500);

}

void printMainMenu(int selection) {
    //clearScreen();
    //system("cls");
    clearLines(10, 21);
    char l15[91] = "M\"\"MMMMM\"\"MM MMP\"\"\"\"\"\"\"MM M\"\"\"\"\"\"\"`YM MM'\"\"\"\"\"`MM M\"\"\"\"\"`'\"\"\"`YM MMP\"\"\"\"\"\"\"MM M\"\"\"\"\"\"\"`YM ",
    l16[91] = "M  MMMMM  MM M' .mmmm  MM M  mmmm.  M M' .mmm. `M M  mm.  mm.  M M' .mmmm  MM M  mmmm.  M ",
    l17[91] = "M         `M M         `M M  MMMMM  M M  MMMMMMMM M  MMM  MMM  M M         `M M  MMMMM  M ",
    l18[91] = "M  MMMMM  MM M  MMMMM  MM M  MMMMM  M M  MMM   `M M  MMM  MMM  M M  MMMMM  MM M  MMMMM  M ",
    l19[91] = "M  MMMMM  MM M  MMMMM  MM M  MMMMM  M M. `MMM' .M M  MMM  MMM  M M  MMMMM  MM M  MMMMM  M ",
    l20[91] = "M  MMMMM  MM M  MMMMM  MM M  MMMMM  M MM.     .MM M  MMM  MMM  M M  MMMMM  MM M  MMMMM  M ",
    l21[91] = "MMMMMMMMMMMM MMMMMMMMMMMM MMMMMMMMMMM MMMMMMMMMMM MMMMMMMMMMMMMM MMMMMMMMMMMM MMMMMMMMMMM ",
    *levelSelectionUp = "######################################",
    *levelSelection =   "#            LEVEL SELECTION         #",
    *levelEasy = "EASY\n",
    *levelEasySelected = ">> EASY <<\n",
    *levelMedium = "MEDIUM\n",
    *levelMediumSelected = ">> MEDIUM <<\n",
    *levelHard = "HARD\n",
    *levelHardSelected = ">> HARD <<\n",
    *levelInsane= "INSANE\n",
    *levelInsaneSelected = ">> INSANE <<\n",
    *instructionText = "CONTROLS:",
    *wKey = "\tW / UP -> Cursor Up",
    *sKey = "\tS / DOWN -> Cursor Down",
    *returnKey = "\tENTER -> Confirm Selection";

    // Print title to top of screen
    printCentre(l15, 1);
    printCentre(l16, 2);
    printCentre(l17, 3);
    printCentre(l18, 4);
    printCentre(l19, 5);
    printCentre(l20, 6);
    printCentre(l21, 7);

    // Print level selection title
    printCentre(levelSelectionUp, 11);
    printCentre(levelSelection, 12);
    printCentre(levelSelectionUp, 13);

    // Print instructions
    printLeft(instructionText, 15);
    printLeft(wKey, 16);
    printLeft(sKey, 17);
    printLeft(returnKey, 18);

    // Print actual menu
    switch (selection) {
        case 0:
            printCentre(levelEasySelected, 15);
            printCentre(levelMedium, 17);
            printCentre(levelHard, 19);
            printCentre(levelInsane, 21);
            break;
        case 1:
            printCentre(levelEasy, 15);
            printCentre(levelMediumSelected, 17);
            printCentre(levelHard, 19);
            printCentre(levelInsane, 21);
            break;
        case 2:
            printCentre(levelEasy, 15);
            printCentre(levelMedium, 17);
            printCentre(levelHardSelected, 19);
            printCentre(levelInsane, 21);
            break;
        case 3:
            printCentre(levelEasy, 15);
            printCentre(levelMedium, 17);
            printCentre(levelHard, 19);
            printCentre(levelInsaneSelected, 21);
            break;
        default:
            printXYCentre("AN ERROR HAS OCCURRED WHILE GENERATING THE MENU! Please try again!");

            break;
    }

}

void printLeft(char *str, short yCoord) {
    setCursorPosition(0, yCoord);
    printf(str);
}

void printError(char *msg) {

    printMessage("!!! ERROR !!!", msg);

    printf("\a");
}

void printMessage(char *title, char *msg) {
    char *l1 = "  =====================================================================  ", // TWO SPACES AT THE END!
         *l2 = "  ||                                                                 ||  ";

        short yCoord = 12, height = 12;

        for (short i = 0; i < height; i++) {
            if (i == 0) {
                printCentre(l1, yCoord);
            } else if (i != height - 1) {
                printCentre(l2, yCoord + i);
            } else {
                printCentre(l1, yCoord + i);
            }
        }

        printCentre(title, yCoord + 2);
        printCentre(msg, yCoord + 5);
        printCentre("Hit [ ENTER ] to Continue!", height + yCoord + 2);
        getchar();
}

void clearLines(short from, short to) {
    for (short i = from; i < to + 1; i++) {
        clearLine(i);
    }
}
