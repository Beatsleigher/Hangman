// Written by Simon Cahill
// Copyright (c) 2016
// All Right Reserved
// Copies and modifications of this file are prohibited and punishable by law,
// unless done with EXPRESS PERMISSION by the author of this file.

#ifndef UI_H_INCLUDED
#define UI_H_INCLUDED

#include <windows.h>

///////////////////////////////////////
/// \brief Gets the length of the console
///         window by columns.
///////////////////////////////////////
int getConsoleLen();

///////////////////////////////////////
/// \brief Gets the height of the console
///         window by rows.
///////////////////////////////////////
int getConsoleHeight();

///////////////////////////////////////
/// \brief Converts an X and a Y value
///         to a COORD struct.
///////////////////////////////////////
COORD getCoord(short x, short y);

///////////////////////////////////////
/// \brief Sets the position of the
///         cursor in the window to the
///         given coordinates.
///////////////////////////////////////
void setCursorPosition(short x, short y);

///////////////////////////////////////
/// \brief Prints to the centre (X-axis)
///         of the console window.
///////////////////////////////////////
void printCentre(char *str, short yCoord);

///////////////////////////////////////
/// \brief Prints to the right side of
///         the console window.
///////////////////////////////////////
void printRight(char *str, short yCoord);

///////////////////////////////////////
/// \brief Prints to the centre (X/Y axis)
///         of the console window.
///////////////////////////////////////
void printXYCentre(char *str);

///////////////////////////////////////
/// \brief Prints a given string to the
///         top row in the middle of the
///         console screen.
///////////////////////////////////////
void printTopCentre(char *str);

///////////////////////////////////////
/// \brief Prints a given string to the
///         bottom row in the middle of
///         the console screen.
///////////////////////////////////////
void printBottomCentre(char *str);

///////////////////////////////////////
/// \brief Prints a progress bar to the
///         top of the console screen.
///////////////////////////////////////
void printProgressBar(int percent, int startFrom);

///////////////////////////////////////
/// \brief Clears the console screen
///         by scrolling through the rows
///         and columns of the screen,
///         and clearing each char.
///         Gives it a cool retro-look.
///////////////////////////////////////
void clearScreen();

#endif // UI_H_INCLUDED
