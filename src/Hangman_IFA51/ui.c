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
