/**
 * @file vault.c
 * @author Kanoa Haley - 0956712 - khaley@mail.uoguelph.ca
 * @date June 24, 2017
 * @brief File containing the implemention for the vault application including its main method. Mostly used for the UI.
 */

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <signal.h>
#include "VaultUtilities.h"
#include "VaultFile.h"

#define CONFIG_FILE "config.txt"
#define ARROW "->"
#define arrow(x) x ? ARROW : ""

/**
 * UI Function
 * Displays the main menu with arrow key navigation implementing program operations
 */
void displayMainMenu();

/**
 * UI Function
 * Displays the login window and lets the user enter their current password, or, if none exist, enter a new password
 */
void displayLogin();

/**
 * UI Function
 * Displays the window to input a vault file
 *@returns The vault data if correct name or null data if the name is incorrect
 *@param vault The previous vault struct
 */
Vault *displayOpenVault(Vault *vault);

/**
 * UI Function
 * Displays the UI to retrieve a password based upon a descriptor
 */
void displayGetPassword(Vault *vault);

/**
 * UI Function
 * Displays the UI to add a password via a descriptor
 */
void displayAddPassword(Vault *vault);

/**
 * UI Function
 * Displays the UI to remove a password based upon a descriptor
 */
void displayRemovePassword(Vault *vault);

/**
 * UI Function
 * Displays the UI to update a password given a descriptor and new password
 */
void displayUpdatePassword(Vault *vault);

/**
 * Causes the application to exit gracefully
 */
void finish();

int main()
{
    /* setup environment */
    signal(SIGINT, finish);
    initscr();
    keypad(stdscr, TRUE);
    noecho();

    displayLogin();
    displayMainMenu();
    
    finish();
}

void displayMainMenu()
{
    /* program variables */
    Vault *vault = malloc(sizeof(Vault));
    char buffer[BUFFER_SIZE];
    int input;
    int listPos = 0;

    while (1) {
        /* print the menu */
        noecho();
        clear();
        printw("Password Vault (Q to save and exit)");
        mvprintw(1, 0, "Selected File: %s", vault == NULL ? "None" : vault->data == NULL ? "Could not load" : vault->fileName);
        mvprintw(3, 0, "Main Menu (Use Up/Down & Enter): ");
        mvprintw(4, 0, "%s\tOpen vault file", arrow(listPos == 0));
        mvprintw(5, 0, "%s\tUpdate master password", arrow(listPos == 1));
        mvprintw(6, 0, "%s\tGet password", arrow(listPos == 2));
        mvprintw(7, 0, "%s\tAdd password", arrow(listPos == 3));
        mvprintw(8, 0, "%s\tRemove password", arrow(listPos == 4));
        mvprintw(9, 0, "%s\tUpdate password", arrow(listPos == 5));
        mvprintw(10, 0, "%s\tSave and exit", arrow(listPos == 6));
        move(2, 0);
        refresh();

        /* get input and perform actions */
        input = getch();
        if (input == KEY_UP && listPos > 0) {
            listPos--;
        } else if (input == KEY_DOWN && listPos < 6) {
            listPos++;
        } else if (input == 'Q' || input == 'q' || (input == '\n' && listPos == 6)) {
            saveVault(vault->data, vault->fileName);
            return;
        } else if (input == '\n') {
            switch (listPos) {
                case 0:
                    saveVault(vault->data, vault->fileName);
                    vault = displayOpenVault(vault);
                    break;
                case 1:
                    clear();
                    echo();
                    printw("New master password: ");
                    refresh();
                    getnstr(buffer, BUFFER_SIZE - 1);
                    savePassword(CONFIG_FILE, buffer);
                    break;
                case 2:
                    displayGetPassword();
                    break;
                case 3:
                    displayAddPassword();
                    break;
                case 4:
                    displayRemovePassword();
                    break;
                case 5:
                    displayUpdatePassword();
                    break;
            }
        }
    }
}

void displayLogin()
{
    char *password = getPassword(CONFIG_FILE);
    char input[BUFFER_SIZE] = "";
    int isNew = password == NULL;
    
    do {
        clear();
        echo();
        printw("Vault Login");
        move(1, 0);
        if (strcmp(input, "") != 0) {
            printw("Incorrect master password!");
            move(2, 0);
        }
        printw(isNew ? "Enter a new master password for vault access: " : "Enter your vault master password: ");
        refresh();
        getnstr(input, BUFFER_SIZE - 1);
    } while (password != NULL && strcmp(password, input) != 0);

    savePassword(CONFIG_FILE, input);
}

Vault *displayOpenVault(Vault *vault)
{
    char input[BUFFER_SIZE];
    if (vault->fileName != NULL) {
        free(vault->fileName);
    }

    clear();
    echo();
    printw("Password Vault Selection");
    mvprintw(1, 0, "Enter a password vault file: ");
    getnstr(input, BUFFER_SIZE - 1);

    stripNewline(input);
    vault->fileName = malloc(sizeof(char) * (strlen(input) + 1));
    strcpy(vault->fileName, input);
    vault->data = loadVault(vault->fileName);
    return vault;
}

void displayGetPassword(Vault *vault)
{

}

void displayAddPassword(Vault *vault)
{

}

void displayRemovePassword(Vault *vault)
{

}

void displayUpdatePassword(Vault *vault)
{

}

void finish()
{
    endwin();
    exit(0);
}