// Written by Simon Cahill
// Copyright (c) 2016
// All Rights Reserved
// Copies and modifications of this file are prohibited and punishable by law,
// unless done with EXPRESS PERMISSION by the author of this file.


#include <stdio.h>
#include <stdlib.h>

// Project includes
#include "main.h"
#include "systemio.h"
#include "words.h"

int main() {

    // Create directories needed by the program
    createDirectories();

    // Check if word files exist.
    struct WordCategories wordCategories;
    wordCategories = getWords();

    return 0;
}
