/**
 * @file gamesCsvModel.c
 * @author Kanoa Haley - 0956712 - khaley@mail.uoguelph.ca
 * @date August 7, 2017
 * @brief File containing the implementations for the games data type based
 *        off the assets/Games.csv file as well as the logic to load and save the
 *        structure from/to disk.
 */

#include "gamesCsvModel.h"

GamesCsvModel *createGamesCsv(char *fileName)
{
    GamesCsvModel *model;

    if (fileName == NULL) {
        return NULL;
    }

    model = malloc(sizeof(GamesCsvModel));
    model->tree = createBalancedBinTree(gameKeyCompare, destroyGameModel, copyGameModel);

    if (model->tree == NULL) {
        free(model);
        return NULL;
    }

    model->count = 0;
    model->fileName = fileName;

    return model;
}

GameModel *createGameModel(char *productId, char *name, char *publisher, char *genre, bool taxable, float price, int quantity)
{
    GameModel *model;

    if (productId == NULL || strlen(productId) == 0) {
        return NULL;
    }

    model = malloc(sizeof(GameModel));
    model->key = *createGameKey(productId);
    model->productId = productId;
    model->name = name;
    model->publisher = publisher;
    model->genre = genre;
    model->taxable = taxable;
    model->price = price;
    model->quantity = quantity;

    return model;
}

GameKey *createGameKey(char *productId)
{
    GameKey *key;
    int length;

    if (productId == NULL) {
        return NULL;
    }

    key = malloc(sizeof(GameKey));
    length = strlen(productId);
    key->productId = malloc((sizeof(char) * length) + 1);
    strncpy(key->productId, productId, length);
    key->productId[strlen(productId)] = 0;

    return key;
}

/**This function loads a gamesCsvModel from a CSV file.
 *@param fileName the csv file with game data
 *@return a newly allocated and filled gamesCsvModel
 */
GamesCsvModel *loadGamesCsv(char *fileName)
{
    return NULL;
}

/**This functions saves a gamesCsvModel to a csv file as specified within the model.
 *@param model the data to save
 *@return whether saving was successful
 */
bool saveGamesCsv(GamesCsvModel *model)
{
    return false;
}

/**This function adds a new game to a gamesCsvModel.
 *@param model the model to add the game to.
 *@param productId Product ID of the game
 *@param name Name of the game
 *@param publisher Publisher of the game
 *@param genre Genre of the game
 *@param taxable Whether to tax the game
 *@param price The price of the game in dollars
 *@param quantity The number of games in stock
 */
void addGameToModel(GamesCsvModel *model, char *productId, char *name, char *publisher, char *genre, bool taxable, float price, int quantity)
{
    return;
}

/**This function removes a number of games from the inventory of a gamesCsvModel.
 *@param model the inventory model
 *@param productId the product to remove
 *@param count the number to remove
 */
void removeGameFromModel(GamesCsvModel *model, char *productId, int count)
{
    return;
}

/**This function retrieves a gameModel from a gamesCsvModel based on a product id.
 *@param model the data to look for the gameModel in
 *@param productId the product id to search for
 *@return a gameModel if found or NULL if it does not exist
 */
GameModel *lookupGameFromModel(GamesCsvModel *model, char *productId)
{
    return NULL;
}

/**This function checks if a gamesCsvModel contains a gameModel based on a product id with enough quantity.
 *@param model the data to look in
 *@param productId the product id to look for
 *@param count the minimum number for quantity
 */
bool containsGameFromModel(GamesCsvModel *model, char *productId, int count)
{
    return false;
}

/**This function retrieves the quantity of games in a gamesCsvModel
 *@param model the data to look in
 *@param productId the product id to look for
 */
int numGameFromModel(GamesCsvModel *model, char *productId)
{
    return 0;
}

int gameKeyCompare(void *key1, void *key2)
{
    if (key1 == NULL) {
        return -1;
    } else if (key2 == NULL) {
        return 1;
    } else {
        return strcmp((*((GameKey *) key1)).productId, (*((GameKey *) key2)).productId);
    }
}

void destroyGameModel(void *modelPtr)
{
    GameModel *model;

    if (modelPtr == NULL) {
        return;
    }

    model = (GameModel *) modelPtr;
    free(model->key.productId);
    free(model->productId);
    free(model->name);
    free(model->publisher);
    free(model->genre);
    free(model);
}

void *copyGameModel(void *modelPtr)
{
    GameModel *model;

    if (modelPtr == NULL) {
        return NULL;
    }

    model = (GameModel *) modelPtr;

    return createGameModel(model->productId, model->name, model->publisher, model->genre, model->taxable, model->price, model->quantity);
}
