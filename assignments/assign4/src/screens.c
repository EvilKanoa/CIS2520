/**
 * @file screens.c
 * @author Kanoa Haley - 0956712 - khaley@mail.uoguelph.ca
 * @date August 7, 2017
 * @brief File containing the implementation for the user screens/views in the POS
 *        system.
 */

#include <stdio.h>
#include <stdlib.h>
#include "screens.h"

View nextView(State *state)
{
    if (state->clear) {
        clearScreen();
    }

    switch (state->view) {
        case MAIN_VIEW:
            state->view = displayMain(state);
            break;
        case SEARCH_VIEW:
            state->view = displaySearch(state);
            break;
        case INVENTORY_VIEW:
            state->view = displayInventory(state);
            break;
        case REMOVE_VIEW:
            state->view = displayRemove(state);
            break;
        case ADD_VIEW:
            state->view = displayAdd(state);
            break;
        case INVOICE_VIEW:
            state->view = displayInvoice(state);
            break;
        default:
            state->view = EXIT_VIEW;
    }

    return state->view;
}

View displayMain(State *state)
{
    int choice;

    printf("\n\n--- POS SYSTEM ---\n");
    printf("--- Main  Menu ---\n");
    printf("1. Search Products\n");
    printf("2. Display All Products\n");
    printf("3. Remove a Product\n");
    printf("4. Add Product to Invoice\n");
    printf("5. Print Customer Invoice\n");
    printf("6. Exit\n");

    do {
        printf("Enter an option (1-6): ");
        choice = getIntInput(state);
    } while (choice < 1 || choice > 6);

    state->clear = false;

    switch (choice) {
        case 1:
            return SEARCH_VIEW;
        case 2:
            return INVENTORY_VIEW;
        case 3:
            return REMOVE_VIEW;
        case 4:
            return ADD_VIEW;
        case 5:
            return INVOICE_VIEW;
        case 6:
            return EXIT_VIEW;
    }

    return MAIN_VIEW;
}

View displaySearch(State *state)
{
    printf("search\n");
    return MAIN_VIEW;
}

View displayExit(State *state)
{
    printf("Saving and exiting POS system...\n");

    return EXIT_VIEW;
}

View displayInventory(State *state)
{
    printf("inventory\n");
    return MAIN_VIEW;
}

View displayRemove(State *state)
{
    printf("remove\n");
    return MAIN_VIEW;
}

View displayAdd(State *state)
{
    printf("add\n");
    return MAIN_VIEW;
}

View displayInvoice(State *state)
{
    printf("invoice\n");
    return MAIN_VIEW;
}

void clearScreen()
{
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

int getIntInput(State *state)
{
    getStringInput(state);
    return atoi(state->buffer);
}

char *getStringInput(State *state)
{
    size_t length;

    fgets(state->buffer, VIEW_INPUT_BUFFER, stdin);

    if (state->buffer == NULL) {
        state->buffer = "";
        return NULL;
    }

    length = strlen(state->buffer);
    if (state->buffer[length - 1] == '\n') {
        state->buffer[length - 1] = 0;
    }

    return state->buffer;
}
