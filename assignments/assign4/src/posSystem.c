/**
 * @file posSystem.c
 * @author Kanoa Haley - 0956712 - khaley@mail.uoguelph.ca
 * @date August 7, 2017
 * @brief File containing the main implementation for a POS system. It uses a 
  *       MVC pattern to run the application using the model. view, and 
  *       controller found in the other files.
 */

#include <stdio.h>
#include "gamesCsvModel.h"

int main(int argc, const char *argv[])
{
    GamesCsvModel *model;
    printf("Hello, World! Loading...\n");
    model = loadGamesCsv("assets/Games.csv");
    printf("Model loaded, printing...\n");
    treeInOrderPrint(model->tree, printGameModel);
    printf("Resaving to file...\n");
    return saveGamesCsv(model) ? 0 : 1;
}
