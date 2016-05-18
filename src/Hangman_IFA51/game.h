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

#endif // GAME_H_INCLUDED
