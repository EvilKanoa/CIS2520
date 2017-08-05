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
    if (!loadGamesCsv(state->model, INVENTORY_FILE)) {
        destroyState(state);
        return 1;
    }

    while (state->view != EXIT_VIEW) {
        switch (state->view) {
            case MAIN_VIEW:
                state->view = displayMain(state);
                break;
            case SEARCH_VIEW:
                state->view = displaySearch(state);
                break;
        }
    }

    displayExit(state);
    saveSuccess = saveGamesCsv(state->model, INVENTORY_FILE) ? 0 : 1;

    destroyState(state);
    return saveSuccess;
}

State *createState()
{
    State *state = malloc(sizeof(State));
    state->model = createGamesCsv();
    state->search = malloc(sizeof(char) * SEARCH_BUFFER);
    state->view = MAIN_VIEW;
    return state;
}

void destroyState(State *state)
{
    if (state == NULL) {
        return;
    }

    destroyGamesCsv(state->model);
    free(state->search);
    free(state);
}
