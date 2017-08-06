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
        case LOAD_VIEW:
            state->view = displayLoad(state);
            break;
        default:
            state->view = EXIT_VIEW;
    }

    return state->view;
}

View displayMain(State *state)
{
    int choice;

    printf("\n--- POS SYSTEM ---\n");
    printf("--- Main  Menu ---\n");
    printf("1. Search Products\n");
    printf("2. Display All Products\n");
    printf("3. Remove a Product\n");
    printf("4. Add Product to Invoice\n");
    printf("5. Print Customer Invoice\n");
    printf("6. Load Inventory File to Current\n");
    printf("7. Exit\n");

    do {
        printf("Enter an option (1-7): ");
        choice = getIntInput(state);
    } while (choice < 1 || choice > 7);

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
            return LOAD_VIEW;
        case 7:
            return EXIT_VIEW;
    }

    return MAIN_VIEW;
}

View displaySearch(State *state)
{
    char *input;
    List *search;

    printf("--- Search Inventory ---\n");
    printf("Enter a search term (searches by name): ");

    input = getStringInput(state);
    search = searchByName(state->inventory, input);

    search->printData = printInventoryItem;
    printf("\n\n--- Results ---\n");
    printForward(search);

    deleteList(search);
    state->clear = false;

    return MAIN_VIEW;
}

View displayExit(State *state)
{
    clearScreen();
    printf("Saving and exiting POS system...\n");

    return EXIT_VIEW;
}

View displayInventory(State *state)
{
    clearScreen();
    printf("--- Current Inventory ---\n");
    treeInOrderPrint(state->inventory->tree, printInventoryItem);
    state->clear = false;

    return MAIN_VIEW;
}

View displayRemove(State *state)
{
    GameModel *item;
    char *input;

    printf("--- Remove All from Inventory ---\n");

    do {
        printf("Item's product ID: ");
        input = getStringInput(state);

        item = lookupGameFromModel(state->inventory, input);
        if (item == NULL) {
            printf("Unable to find an item by that ID!\n");
            printf("Enter 'x' to exit to the main menu or try again.\n");
        }
    } while (item == NULL && strcmp(input, "x") != 0);

    if (item == NULL) {
        state->clear = true;
        return MAIN_VIEW;
    }

    clearScreen();
    removeGameFromModel(state->inventory, item->productId, item->quantity);
    printf("Removed from inventory.\n");

    return MAIN_VIEW;
}

View displayAdd(State *state)
{
    GameModel *item;
    char *input;
    int quantity;

    printf("--- Add to Invoice ---\n");

    do {
        printf("Item's product ID: ");
        input = getStringInput(state);

        item = lookupGameFromModel(state->inventory, input);
        if (item == NULL) {
            printf("Unable to find an item by that ID!\n");
            printf("Enter 'x' to exit to the main menu or try again.\n");
        }
    } while (item == NULL && strcmp(input, "x") != 0);

    if (item == NULL) {
        state->clear = true;
        return MAIN_VIEW;
    }

    printf("\n");
    printf("Game: %s (%s)\n", item->name, item->productId);
    printf("Quantity: %d\n", item->quantity);

    do {
        printf("Purchase quantity (0 - %d): ", item->quantity);
        quantity = getIntInput(state);

        if (quantity > item->quantity) {
            printf("Not enough items in inventory\n");
        }
    } while (quantity < 0 || quantity > item->quantity);

    if (quantity == 0) {
       state->clear = true;
       return MAIN_VIEW;
    }

    addGameToModel(state->invoice, item->productId, item->name, item->publisher,
        item->genre, item->taxable, item->price, quantity);
    removeGameFromModel(state->inventory, item->productId, quantity);

    clearScreen();
    printf("Added %d %s of %s to invoice.\n", quantity,
        quantity > 1 ? "copies" : "copy", item->name);

    state->clear = false;

    return MAIN_VIEW;
}

View displayInvoice(State *state)
{
    List *taxed = getTaxed(state->invoice);
    List *nontaxed = getNontaxed(state->invoice);
    float taxTotal = calculateGamesListTotal(taxed) * 1.13;
    float nontaxTotal = calculateGamesListTotal(nontaxed);

    clearScreen();
    printf("--- Customer Invoice ---\n");
    printf("\nTaxed Items\n-----------\n");
    taxed->printData = printInvoiceItem;
    printForward(taxed);
    printf("\nTaxed Subtotal:\t%.2f\n", taxTotal);

    printf("\nNon-Taxed Items\n---------------\n");
    nontaxed->printData = printInvoiceItem;
    printForward(nontaxed);
    printf("\nNon-Taxed Subtotal:\t%.2f\n", nontaxTotal);

    printf("\nTotal:\t%.2f\n", taxTotal + nontaxTotal);

    printf("\nPress enter to clear.\n");
    getchar();

    deleteList(taxed);
    deleteList(nontaxed);
    destroyGamesCsv(state->invoice);
    state->invoice = createGamesCsv();
    state->clear = true;

    return MAIN_VIEW;
}

View displayLoad(State *state)
{
    char *input;

    printf("--- Load New Inventory File ---\n");
    printf("\nEnter the file name you wish to load: ");
    input = getStringInput(state);

    if (loadGamesCsv(state->inventory, input)) {
        printf("%s successfully loaded into current inventory!\n", input);
    } else {
        printf("Failed to load %s.\n", input);
    }

    state->clear = false;

    return MAIN_VIEW;
}

void clearScreen()
{
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\
        \n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\
        \n\n\n\n\n\n\n\n\n\n\n\n\n");
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
    }

    length = strlen(state->buffer);
    if (state->buffer[length - 1] == '\n') {
        state->buffer[length - 1] = 0;
    }

    return state->buffer;
}

void printInventoryItem(void *modelPtr)
{
    GameModel *model;

    if (modelPtr == NULL) {
        return;
    }

    model = (GameModel *) modelPtr;
    printf("Name: %s\n", model->name);
    printf("Product ID: %s\n", model->productId);
    printf("Publisher(s): %s\n", model->publisher);
    printf("Genre(s): %s\n", model->genre);
    printf("%s\n", model->taxable ? "Taxed" : "No Tax");
    printf("Price: $%.2f\n", model->price);
    printf("Quantity Available: %d\n", model->quantity);
    printf("\n");
}

void printInvoiceItem(void *modelPtr)
{
    GameModel *model;

    if (modelPtr == NULL) {
        return;
    }

    model = (GameModel *) modelPtr;

    if (model->taxable) {
        printf("\nName:\t\t%s\nPrice:\t\t%.2f\nQuantity:\t%d\nSubtotal:\t%.2f\nTax:\t\t%.2f\nTotal:\t\t%.2f\n", 
            model->name, model->price, model->quantity, 
            model->price * model->quantity,
            model->price * model->quantity * 0.13,
            model->price * model->quantity * 1.13);
    } else {
        printf("\nName:\t\t%s\nPrice:\t\t%.2f\nQuantity:\t%d\nTotal:\t\t%.2f\n", 
            model->name, model->price, model->quantity, 
            model->price * model->quantity);
    }
}

float calculateGamesListTotal(List *list)
{
    Node *node;
    GameModel *model;
    float total = 0;

    if (list == NULL) {
        return total;
    }

    node = list->head;
    while (node != NULL) {
        model = (GameModel *) node->data;
        total += (model->price * model->quantity);
        node = node->next;
    }

    return total;
}
