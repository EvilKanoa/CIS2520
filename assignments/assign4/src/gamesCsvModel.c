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

    model->fileName = copyString(fileName);

    return model;
}

void destroyGamesCsv(GamesCsvModel *model)
{
    if (model == NULL) {
        return;
    }

    destroyBalancedBinTree(model->tree);
    free(model->fileName);
    free(model);
}

GameModel *createGameModel(char *productId, char *name, char *publisher, char *genre, bool taxable, float price, int quantity)
{
    GameModel *model;

    if (productId == NULL || strlen(productId) == 0) {
        return NULL;
    }

    model = malloc(sizeof(GameModel));
    model->key = *createGameKey(productId);
    model->productId = copyString(productId);
    model->name = copyString(name);
    model->publisher = copyString(publisher);
    model->genre = copyString(genre);
    model->taxable = taxable;
    model->price = price;
    model->quantity = quantity;

    return model;
}

GameKey *createGameKey(char *productId)
{
    GameKey *key;

    if (productId == NULL) {
        return NULL;
    }

    key = malloc(sizeof(GameKey));
    key->productId = copyString(productId);

    return key;
}

void destroyGameKey(GameKey *key)
{
    if (key == NULL) {
        return;
    }

    free(key->productId);
    free(key);
}

GamesCsvModel *loadGamesCsv(char *fileName)
{
    FILE *fp = fileName == NULL ? NULL : fopen(fileName, "r");
    GamesCsvModel *model;
    char buffer[INPUT_BUFFER];
    float priceF;

    char *productId, *name, *publisher, *genre, *taxable, *price, *quantity;

    if (fp == NULL) {
        return NULL;
    }

    model = createGamesCsv(fileName);

    while (fgets(buffer, INPUT_BUFFER, fp) != NULL) {
        if (strncmp(CSV_HEADER, buffer, strlen(CSV_HEADER)) == 0) {
            continue;
        }

        productId = strtok(buffer, CSV_DELIM);
        name = strtok(NULL, CSV_DELIM);
        publisher = strtok(NULL, CSV_DELIM);
        genre = strtok(NULL, CSV_DELIM);
        taxable = strtok(NULL, CSV_DELIM);
        price = strtok(NULL, CSV_DELIM);
        quantity = strtok(NULL, CSV_DELIM);
        if (productId == NULL || name == NULL || publisher == NULL || genre == NULL || taxable == NULL || price == NULL || quantity == NULL) {
            continue;
        }
        if (price != NULL && strlen(price) > 0) {
            priceF = (float) atof(price + 1);
        } else {
            priceF = 0;
        }

        addGameToModel(model, productId, name, publisher, genre, (char) atoi(taxable), priceF, atoi(quantity));
    }

    return model;
}

/**This functions saves a gamesCsvModel to a csv file as specified within the model.
 *@param model the data to save
 *@return whether saving was successful
 */
bool saveGamesCsv(GamesCsvModel *model)
{
    return false;
}

void addGameToModel(GamesCsvModel *model, char *productId, char *name, char *publisher, char *genre, bool taxable, float price, int quantity)
{
    if (model == NULL || productId == NULL || strlen(productId) == 0) {
        return;
    }

    if (containsGameFromModel(model, productId, 1)) {
        lookupGameFromModel(model, productId)->quantity += quantity  ;
    } else {
        treeInsertNode(model->tree, createGameModel(productId, name, publisher, genre, taxable, price, quantity));
    }
}

void removeGameFromModel(GamesCsvModel *model, char *productId, int count)
{
    GameModel *game;

    if (model == NULL || productId == NULL || strlen(productId) == 0 || count < 1) {
        return;
    }

    game = lookupGameFromModel(model, productId);
    if (game == NULL) {
        return;
    } else if (game->quantity <= count) {
        treeDeleteNode(model->tree, game);
    } else {
        game->quantity -= count;
    }
}

GameModel *lookupGameFromModel(GamesCsvModel *model, char *productId)
{
    GameKey *key;
    GameModel *game;

    if (model == NULL || productId == NULL || strlen(productId) == 0) {
        return NULL;
    }

    key = createGameKey(productId);
    game = treeFindNode(model->tree, key);
    destroyGameKey(key);

    return game;
}

bool containsGameFromModel(GamesCsvModel *model, char *productId, int count)
{
    return numGameFromModel(model, productId) >= count;
}

int numGameFromModel(GamesCsvModel *model, char *productId)
{
    GameModel *game;

    if (model == NULL || productId == NULL || strlen(productId) == 0) {
        return false;
    }

    game = lookupGameFromModel(model, productId);
    return game == NULL ? 0 : game->quantity;
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

void printGameModel(void *modelPtr)
{
    GameModel *game = (GameModel *) modelPtr;
    if (modelPtr != NULL && game != NULL) {
        printf("%s, %s, %s, %s, %s, $%.2f, %i\n", game->productId, game->name, game->publisher, game->genre, game->taxable ? "Taxable" : "Non-taxable", game->price, game->quantity);
    }
}

char *copyString(char *src)
{
    char *str;
    unsigned long length;

    if (src == NULL) {
        return NULL;
    }

    length = strlen(src);
    str = malloc(sizeof(char) * (length + 1));
    strncpy(str, src, length);
    str[length] = 0;

    return str;
}
