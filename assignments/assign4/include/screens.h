/**
 * @file screens.h
 * @author Kanoa Haley - 0956712 - khaley@mail.uoguelph.ca
 * @date August 7, 2017
 * @brief File containing the definitions for the user screens/views in the POS
 *        system.
 */

#ifndef _SCREENS_
#define _SCREENS_

/**Views that can be displayed during the program.
 * These views are populated according to the current state.
 */
#define MAIN_VIEW 1
#define EXIT_VIEW 2
#define SEARCH_VIEW 3
typedef int View;

#include "posSystem.h"

/**UI function to display and interact with the user on a main menu.
 *@param state the current state of the POS system
 *@return the next view to display
 */
View displayMain(State *state);

/**UI function to display and interact with the user on a search page.
 *@param state the current state of the POS system
 *@return the next view to display
 */
View displaySearch(State *state);

/**UI function to print any information before exiting.
 *@param state the current state of the POS system
 *@return the next view to display (not used for exits)
 */
View displayExit(State *state);

#endif
