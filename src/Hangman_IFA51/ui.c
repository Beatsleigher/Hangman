// Written by Simon Cahill
// Copyright (c) 2016
// All Right Reserved
// Copies and modifications of this file are prohibited and punishable by law,
// unless done with EXPRESS PERMISSION by the author of this file.

// Project includes
#include "ui.h"
#include "systemio.h"
#include "words.h"
#include "game.h"

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
#include <stdbool.h>

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
    int y = 0;
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
//        printf("\xDB"); // Full block
//        printf("\xDC"); // Lower half block
        printf("\xDF"); // Upper half block
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
    //clearLines(10, 21);
    char l15[91] = "M\"\"MMMMM\"\"MM MMP\"\"\"\"\"\"\"MM M\"\"\"\"\"\"\"`YM MM'\"\"\"\"\"`MM M\"\"\"\"\"`'\"\"\"`YM MMP\"\"\"\"\"\"\"MM M\"\"\"\"\"\"\"`YM ",
    l16[91] = "M  MMMMM  MM M' .mmmm  MM M  mmmm.  M M' .mmm. `M M  mm.  mm.  M M' .mmmm  MM M  mmmm.  M ",
    l17[91] = "M         `M M         `M M  MMMMM  M M  MMMMMMMM M  MMM  MMM  M M         `M M  MMMMM  M ",
    l18[91] = "M  MMMMM  MM M  MMMMM  MM M  MMMMM  M M  MMM   `M M  MMM  MMM  M M  MMMMM  MM M  MMMMM  M ",
    l19[91] = "M  MMMMM  MM M  MMMMM  MM M  MMMMM  M M. `MMM' .M M  MMM  MMM  M M  MMMMM  MM M  MMMMM  M ",
    l20[91] = "M  MMMMM  MM M  MMMMM  MM M  MMMMM  M MM.     .MM M  MMM  MMM  M M  MMMMM  MM M  MMMMM  M ",
    l21[91] = "MMMMMMMMMMMM MMMMMMMMMMMM MMMMMMMMMMM MMMMMMMMMMM MMMMMMMMMMMMMM MMMMMMMMMMMM MMMMMMMMMMM ",
    *levelSelectionUp = "######################################",
    *levelSelection =   "#           LEVEL SELECTION          #",
//    *levelSelectionUp = "\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB",
//    *levelSelection =   "\xDB           LEVEL SELECTION          \xDB",
    *levelEasy = "EASY\n",
    *levelEasySelected = ">> EASY <<\n",
    *levelMedium = "MEDIUM\n",
    *levelMediumSelected = ">> MEDIUM <<\n",
    *levelHard = "HARD\n",
    *levelHardSelected = ">> HARD <<\n",
    *levelInsane= "INSANE\n",
    *levelInsaneSelected = ">> INSANE <<\n",
    *instructionText = "CONTROLS:",
    *wKey = "\tW / UP\t\t-> Cursor Up",
    *sKey = "\tS / DOWN\t-> Cursor Down",
    *returnKey = "\tENTER\t\t-> Confirm Selection",
    *escKey = "\tESC\t\t-> Exit Game",
    *questionMarkKey = "\t?\t\t-> Help";

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
    printLeft(escKey, 19);
    printLeft(questionMarkKey, 20);

    // Clear menu items
    // Just print whitespace.
    printCentre("            ", 15);
    printCentre("            ", 17);
    printCentre("            ", 19);
    printCentre("            ", 21);

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
    char *l1 = "  \xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB  ", // TWO SPACES AT THE END!
         *l2 = "\xBA                                                                    \xBA",
         *l3 = "  \xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC  ";

        short yCoord = 12, height = 12;

        for (short i = 0; i < height; i++) {
            if (i == 0) {
                printCentre(l1, yCoord);
            } else if (i != height - 1) {
                printCentre(l2, yCoord + i);
            } else {
                printCentre(l3, yCoord + i);
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

void printMultilineMsg(char *title, char lines[5][60], short linesPassed) {
    char *l1 = "  \xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB  ", // TWO SPACES AT THE END!
         *l2 = "\xBA                                                                    \xBA",
         *l3 = "  \xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC  ";

        short yCoord = 12, height = 12;

        for (short i = 0; i < height; i++) {
            if (i == 0) {
                printCentre(l1, yCoord);
            } else if (i != height - 1) {
                printCentre(l2, yCoord + i);
            } else {
                printCentre(l3, yCoord + i);
            }
            //Sleep(750);
        }

        printCentre(title, yCoord + 2);

        for (int i = 0; i < linesPassed; i++) {
            printCentre(lines[i], yCoord + i + 5);
//            Sleep(1000);
        }

        printCentre("Hit [ ENTER ] to Continue!", height + yCoord + 2);
        getchar();
}

void printMultilineError(char lines[5][60], short linesPassed) {
    printMultilineMsg("!!! ERROR !!!", lines, linesPassed);
}

void showGameOver() {
    char skullCrossBones[22][60];
    char gameOver[5][60];
    strcpy(skullCrossBones[0],  "...                  ... MNO! ...                  ");
    strcpy(skullCrossBones[1],  "   ..... MNO!! ...................... MNNOO! ...   ");
    strcpy(skullCrossBones[2],  " ..... MMNO! ......................... MNNOO!! .   ");
    strcpy(skullCrossBones[3],  "..... MNOONNOO!   MMMMMMMMMMPPPOII!   MNNO!!!! .   ");
    strcpy(skullCrossBones[4],  " ... !O! NNO! MMMMMMMMMMMMMPPPOOOII!! NO! ....     ");
    strcpy(skullCrossBones[5],  "    ...... ! MMMMMMMMMMMMMPPPPOOOOIII! ! ...       ");
    strcpy(skullCrossBones[6],  "   ........ MMMMMMMMMMMMPPPPPOOOOOOII!! .....      ");
    strcpy(skullCrossBones[7],  "   ........ MMMMMOOOOOOPPPPPPPPOOOOMII! ...        ");
    strcpy(skullCrossBones[8],  "    ....... MMMMM..    OPPMMP    .,OMI! ....       ");
    strcpy(skullCrossBones[9],  "     ...... MMMM::   o.,OPMP,.o   ::I!! ...        ");
    strcpy(skullCrossBones[10], "         .... NNM:::.,,OOPM!P,.::::!! ....         ");
    strcpy(skullCrossBones[11], "          .. MMNNNNNOOOOPMO!!IIPPO!!O! .....       ");
    strcpy(skullCrossBones[12], "         ... MMMMMNNNNOO:!!:!!IPPPPOO! ....        ");
    strcpy(skullCrossBones[13], "           .. MMMMMNNOOMMNNIIIPPPOO!! ......       ");
    strcpy(skullCrossBones[14], "          ...... MMMONNMMNNNIIIOO!..........       ");
    strcpy(skullCrossBones[15], "       ....... MN MOMMMNNNIIIIIO! OO ..........    ");
    strcpy(skullCrossBones[16], "    ......... MNO! IiiiiiiiiiiiI OOOO ...........  ");
    strcpy(skullCrossBones[17], "  ...... NNN.MNO! . O!!!!!!!!!O . OONO NO! ........");
    strcpy(skullCrossBones[18], "   .... MNNNNNO! ...OOOOOOOOOOO .  MMNNON!........ ");
    strcpy(skullCrossBones[19], "   ...... MNNNNO! .. PPPPPPPPP .. MMNON!........   ");
    strcpy(skullCrossBones[20], "      ...... OO! ................. ON! .......     ");
    strcpy(skullCrossBones[21], "         ...........                               ");

    strcpy(gameOver[0],  "  ___    __    __  __  ____    _____  _  _  ____  ____ ");
    strcpy(gameOver[1],  " / __)  /__\\  (  \\/  )( ___)  (  _  )( \\/ )( ___)(  _ \\");
    strcpy(gameOver[2],  "( (_-. /(__)\\  )    (  )__)    )(_)(  \\  /  )__)  )   /");
    strcpy(gameOver[3],  " \\___/(__)(__)(_/\\/\\_)(____)  (_____)  \\/  (____)(_)\\_)");

    clearLines(3, 29);
    for (int i = 0; i < sizeof(skullCrossBones) / sizeof(skullCrossBones[0]); i++) {
        printCentre(skullCrossBones[i], i + 4);
    }

    for (int i = 0; i < sizeof(gameOver) / sizeof(gameOver[0]); i++) {
        printCentre(gameOver[i], i + 26);
    }

}

void showLoadingScreen() {
    clearScreen();

    short height = (short)getConsoleHeight() / 2;

    printCentre("M\"\"MMMMMMMM MMP\"\"\"\"\"YMM MMP\"\"\"\"\"\"\"MM M\"\"\"\"\"\"'YMM M\"\"M M\"\"\"\"\"\"\"`YM MM'\"\"\"\"\"`MM ", height - 3);
    printCentre("M  MMMMMMMM M' .mmm. `M M' .mmmm  MM M  mmmm. `M M  M M  mmmm.  M M' .mmm. `M ", height - 2);
    printCentre("M  MMMMMMMM M  MMMMM  M M         `M M  MMMMM  M M  M M  MMMMM  M M  MMMMMMMM ", height - 1);
    printCentre("M  MMMMMMMM M  MMMMM  M M  MMMMM  MM M  MMMMM  M M  M M  MMMMM  M M  MMM   `M ", height);
    printCentre("M  MMMMMMMM M. `MMM' .M M  MMMMM  MM M  MMMM' .M M  M M  MMMMM  M M. `MMM' .M ", height + 1);
    printCentre("M         M MMb     dMM M  MMMMM  MM M       .MM M  M M  MMMMM  M MM.     .MM ", height + 2);
    printCentre("MMMMMMMMMMM MMMMMMMMMMM MMMMMMMMMMMM MMMMMMMMMMM MMMM MMMMMMMMMMM MMMMMMMMMMM ", height + 3);

    printCentre("Please wait while contents are being loaded and selected...", height + 6);

}

bool showChoiceDialog(char *title, char msg[5][60], char *okButton, char *cancelButton) {
    // TODO: Add logic
    return false;
}

void setForegoundColour(WORD colour) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole, colour);
}

void setBackgroundColour(WORD colour) { // I know, seemingly redundant, but makes things more comprehensive.
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole, colour);
}

void resetConsoleColours() {
    system("color 0a");
}

void printStatusBar() {
    for (int i = 0; i < getConsoleLen(); i++) {
        setCursorPosition(i, getConsoleHeight() - 1);
        printf("\xDB");
        setCursorPosition(i, 0); // Prevent screen from jumping up and down
    }
    setCursorPosition(getConsoleLen() / 2, getConsoleHeight() - 1);
}

void printStatusBarMsg(char *msg) {
    printStatusBar();
    printCentre(msg, getConsoleHeight() - 1);
}

void clearStatusBar() {
    clearLine(getConsoleHeight() - 1);
}

void printGoodBye() {
    // Clear screen
    clearScreen();

    // Print farewell
    char *l1 = "MM'\"\"\"\"\"`MM MMP\"\"\"\"\"YMM MMP\"\"\"\"\"YMM M\"\"\"\"\"\"'YMM M#\"\"\"\"\"\"\"'M  M\"\"MMMM\"\"M MM\"\"\"\"\"\"\"\"`M dP ",
         *l2 = "M' .mmm. `M M' .mmm. `M M' .mmm. `M M  mmmm. `M ##  mmmm. `M M. `MM' .M MM  mmmmmmmM 88 ",
         *l3 = "M  MMMMMMMM M  MMMMM  M M  MMMMM  M M  MMMMM  M #'        .M MM.    .MM M`      MMMM 88 ",
         *l4 = "M  MMM   `M M  MMMMM  M M  MMMMM  M M  MMMMM  M M#  MMMb.'YM MMMb  dMMM MM  MMMMMMMM dP ",
         *l5 = "M. `MMM' .M M. `MMM' .M M. `MMM' .M M  MMMM' .M M#  MMMM'  M MMMM  MMMM MM  MMMMMMMM    ",
         *l6 = "MM.     .MM MMb     dMM MMb     dMM M       .MM M#       .;M MMMM  MMMM MM        .M oo ",
         *l7 = "MMMMMMMMMMM MMMMMMMMMMM MMMMMMMMMMM MMMMMMMMMMM M#########M  MMMMMMMMMM MMMMMMMMMMMM    ";

    short centre = (short)getConsoleHeight() / 2;

    printCentre(l1, centre - 3);
    printCentre(l2, centre - 2);
    printCentre(l3, centre - 1);
    printCentre(l4, centre);
    printCentre(l5, centre + 1);
    printCentre(l6, centre + 2);
    printCentre(l7, centre + 3);


    // Sleep two seconds, clear screen again and exit.
    Sleep(2000);
    clearScreen();

}

void printGameUI(int selectedLevel, char *randomWord, short errors, char typedChar, char typedErrors[7][1]) {
    // Print box around window border

    /// Print top row
    for (int i = 0; i < getConsoleLen(); i++) {
        setCursorPosition(i, 0);
        if (i == 0) {
            printf("\xC9");
        } else if (i == getConsoleLen() - 1) {
            printf("\xBB");
        } else if (i == 14) {
            printf("\xCB");
        } else {
            printf("\xCD");
        }
    }
    switch (selectedLevel) {
        case LEVEL_EASY:
            printTopCentre("Hangman\xCD\xCD\xCD\xCDLevel: Easy");
            break;
        case LEVEL_MEDIUM:
            printTopCentre("Hangman\xCD\xCD\xCD\xCDLevel: Medium");
            break;
        case LEVEL_HARD:
            printTopCentre("Hangman\xCD\xCD\xCD\xCDLevel: Hard");
            break;
        case LEVEL_INSANE:
            printTopCentre("Hangman\xCD\xCD\xCD\xCDLevel: Insane!");
            break;
        default:
            break;
    }

    /// Print sides
    for (int i = 1; i < getConsoleHeight(); i++) {
        clearLine(i);
        printLeft("\xBA", i);
        printRight("\xBA", i);
        setCursorPosition(14, i);
        printf("\xBA");
        if (i == 3) {
            printLeft("\xCC\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB9", i);
        }
    }

    /// Print bottom row
    for (int i = 0; i < getConsoleLen(); i++) {
        setCursorPosition(i, getConsoleHeight() - 1);
        if (i == 0) {
            printf("\xC8");
        } else if (i == getConsoleLen() - 1) {
            printf("\xBC");
        } else if (i == 14) {
            printf("\xCA");
        } else {
            printf("\xCD");
        }
    }
    setCursorPosition(0, 0);

    printHangman(errors);

}

void printHangman(short errors) {
    short yCoord = 3;
    char *hang1 =  " ___________.._______    ",
         *hang2 =  "| .__________))______|   ",
         *hang3 =  "| | / /      ||          ",
         *hang4 =  "| |/ /       ||          ",
         *hang5 =  "| | /        ||          ",
         *hang6 =  "| |/         ||          ",
         *hang7 =  "| |          ||          ",
         *hang8 =  "| |                      ",
         *hang9 =  "| |                      ",
         *hang10 = "| |                      ",
         *hang11 = "| |                      ",
         *hang12 = "| |                      ",
         *hang13 = "| |                      ",
         *hang14 = "| |                      ",
         *hang15 = "| |                      ",
         *hang16 = "| |                      ",
         *hang17 = "| |                      ",
         *hang18 = "| |                      ",
         *hang19 = "\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"|",
         *hang20 = "|\"|\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"|\"|",
         *hang21 = "| |                   | |",
         *hang22 = ": :                   : :",
         *hang23 = ". .                   . .";

    char *hang1_0 =  " ___________.._______    ",
         *hang2_0 =  "| .__________))______|   ",
         *hang3_0 =  "| | / /      ||          ",
         *hang4_0 =  "| |/ /       ||          ",
         *hang5_0 =  "| | /        ||.-''.     ",
         *hang6_0 =  "| |/         |/  _  \\    ",
         *hang7_0 =  "| |          ||  `/,|    ",
         *hang8_0 =  "| |          (\\\\`_.'     ",
         *hang9_0 =  "| |         .-`--'.      ",
         *hang10_0 = "| |                      ",
         *hang11_0 = "| |                      ",
         *hang12_0 = "| |                      ",
         *hang13_0 = "| |                      ",
         *hang14_0 = "| |                      ",
         *hang15_0 = "| |                      ",
         *hang16_0 = "| |                      ",
         *hang17_0 = "| |                      ",
         *hang18_0 = "| |                      ",
         *hang19_0 = "\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"|",
         *hang20_0 = "|\"|\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"|\"|",
         *hang21_0 = "| |                   | |",
         *hang22_0 = ": :                   : :",
         *hang23_0 = ". .                   . .";

    char *hang1_1 =  " ___________.._______    ",
         *hang2_1 =  "| .__________))______|   ",
         *hang3_1 =  "| | / /      ||          ",
         *hang4_1 =  "| |/ /       ||          ",
         *hang5_1 =  "| | /        ||.-''.     ",
         *hang6_1 =  "| |/         |/  _  \\    ",
         *hang7_1 =  "| |          ||  `/,|    ",
         *hang8_1 =  "| |          (\\\\`_.'     ",
         *hang9_1 =  "| |         .-`--'.      ",
         *hang10_1 = "| |         Y . . Y      ",
         *hang11_1 = "| |          |   |       ",
         *hang12_1 = "| |          | . |       ",
         *hang13_1 = "| |          |   |       ",
         *hang14_1 = "| |                      ",
         *hang15_1 = "| |                      ",
         *hang16_1 = "| |                      ",
         *hang17_1 = "| |                      ",
         *hang18_1 = "| |                      ",
         *hang19_1 = "\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"|",
         *hang20_1 = "|\"|\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"|\"|",
         *hang21_1 = "| |                   | |",
         *hang22_1 = ": :                   : :",
         *hang23_1 = ". .                   . .";

    char *hang1_2 =  " ___________.._______    ",
         *hang2_2 =  "| .__________))______|   ",
         *hang3_2 =  "| | / /      ||          ",
         *hang4_2 =  "| |/ /       ||          ",
         *hang5_2 =  "| | /        ||.-''.     ",
         *hang6_2 =  "| |/         |/  _  \\    ",
         *hang7_2 =  "| |          ||  `/,|    ",
         *hang8_2 =  "| |          (\\\\`_.'     ",
         *hang9_2 =  "| |         .-`--'.      ",
         *hang10_2 = "| |         Y . . Y\\     ",
         *hang11_2 = "| |          |   | \\\\    ",
         *hang12_2 = "| |          | . |  \\\\   ",
         *hang13_2 = "| |          |   |   (`  ",
         *hang14_2 = "| |                      ",
         *hang15_2 = "| |                      ",
         *hang16_2 = "| |                      ",
         *hang17_2 = "| |                      ",
         *hang18_2 = "| |                      ",
         *hang19_2 = "\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"|",
         *hang20_2 = "|\"|\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"|\"|",
         *hang21_2 = "| |                   | |",
         *hang22_2 = ": :                   : :",
         *hang23_2 = ". .                   . .";

    char *hang1_3 =  " ___________.._______    ",
         *hang2_3 =  "| .__________))______|   ",
         *hang3_3 =  "| | / /      ||          ",
         *hang4_3 =  "| |/ /       ||          ",
         *hang5_3 =  "| | /        ||.-''.     ",
         *hang6_3 =  "| |/         |/  _  \\    ",
         *hang7_3 =  "| |          ||  `/,|    ",
         *hang8_3 =  "| |          (\\\\`_.'     ",
         *hang9_3 =  "| |         .-`--'.      ",
         *hang10_3 = "| |        /Y . . Y\\     ",
         *hang11_3 = "| |       // |   | \\\\    ",
         *hang12_3 = "| |      //  | . |  \\\\   ",
         *hang13_3 = "| |     ')   |   |   (`  ",
         *hang14_3 = "| |                      ",
         *hang15_3 = "| |                      ",
         *hang16_3 = "| |                      ",
         *hang17_3 = "| |                      ",
         *hang18_3 = "| |                      ",
         *hang19_3 = "\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"|",
         *hang20_3 = "|\"|\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"|\"|",
         *hang21_3 = "| |                   | |",
         *hang22_3 = ": :                   : :",
         *hang23_3 = ". .                   . .";

    char *hang1_4 =  " ___________.._______    ",
         *hang2_4 =  "| .__________))______|   ",
         *hang3_4 =  "| | / /      ||          ",
         *hang4_4 =  "| |/ /       ||          ",
         *hang5_4 =  "| | /        ||.-''.     ",
         *hang6_4 =  "| |/         |/  _  \\    ",
         *hang7_4 =  "| |          ||  `/,|    ",
         *hang8_4 =  "| |          (\\\\`_.'     ",
         *hang9_4 =  "| |         .-`--'.      ",
         *hang10_4 = "| |        /Y . . Y\\     ",
         *hang11_4 = "| |       // |   | \\\\    ",
         *hang12_4 = "| |      //  | . |  \\\\   ",
         *hang13_4 = "| |     ')   |   |   (`  ",
         *hang14_4 = "| |          ||'||       ",
         *hang15_4 = "| |             ||       ",
         *hang16_4 = "| |             ||       ",
         *hang17_4 = "| |             ||       ",
         *hang18_4 = "| |             | \\     ",
         *hang19_4 = "\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"|",
         *hang20_4 = "|\"|\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"|\"|",
         *hang21_4 = "| |                   | |",
         *hang22_4 = ": :                   : :",
         *hang23_4 = ". .                   . .";

    char *hang1_5 =  " ___________.._______    ",
         *hang2_5 =  "| .__________))______|   ",
         *hang3_5 =  "| | / /      ||          ",
         *hang4_5 =  "| |/ /       ||          ",
         *hang5_5 =  "| | /        ||.-''.     ",
         *hang6_5 =  "| |/         |/  _  \\    ",
         *hang7_5 =  "| |          ||  `/,|    ",
         *hang8_5 =  "| |          (\\\\`_.'     ",
         *hang9_5 =  "| |         .-`--'.      ",
         *hang10_5 = "| |        /Y . . Y\\     ",
         *hang11_5 = "| |       // |   | \\\\    ",
         *hang12_5 = "| |      //  | . |  \\\\   ",
         *hang13_5 = "| |     ')   |   |   (`  ",
         *hang14_5 = "| |          ||'||       ",
         *hang15_5 = "| |          || ||       ",
         *hang16_5 = "| |          || ||       ",
         *hang17_5 = "| |          || ||       ",
         *hang18_5 = "| |         / | | \\     ",
         *hang19_5 = "\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"|",
         *hang20_5 = "|\"|\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"|\"|",
         *hang21_5 = "| |                   | |",
         *hang22_5 = ": :                   : :",
         *hang23_5 = ". .                   . .";

    char *hang1_6 =  " ___________.._______    ",
         *hang2_6 =  "| .__________))______|   ",
         *hang3_6 =  "| | / /      ||          ",
         *hang4_6 =  "| |/ /       ||          ",
         *hang5_6 =  "| | /        ||.-''.     ",
         *hang6_6 =  "| |/         |/  _  \\    ",
         *hang7_6 =  "| |          ||  `/,|    ",
         *hang8_6 =  "| |          (\\\\`_.'     ",
         *hang9_6 =  "| |         .-`--'.      ",
         *hang10_6 = "| |        /Y . . Y\\     ",
         *hang11_6 = "| |       // |   | \\\\    ",
         *hang12_6 = "| |      //  | . |  \\\\   ",
         *hang13_6 = "| |     ')   |   |   (`  ",
         *hang14_6 = "| |          ||'||       ",
         *hang15_6 = "| |          || ||       ",
         *hang16_6 = "| |          || ||       ",
         *hang17_6 = "| |          || ||       ",
         *hang18_6 = "| |         / | | \\     ",
         *hang19_6 = "\"\"\"\"\"\"\"\"\"\"|_`-' `-' |\"\"\"|",
         *hang20_6 = "|\"|\"\"\"\"\"\"\"\\ \\       '\"|\"|",
         *hang21_6 = "| |        \\ \\        | |",
         *hang22_6 = ": :         \\ \\       : :",
         *hang23_6 = ". .          `'       . .";

    if (errors == 0) {
        printCentre(hang1, yCoord++);
        printCentre(hang2, yCoord++);
        printCentre(hang3, yCoord++);
        printCentre(hang4, yCoord++);
        printCentre(hang5, yCoord++);
        printCentre(hang6, yCoord++);
        printCentre(hang7, yCoord++);
        printCentre(hang8, yCoord++);
        printCentre(hang9, yCoord++);
        printCentre(hang10, yCoord++);
        printCentre(hang11, yCoord++);
        printCentre(hang12, yCoord++);
        printCentre(hang13, yCoord++);
        printCentre(hang14, yCoord++);
        printCentre(hang15, yCoord++);
        printCentre(hang16, yCoord++);
        printCentre(hang17, yCoord++);
        printCentre(hang18, yCoord++);
        printCentre(hang19, yCoord++);
        printCentre(hang20, yCoord++);
        printCentre(hang21, yCoord++);
        printCentre(hang22, yCoord++);
        printCentre(hang23, yCoord++);
    } else if (errors == 1) {
        printCentre(hang1_0, yCoord++);
        printCentre(hang2_0, yCoord++);
        printCentre(hang3_0, yCoord++);
        printCentre(hang4_0, yCoord++);
        printCentre(hang5_0, yCoord++);
        printCentre(hang6_0, yCoord++);
        printCentre(hang7_0, yCoord++);
        printCentre(hang8_0, yCoord++);
        printCentre(hang9_0, yCoord++);
        printCentre(hang10_0, yCoord++);
        printCentre(hang11_0, yCoord++);
        printCentre(hang12_0, yCoord++);
        printCentre(hang13_0, yCoord++);
        printCentre(hang14_0, yCoord++);
        printCentre(hang15_0, yCoord++);
        printCentre(hang16_0, yCoord++);
        printCentre(hang17_0, yCoord++);
        printCentre(hang18_0, yCoord++);
        printCentre(hang19_0, yCoord++);
        printCentre(hang20_0, yCoord++);
        printCentre(hang21_0, yCoord++);
        printCentre(hang22_0, yCoord++);
        printCentre(hang23_0, yCoord++);
    } else if (errors == 2) {
        printCentre(hang1_1, yCoord++);
        printCentre(hang2_1, yCoord++);
        printCentre(hang3_1, yCoord++);
        printCentre(hang4_1, yCoord++);
        printCentre(hang5_1, yCoord++);
        printCentre(hang6_1, yCoord++);
        printCentre(hang7_1, yCoord++);
        printCentre(hang8_1, yCoord++);
        printCentre(hang9_1, yCoord++);
        printCentre(hang10_1, yCoord++);
        printCentre(hang11_1, yCoord++);
        printCentre(hang12_1, yCoord++);
        printCentre(hang13_1, yCoord++);
        printCentre(hang14_1, yCoord++);
        printCentre(hang15_1, yCoord++);
        printCentre(hang16_1, yCoord++);
        printCentre(hang17_1, yCoord++);
        printCentre(hang18_1, yCoord++);
        printCentre(hang19_1, yCoord++);
        printCentre(hang20_1, yCoord++);
        printCentre(hang21_1, yCoord++);
        printCentre(hang22_1, yCoord++);
        printCentre(hang23_1, yCoord++);
    } else if (errors == 3) {
        printCentre(hang1_2, yCoord++);
        printCentre(hang2_2, yCoord++);
        printCentre(hang3_2, yCoord++);
        printCentre(hang4_2, yCoord++);
        printCentre(hang5_2, yCoord++);
        printCentre(hang6_2, yCoord++);
        printCentre(hang7_2, yCoord++);
        printCentre(hang8_2, yCoord++);
        printCentre(hang9_2, yCoord++);
        printCentre(hang10_2, yCoord++);
        printCentre(hang11_2, yCoord++);
        printCentre(hang12_2, yCoord++);
        printCentre(hang13_2, yCoord++);
        printCentre(hang14_2, yCoord++);
        printCentre(hang15_2, yCoord++);
        printCentre(hang16_2, yCoord++);
        printCentre(hang17_2, yCoord++);
        printCentre(hang18_2, yCoord++);
        printCentre(hang19_2, yCoord++);
        printCentre(hang20_2, yCoord++);
        printCentre(hang21_2, yCoord++);
        printCentre(hang22_2, yCoord++);
        printCentre(hang23_2, yCoord++);
    } else if (errors == 4) {
        printCentre(hang1_3, yCoord++);
        printCentre(hang2_3, yCoord++);
        printCentre(hang3_3, yCoord++);
        printCentre(hang4_3, yCoord++);
        printCentre(hang5_3, yCoord++);
        printCentre(hang6_3, yCoord++);
        printCentre(hang7_3, yCoord++);
        printCentre(hang8_3, yCoord++);
        printCentre(hang9_3, yCoord++);
        printCentre(hang10_3, yCoord++);
        printCentre(hang11_3, yCoord++);
        printCentre(hang12_3, yCoord++);
        printCentre(hang13_3, yCoord++);
        printCentre(hang14_3, yCoord++);
        printCentre(hang15_3, yCoord++);
        printCentre(hang16_3, yCoord++);
        printCentre(hang17_3, yCoord++);
        printCentre(hang18_3, yCoord++);
        printCentre(hang19_3, yCoord++);
        printCentre(hang20_3, yCoord++);
        printCentre(hang21_3, yCoord++);
        printCentre(hang22_3, yCoord++);
        printCentre(hang23_3, yCoord++);
    } else if (errors == 5) {
        printCentre(hang1_4, yCoord++);
        printCentre(hang2_4, yCoord++);
        printCentre(hang3_4, yCoord++);
        printCentre(hang4_4, yCoord++);
        printCentre(hang5_4, yCoord++);
        printCentre(hang6_4, yCoord++);
        printCentre(hang7_4, yCoord++);
        printCentre(hang8_4, yCoord++);
        printCentre(hang9_4, yCoord++);
        printCentre(hang10_4, yCoord++);
        printCentre(hang11_4, yCoord++);
        printCentre(hang12_4, yCoord++);
        printCentre(hang13_4, yCoord++);
        printCentre(hang14_4, yCoord++);
        printCentre(hang15_4, yCoord++);
        printCentre(hang16_4, yCoord++);
        printCentre(hang17_4, yCoord++);
        printCentre(hang18_4, yCoord++);
        printCentre(hang19_4, yCoord++);
        printCentre(hang20_4, yCoord++);
        printCentre(hang21_4, yCoord++);
        printCentre(hang22_4, yCoord++);
        printCentre(hang23_4, yCoord++);
    } else if (errors == 6) {
        printCentre(hang1_5, yCoord++);
        printCentre(hang2_5, yCoord++);
        printCentre(hang3_5, yCoord++);
        printCentre(hang4_5, yCoord++);
        printCentre(hang5_5, yCoord++);
        printCentre(hang6_5, yCoord++);
        printCentre(hang7_5, yCoord++);
        printCentre(hang8_5, yCoord++);
        printCentre(hang9_5, yCoord++);
        printCentre(hang10_5, yCoord++);
        printCentre(hang11_5, yCoord++);
        printCentre(hang12_5, yCoord++);
        printCentre(hang13_5, yCoord++);
        printCentre(hang14_5, yCoord++);
        printCentre(hang15_5, yCoord++);
        printCentre(hang16_5, yCoord++);
        printCentre(hang17_5, yCoord++);
        printCentre(hang18_5, yCoord++);
        printCentre(hang19_5, yCoord++);
        printCentre(hang20_5, yCoord++);
        printCentre(hang21_5, yCoord++);
        printCentre(hang22_5, yCoord++);
        printCentre(hang23_5, yCoord++);
    } else if (errors == 7) {
        printCentre(hang1_6, yCoord++);
        printCentre(hang2_6, yCoord++);
        printCentre(hang3_6, yCoord++);
        printCentre(hang4_6, yCoord++);
        printCentre(hang5_6, yCoord++);
        printCentre(hang6_6, yCoord++);
        printCentre(hang7_6, yCoord++);
        printCentre(hang8_6, yCoord++);
        printCentre(hang9_6, yCoord++);
        printCentre(hang10_6, yCoord++);
        printCentre(hang11_6, yCoord++);
        printCentre(hang12_6, yCoord++);
        printCentre(hang13_6, yCoord++);
        printCentre(hang14_6, yCoord++);
        printCentre(hang15_6, yCoord++);
        printCentre(hang16_6, yCoord++);
        printCentre(hang17_6, yCoord++);
        printCentre(hang18_6, yCoord++);
        printCentre(hang19_6, yCoord++);
        printCentre(hang20_6, yCoord++);
        printCentre(hang21_6, yCoord++);
        printCentre(hang22_6, yCoord++);
        printCentre(hang23_6, yCoord++);
    } else {
        // ERROR
    }

}

void printGameStats(short errors, char typedErrors[7][1]) {
    short yCoord = 4;
    setCursorPosition(3, 2);
    printf("Fails (%i): ", errors);
    for (int i = 0; i < errors; i++) {
        setCursorPosition(7, yCoord + i);
        char error = typedErrors[i][0];
        printf("%c", error);
    }
}

void printGameWordPlaceholder(char *word) {
    setCursorPosition(getConsoleLen() / 2 - strlen(word), getConsoleHeight() - 2);
    for (int i = 0; i < strlen(word); i++) {
        printf(" _");
    }
}

void printGameWonScreen() {
    char *l1 = "                           oooo$$$$$$$$$$$$oooo                               ",
         *l2 = "                       oo$$$$$$$$$$$$$$$$$$$$$$$$o                            ",
         *l3 = "                    oo$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$o         o$   $$ o$      ",
         *l4 = "    o $ oo        o$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$o       $$ $$ $$o$     ",
         *l5 = " oo $ $ \"$      o$$$$$$$$$    $$$$$$$$$$$$$    $$$$$$$$$o       $$$o$$o$     ",
         *l6 = " \"$$$$$$o$     o$$$$$$$$$      $$$$$$$$$$$      $$$$$$$$$$o    $$$$$$$$       ",
         *l7 = "   $$$$$$$    $$$$$$$$$$$      $$$$$$$$$$$      $$$$$$$$$$$$$$$$$$$$$$$       ",
         *l8 = "   $$$$$$$$$$$$$$$$$$$$$$$    $$$$$$$$$$$$$    $$$$$$$$$$$$$$  \"\"\"$$$         ",
         *l9 = "    \"$$$\"\"\"\"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$     \"$$$        ",
         *l10 = "     $$$   o$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$     \"$$$o     ",
         *l11 = "    o$$\"   $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$       $$$o    ",
         *l12 = "    $$$    $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\" \"$$$$$$ooooo$$$$o  ",
         *l13 = "   o$$$oooo$$$$$  $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$   o$$$$$$$$$$$$$$$$$ ",
         *l14 = "   $$$$$$$$\"$$$$   $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$     $$$$\"\"\"\"\"\"\"\"       ",
         *l15 = "  \"\"\"\"       $$$$    \"$$$$$$$$$$$$$$$$$$$$$$$$$$$$\"      o$$$                ",
         *l16 = "             \"$$$o     \"\"\"$$$$$$$$$$$$$$$$$$\"$$\"         $$$                 ",
         *l17 = "               $$$o          \"$$\"\"$$$$$$\"\"\"\"           o$$$                  ",
         *l18 = "                $$$$o                                o$$$\"                   ",
         *l19 = "                 \"$$$$o      o$$$$$$o\"$$$$o        o$$$$                     ",
         *l20 = "                   \"$$$$$oo     \"\"$$$$o$$$$$o   o$$$$\"\"                      ",
         *l21 = "                      \"\"$$$$$oooo  \"$$$o$$$$$$$$$\"\"\"                         ",
         *l22 = "                         \"\"$$$$$$$oo $$$$$$$$$$                              ",
         *l23 = "                                 \"\"\"\"$$$$$$$$$$$                             ",
         *l24 = "                                     $$$$$$$$$$$$                            ",
         *l25 = "                                      $$$$$$$$$$\"                            ",
         *l26 = "                                       \"$$$\"\"                                ";

    int yCoord = 2;
    printCentre(l1, yCoord++);
    printCentre(l2, yCoord++);
    printCentre(l3, yCoord++);
    printCentre(l4, yCoord++);
    printCentre(l5, yCoord++);
    printCentre(l6, yCoord++);
    printCentre(l7, yCoord++);
    printCentre(l8, yCoord++);
    printCentre(l9, yCoord++);
    printCentre(l10, yCoord++);
    printCentre(l11, yCoord++);
    printCentre(l12, yCoord++);
    printCentre(l13, yCoord++);
    printCentre(l14, yCoord++);
    printCentre(l15, yCoord++);
    printCentre(l16, yCoord++);
    printCentre(l17, yCoord++);
    printCentre(l18, yCoord++);
    printCentre(l19, yCoord++);
    printCentre(l20, yCoord++);
    printCentre(l21, yCoord++);
    printCentre(l22, yCoord++);
    printCentre(l23, yCoord++);
    printCentre(l24, yCoord++);
    printCentre(l25, yCoord++);
    printCentre(l26, yCoord++);

    printCentre("Press [ ENTER ] to Continue", yCoord + 1);
    getchar();

}

void printHelp(int topic, bool show) {
    char topics[][16] = {
        "General",
        "Level Selection",
        "Gameplay",
        "Level Easy",
        "Level Medium",
        "Level Hard",
        "level Insane"
    };
    char topicsSelected[][22] = {
        ">> General",
        ">> Level Selection",
        ">> Gameplay",
        ">> Level Easy",
        ">> Level Medium",
        ">> Level Hard",
        ">> Level Insane"
    };

    char *helpGeneral = "Help\xCD\xCDGeneral",
         *helpLevelSelection = "Help\xCD\xCDLevel Selection",
         *helpGameplay = "Help\xCD\xCDGameplay",
         *helpLevelEasy = "Help\xCD\xCDLevel Easy",
         *helpLevelMedium = "Help\xCD\xCDLevel Medium",
         *helpLevelHard = "Help\xCD\xCDLevel Hard",
         *helpLevelInsane = "Help\xCD\xCDLevel Insane";

    double divider = 4;

     // Print box around window border

    /// Print top row
    for (int i = 0; i < getConsoleLen(); i++) {
        setCursorPosition(i, 0);
        if (i == 0) {
            printf("\xC9");
        } else if (i == getConsoleLen() - 1) {
            printf("\xBB");
        } else if (i == getConsoleLen() / divider) {
            printf("\xCB");
        } else {
            printf("\xCD");
        }
    }
    switch (topic) {
        case TOPIC_GENERAL:
            setCursorPosition((getConsoleLen() + (getConsoleLen() / divider)) / 2 - strlen(helpGeneral) / 2, 0);
            printf(helpGeneral);
            //printTopCentre("Help\xCD\xCDGeneral");
            break;
        case TOPIC_LEVEL_SELECTION:
            setCursorPosition((getConsoleLen() + (getConsoleLen() / divider)) / 2 - strlen(helpGeneral) / 2, 0);
            printf(helpLevelSelection);
            break;
        case TOPIC_GAMEPLAY:
            setCursorPosition((getConsoleLen() + (getConsoleLen() / divider)) / 2 - strlen(helpGeneral) / 2, 0);
            printf(helpGameplay);
            break;
        case TOPIC_LEVEL_EASY:
            setCursorPosition((getConsoleLen() + (getConsoleLen() / divider)) / 2 - strlen(helpGeneral) / 2, 0);
            printf(helpLevelEasy);
            break;
        case TOPIC_LEVEL_MEDIUM:
            setCursorPosition((getConsoleLen() + (getConsoleLen() / divider)) / 2 - strlen(helpGeneral) / 2, 0);
            printf(helpLevelMedium);
            break;
        case TOPIC_LEVEL_HARD:
            setCursorPosition((getConsoleLen() + (getConsoleLen() / divider)) / 2 - strlen(helpGeneral) / 2, 0);
            printf(helpLevelHard);
            break;
        case TOPIC_LEVEL_INSANE:
            setCursorPosition((getConsoleLen() + (getConsoleLen() / divider)) / 2 - strlen(helpGeneral) / 2, 0);
            printf(helpLevelInsane);
            break;
        default:
            break;
    }

    /// Print sides
    for (int i = 1; i < getConsoleHeight(); i++) {
        clearLine(i);
        printLeft("\xBA", i);
        printRight("\xBA", i);
        setCursorPosition(getConsoleLen() / divider, i);
        printf("\xBA");
        if (i == 4) {
            for (int j = 0; j != getConsoleLen() / divider + 1; j++) {
                //printLeft("\xCC\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB9", i);
                if (j == 0) {
                    printLeft("\xCC", 4);
                } else if (j == getConsoleLen() / divider) {
                    setCursorPosition(j, 4);
                    printf("\xB9");
                } else {
                    setCursorPosition(j, 4);
                    printf("\xCD");
                }
            }
        }
    }

    /// Print bottom row
    for (int i = 0; i < getConsoleLen(); i++) {
        setCursorPosition(i, getConsoleHeight() - 1);
        if (i == 0) {
            printf("\xC8");
        } else if (i == getConsoleLen() - 1) {
            printf("\xBC");
        } else if (i == getConsoleLen() / divider) {
            printf("\xCA");
        } else {
            printf("\xCD");
        }
    }
    setCursorPosition(0, 0);

    setCursorPosition((getConsoleLen() / divider) / 2 - strlen("Index") / 2, 3);
    printf("Index");

    short yCoord = 3;
    for (int i = 0; i < sizeof(topics) / sizeof(topics[0]); i++) {
        setCursorPosition((getConsoleLen() / divider) / 2 - strlen(topics[i]) / 2, yCoord += 3);
        if (i == topic) {
            printf(topicsSelected[i]);
        } else {
            printf(topics[i]);
        }
    }

    if (show) {
        // Show the contents of the selected menu item.

    } else {
        // Show general introduction to the welcome screen.

    }

}

/// EOF
