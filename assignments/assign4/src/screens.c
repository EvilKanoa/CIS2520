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

View displayMain(State *state)
{
    printf("MAIN MENU\n");
    treeInOrderPrint(state->model->tree, printGameModel);

    return SEARCH_VIEW;
}

View displaySearch(State *state)
{
    printf("Search view :)...\n");

    return EXIT_VIEW;
}

View displayExit(State *state)
{
    printf("Saving and exiting POS system...\n");

    return EXIT_VIEW;
}
