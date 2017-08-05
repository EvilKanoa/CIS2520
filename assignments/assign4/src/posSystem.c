/**
 * @file posSystem.c
 * @author Kanoa Haley - 0956712 - khaley@mail.uoguelph.ca
 * @date August 7, 2017
 * @brief File containing the main implementation for a POS system. It uses a 
 *        MVC pattern to run the application using the models and views found 
 *        in the other files.
 */

#include <stdio.h>
#include "posSystem.h"
#include "screens.h"

int main()
{
    State *state;
    int saveSuccess;

    state = createState();
    if (!loadGamesCsv(state->inventory, INVENTORY_FILE)) {
        destroyState(state);
        return 1;
    }

    while (nextView(state) != EXIT_VIEW);

    displayExit(state);
    saveSuccess = saveGamesCsv(state->inventory, INVENTORY_FILE) ? 0 : 1;

    destroyState(state);
    return saveSuccess;
}

State *createState()
{
    State *state = malloc(sizeof(State));
    state->inventory = createGamesCsv();
    state->invoice = createGamesCsv();
    state->search = malloc(sizeof(char) * VIEW_INPUT_BUFFER);
    state->buffer = malloc(sizeof(char) * VIEW_INPUT_BUFFER);
    state->view = MAIN_VIEW;
    state->clear = true;
    return state;
}

void destroyState(State *state)
{
    if (state == NULL) {
        return;
    }

    destroyGamesCsv(state->inventory);
    destroyGamesCsv(state->invoice);
    free(state->search);
    free(state->buffer);
    free(state);
}
