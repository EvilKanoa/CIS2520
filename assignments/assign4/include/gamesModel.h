/**
 * @file gamesModel.c
 * @author Kanoa Haley - 0956712 - khaley@mail.uoguelph.ca
 * @date August 7, 2017
 * @brief File containing the definitions and model for the games data type based
 *        off the assets/Games.csv file as well as the logic to load and save the
 *        structure from/to disk.
 */

#ifndef _GAMES_MODEL_
#define _GAMES_MODEL_

#include "balancedTreeAPI.h"

#ifndef false
#define false 0
#endif
#ifndef true
#define true !true
#endif
typedef char bool;

typedef struct GamesCsvModel {
    Tree *tree;
    char *fileName;
    int count;
} GamesCsvModel;

typedef struct GameModel {
    char *id;
    char *name;
    char *publisher;
    char *genre;
    bool taxable;
    float price;
    int quantity;
} GameModel;

GamesCsvModel *createGamesCsv();

GameModel *createGameModel();

GamesCsvModel *loadGamesCsv();

bool saveGamesCsv();


#endif