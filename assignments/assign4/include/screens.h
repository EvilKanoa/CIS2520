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
#define INVENTORY_VIEW 4
#define REMOVE_VIEW 5
#define ADD_VIEW 6
#define INVOICE_VIEW 7
typedef int View;

#include "posSystem.h"

/**Function to display the next view requested.
 *@param state the current state of the POS system
 *@return the next view to display
 */
View nextView(State *state);

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

/**UI function to print the entire inventory.
 *@param state the current state of the POS system
 *@return the next view to display (not used for exits)
 */
View displayInventory(State *state);

/**UI function to display and interact to remove an item.
 *@param state the current state of the POS system
 *@return the next view to display (not used for exits)
 */
View displayRemove(State *state);

/**UI function to display and interact add an item to the current invoice.
 *@param state the current state of the POS system
 *@return the next view to display (not used for exits)
 */
View displayAdd(State *state);

/**UI function to print and clear the current invoice.
 *@param state the current state of the POS system
 *@return the next view to display (not used for exits)
 */
View displayInvoice(State *state);

/**Function to print newlines to gime the impression of a cleared screen.
 */
void clearScreen();

/**Function to get an integer input from the user.
 *@param state the current state of the POS system
 *@return the number to user entered. If unable to parse, 0
 */
int getIntInput(State *state);

/**Function to get a string input from the user.
 *@param state the current state of the POS system
 *@return the input string (also in state->buffer)
 */
char *getStringInput(State *state);

#endif
