/**
 * @file posSystem.h
 * @author Kanoa Haley - 0956712 - khaley@mail.uoguelph.ca
 * @date August 7, 2017
 * @brief File containing the main definitions for a POS system. It uses a 
 *        MVC pattern to run the application using the models and views found 
 *        in the other files. Also contains the application state struct.
 */

#ifndef _POS_SYSTEM_
#define _POS_SYSTEM_

#include "gamesCsvModel.h"

/** The default inventory file */
#define INVENTORY_FILE "assets/Games.csv"
/** The buffer size for the search string */
#define VIEW_INPUT_BUFFER 2048

/**
 * This struct stores the correct application state.
 * Note: The state IS mutatable.
 */
typedef struct State {
    GamesCsvModel *model;
    char *search;
    char *buffer;
    int view;
    bool clear;
} State;

/**This function creates a new application state.
 *@return a freshly allocated state
 */
State *createState();

/**This function frees a state from memory.
 *@param state the application state to free
 */
void destroyState(State *state);

#endif
