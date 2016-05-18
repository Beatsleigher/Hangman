// Written by Simon Cahill
// Copyright (c) 2016
// All Right Reserved
// Copies and modifications of this file are prohibited and punishable by law,
// unless done with EXPRESS PERMISSION by the author of this file.

#ifndef WORDS_H_INCLUDED
#define WORDS_H_INCLUDED



///////////////////////////////////////
/// \brief  Declare type, as to make
///         programming easier.
///////////////////////////////////////
typedef struct WordCategories WordCategories;

///////////////////////////////////////
/// \brief  Method template
///////////////////////////////////////
struct WordCategories getWords();

///////////////////////////////////////
/// \brief  Struct containing all the
///         words loaded.
///////////////////////////////////////
struct WordCategories loadedWords;

#endif // WORDS_H_INCLUDED
