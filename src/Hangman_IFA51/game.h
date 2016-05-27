// Written by Simon Cahill
// Copyright (c) 2016
// All Right Reserved
// Copies and modifications of this file are prohibited and punishable by law,
// unless done with EXPRESS PERMISSION by the author of this file.

#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <stdbool.h>

// Project includes
#include "systemio.h"
#include "words.h"

// File definitions
#define LEVEL_EASY 0
#define LEVEL_MEDIUM 1
#define LEVEL_HARD 2
#define LEVEL_INSANE 3
#define QUIT_GAME -1
#define SHOW_HELP -3

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
#define ESC_KEY 27
#define QUESTION_MARK_KEY 63

///////////////////////////////////////
/// \brief  Shows the menu for the game.
///////////////////////////////////////
int showGameMenu();

///////////////////////////////////////
/// \brief  A value indicating whether
///         the game should continue
///         running or not.
///////////////////////////////////////
bool runGame;

///////////////////////////////////////
/// \brief  Indicates the level that the
///         player selected.
///////////////////////////////////////
int selectedLevel;

///////////////////////////////////////
/// \brief  Executes the game (loop).
///////////////////////////////////////
void executeGame(struct WordCategories words);

///////////////////////////////////////
/// \brief  Takes two arguments (strings).
///         Checks if these two strings
///         are anagrams.
///////////////////////////////////////
bool isAnagram(const char *str1, const char *str2);

///////////////////////////////////////
/// \brief  Converts all the chars in a
///         string to their lower-case
///         respective counterparts.
///////////////////////////////////////
char* toLower(char *str);

///////////////////////////////////////
/// \brief  Removes all leading and
///         trailing whitespace from a
///         string.
///////////////////////////////////////
char* trim(char *str);

#endif // GAME_H_INCLUDED
