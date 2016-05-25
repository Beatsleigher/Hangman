// Written by Simon Cahill
// Copyright (c) 2016
// All Right Reserved
// Copies and modifications of this file are prohibited and punishable by law,
// unless done with EXPRESS PERMISSION by the author of this file.

#ifndef SYSTEMIO_H_INCLUDED
#define SYSTEMIO_H_INCLUDED

#include <stdbool.h>

//#========== Structs ==========#

///////////////////////////////////////
/// \brief  Struct containing variables for storing
///         the words for the different categories
///         and levels in the game.
///////////////////////////////////////
struct WordCategories {
    char easyWords[1200][11]; // Really super-easy words...
    char mediumWords[1200][19]; // Some more complex words...
    char hardWords[1200][23]; // This should be semi-tricky
    char insaneWords[200][127]; // This. IS. SPARTAAA
};

///////////////////////////////////////
/// \brief  Declare type, as to make
///         programming easier.
///////////////////////////////////////
typedef struct WordCategories WordCategories;

//#========== Methods and Functions ==========#

///////////////////////////////////////
/// \brief  Gets a value indicating
///         whether the file containing
///         the words for this game exists
///         or not.
/// This method checks for the existence
/// of the file containing the words used
/// in and by this game.
/// This method is used to determine if
/// a new copy of this file should be
/// downloaded or not.
///////////////////////////////////////
bool wordFileExists();

///////////////////////////////////////
/// \brief  Downloads the file containing
///         the words used in the game.
///////////////////////////////////////
//void downloadWordsFile();

///////////////////////////////////////
/// \brief  Saves the file containing the
///         words to the local hard drive.
///////////////////////////////////////
void saveWordsFile();

///////////////////////////////////////
/// \brief  Reads the file containing the
///         words and stores them in a
///         provided struct (WordCategories)
/// \param wordCats A pointer to a
///                 (struct) WordCategories
///                 "instance"
///////////////////////////////////////
void readWords(struct WordCategories *wordCats);

///////////////////////////////////////
/// \brief  Creates the directories used
///         by this program if necessary.
///////////////////////////////////////
void createDirectories();

///////////////////////////////////////
/// \brief  Gets the length of the X-axis
///         of the console in which this
///         application is being executed.
///////////////////////////////////////
int getConsoleXLen();

#endif // SYSTEMIO_H_INCLUDED
