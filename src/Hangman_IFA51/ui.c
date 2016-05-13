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
    int sleepLen = 10;

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
    char l15[91] = "M\"\"MMMMM\"\"MM MMP\"\"\"\"\"\"\"MM M\"\"\"\"\"\"\"`YM MM'\"\"\"\"\"`MM M\"\"\"\"\"`'\"\"\"`YM MMP\"\"\"\"\"\"\"MM M\"\"\"\"\"\"\"`YM ",
    l16[91] = "M  MMMMM  MM M' .mmmm  MM M  mmmm.  M M' .mmm. `M M  mm.  mm.  M M' .mmmm  MM M  mmmm.  M ",
    l17[91] = "M         `M M         `M M  MMMMM  M M  MMMMMMMM M  MMM  MMM  M M         `M M  MMMMM  M ",
    l18[91] = "M  MMMMM  MM M  MMMMM  MM M  MMMMM  M M  MMM   `M M  MMM  MMM  M M  MMMMM  MM M  MMMMM  M ",
    l19[91] = "M  MMMMM  MM M  MMMMM  MM M  MMMMM  M M. `MMM' .M M  MMM  MMM  M M  MMMMM  MM M  MMMMM  M ",
    l20[91] = "M  MMMMM  MM M  MMMMM  MM M  MMMMM  M MM.     .MM M  MMM  MMM  M M  MMMMM  MM M  MMMMM  M ",
    l21[91] = "MMMMMMMMMMMM MMMMMMMMMMMM MMMMMMMMMMM MMMMMMMMMMM MMMMMMMMMMMMMM MMMMMMMMMMMM MMMMMMMMMMM ",
    levelEasy[4] = "EASY",
    levelEasySelected[10] = ">> EASY <<",
    levelMedium[6] = "MEDIUM",
    levelMediumSelected[12] = ">> MEDIUM <<",
    levelHard[4] = "HARD",
    levelHardSelected[10] = ">> HARD <<",
    levelInsane[6] = "INSANE",
    levelInsaneSelected[12] = ">> INSANE <<",
    wKey[14] = "W -> Cursor Up",
    sKey[16] = "S -> Cursor Down";

    // Print title to top of screen
    printCentre(l15, 0);
    printCentre(l16, 1);
    printCentre(l17, 2);
    printCentre(l18, 3);
    printCentre(l19, 4);
    printCentre(l20, 5);
    printCentre(l21, 6);

}
