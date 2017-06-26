/**
 * @file vault.c
 * @author Kanoa Haley - 0956712 - khaley@mail.uoguelph.ca
 * @date June 24, 2017
 * @brief File containing the implemention for the vault application including its main method. Mostly used for the UI.
 */

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "VaultUtilities.h"
#include "VaultFile.h"

#define CONFIG_FILE "config.txt"

int main()
{
    initscr();
    noecho();

    printw("Hello, World!");
    refresh();
    getch();

    endwin();
    return 0;
}
