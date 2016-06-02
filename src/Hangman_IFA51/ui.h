// Written by Simon Cahill
// Copyright (c) 2016
// All Right Reserved
// Copies and modifications of this file are prohibited and punishable by law,
// unless done with EXPRESS PERMISSION by the author of this file.

#ifndef UI_H_INCLUDED
#define UI_H_INCLUDED

#define TOPIC_GENERAL 0
#define TOPIC_LEVEL_SELECTION 1
#define TOPIC_GAMEPLAY 2
#define TOPIC_LEVEL_EASY 3
#define TOPIC_LEVEL_MEDIUM 4
#define TOPIC_LEVEL_HARD 5
#define TOPIC_LEVEL_INSANE 6

#define divider 4 // Used to determine where screen will be divided for different purposes.


#include <windows.h>
#include <stdbool.h>
#include <string.h>

/**
###########################################################
###                       Variables                     ###
###########################################################
*/

///////////////////////////////////////
/// \brief  Contains the amount of spaces
///         required to clear each line
///         of the console.
///////////////////////////////////////
char clearLineString[2048];

///////////////////////////////////////
/// \brief  Contains the amount of spaces
///         required to clear each line
///         of text in the help menu.
///////////////////////////////////////
char clearHelpLineString[2048];

/**
###########################################################
###                   Method Prototypes                 ###
###########################################################
*/

///////////////////////////////////////
/// \brief  Gets the length of the console
///         window by columns.
///////////////////////////////////////
int getConsoleLen();

///////////////////////////////////////
/// \brief  Gets the height of the console
///         window by rows.
///////////////////////////////////////
int getConsoleHeight();

///////////////////////////////////////
/// \brief  Converts an X and a Y value
///         to a COORD struct.
///////////////////////////////////////
COORD getCoord(short x, short y);

///////////////////////////////////////
/// \brief  Sets the position of the
///         cursor in the window to the
///         given coordinates.
///////////////////////////////////////
void setCursorPosition(short x, short y);

///////////////////////////////////////
/// \brief  Prints to the centre (X-axis)
///         of the console window.
///////////////////////////////////////
void printCentre(char *str, short yCoord);

///////////////////////////////////////
/// \brief  Prints to the right side of
///         the console window.
///////////////////////////////////////
void printRight(char *str, short yCoord);

///////////////////////////////////////
/// \brief  Prints to the centre (X/Y axis)
///         of the console window.
///////////////////////////////////////
void printXYCentre(char *str);

///////////////////////////////////////
/// \brief  Prints a given string to the
///         top row in the middle of the
///         console screen.
///////////////////////////////////////
void printTopCentre(char *str);

///////////////////////////////////////
/// \brief  Prints a given string to the
///         bottom row in the middle of
///         the console screen.
///////////////////////////////////////
void printBottomCentre(char *str);

///////////////////////////////////////
/// \brief  Prints a progress bar to the
///         top of the console screen.
///////////////////////////////////////
void printProgressBar(int percent, int startFrom);

///////////////////////////////////////
/// \brief  Clears the console screen
///         by scrolling through the rows
///         and columns of the screen,
///         and clearing each char.
///         Gives it a cool retro-look.
///////////////////////////////////////
void clearScreen();

///////////////////////////////////////
/// \brief  Clears a single line in the
///         console.
///////////////////////////////////////
void clearLine(short row);

///////////////////////////////////////
/// \brief  Clears a single column in the
///         console.
///////////////////////////////////////
void clearColumn(short col);

///////////////////////////////////////
/// \brief  Clears the top line in the
///         console.
///////////////////////////////////////
void clearTopLine();

///////////////////////////////////////
/// \brief  Clears the bottom line in the
///         console.
///////////////////////////////////////
void clearBottomLine();

///////////////////////////////////////
/// \brief  Clears the screen in a cool
///         retro cinematic way!
///////////////////////////////////////
void cinematicClear();

///////////////////////////////////////
/// \brief  Prints the welcome screen
///         in a cool cinematic
///////////////////////////////////////
void printWelcomeScreen();

///////////////////////////////////////
/// \brief  Prints the main menu to the
///         screen. This method does NOT
///         wait for ANY type of input.
///         It prints, and exits.
///////////////////////////////////////
void printMainMenu(int selection);

///////////////////////////////////////
/// \brief  Prints any given text to the
///         left side of the console at
///         the given Y coords.
///////////////////////////////////////
void printLeft(char *str, short yCoord);

///////////////////////////////////////
/// \brief  Prints an error in a cool
///         retro-style message box.
///////////////////////////////////////
void printError(char *msg);

///////////////////////////////////////
/// \brief  Prints a message in a cool
///         retro-style message box.
///////////////////////////////////////
void printMessage(char *title, char *msg);

///////////////////////////////////////
/// \brief  Clears all the lines between
///         the from and to param values.
///         Includes the actual lines, too.
///////////////////////////////////////
void clearLines(short from, short to);

///////////////////////////////////////
/// \brief  Prints a message similar to
///         the \see printMessage
///         function. The main difference,
///         is that this function will
///         print multiple lines (max 5)
///         in to the message box.
///         This is idea when displaying
///         complex errors and
///         notifications.
///////////////////////////////////////
void printMultilineMsg(char *title, char lines[5][60], short linesPassed);

///////////////////////////////////////
/// \brief  Prints a message similar to
///         the \see printError
///         function. The main difference,
///         is that this function will
///         print multiple lines (max 5)
///         in to the message box.
///         This is idea when displaying
///         complex errors and
///         notifications.
///////////////////////////////////////
void printMultilineError(char lines[5][60], short linesPassed);

///////////////////////////////////////
/// \brief  Shows a skull and crossbones,
///         and text saying "game over".
///         Indicates EOG.
///////////////////////////////////////
void showGameOver();

///////////////////////////////////////
/// \brief  Shows the loading screen.
///         Shown immediately before
///         actual game screen is shown.
///////////////////////////////////////
void showLoadingScreen();

///////////////////////////////////////
/// \brief  Shows a choice dialog, where
///         the user can choose what to
///         do.
///////////////////////////////////////
bool showChoiceDialog(char *title, char msg[5][60], char *okButton, char *cancelButton);

///////////////////////////////////////
/// \brief  Sets the text (foreground)
///         colour in the console window.
///////////////////////////////////////
void setForegoundColour(WORD colour);

///////////////////////////////////////
/// \brief  Sets the background colour
///         in the console window.
///////////////////////////////////////
void setBackgroundColour(WORD colour);

///////////////////////////////////////
/// \brief  Resets the colours of the
///         console window to their
///         defaults for this application.
///////////////////////////////////////
void resetConsoleColours();

///////////////////////////////////////
/// \brief  Prints a bar at the bottom
///         of the screen for status
///         messages and such.
///////////////////////////////////////
void printStatusBar();

///////////////////////////////////////
/// \brief  Prints a message to the
///         status bar at the bottom
///         of the screen.
///////////////////////////////////////
void printStatusBarMsg(char *msg);

///////////////////////////////////////
/// \brief  Removes the status bar from
///         the bottom of the console
///         Might come in handy...
///////////////////////////////////////
void clearStatusBar();

///////////////////////////////////////
/// \brief  Prints a screen saying
///         goodbye to the player.
///////////////////////////////////////
void printGoodBye();

///////////////////////////////////////
/// \brief  Prints the actual game UI
///////////////////////////////////////
void printGameUI(int selectedLevel, char *randomWord, short errors, char typedChar, char typedErrors[7][1]);

///////////////////////////////////////
/// \brief  Prints the actual hangman.
///         Depending on how many errors
///         have occurred, more or less
///         parts of the hangman will be
///         shown.
///////////////////////////////////////
void printHangman(short errors);

///////////////////////////////////////
/// \brief  Prints the current stats for the ongoing game.
///////////////////////////////////////
void printGameStats(short errors, char typedErrors[7][1]);

///////////////////////////////////////
/// \brief  Prints the placeholder for
///         the hidden word.
///////////////////////////////////////
void printGameWordPlaceholder(char *word);

///////////////////////////////////////
/// \brief  Prints a screen notifying
///         the player that they have
///         won the game!
///         Congrats to them!
///////////////////////////////////////
void printGameWonScreen();

///////////////////////////////////////
/// \brief  Prints the help screen.
///         Unlike most methods in this
///         header, this method contains
///         some logic for displaying
///         different topics.
///////////////////////////////////////
void printHelp(int topic, bool show);

///////////////////////////////////////
/// \brief  Prints the actual side menu
///         for the help menu.
///         This method contains no
///         logic whatsoever, really...
///////////////////////////////////////
void printHelpMenu(int topic);

///////////////////////////////////////
/// \brief  Prints different help texts
///         for the help menu.
///         Each line of text is max.
///         82 chars long, and max 27
///         lines (per page)!
///////////////////////////////////////
void printHelpText(int topic);

///////////////////////////////////////
/// \brief  Wrapper method to set the
///         size of the console window.
///         This method will NOT redraw
///         and window content!
///////////////////////////////////////
void setConsoleSize(short width, short height);

#endif // UI_H_INCLUDED
