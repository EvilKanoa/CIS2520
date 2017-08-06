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
    model->tree = createBalancedBinTree(gameKeyCompare, destroyGameModel, 
        copyGameModel);

    if (model->tree == NULL) {
        free(model);
        return NULL;
    }

    return model;
}

void destroyGamesCsv(GamesCsvModel *model)
{
    if (model == NULL) {
        return;
    }

    destroyBalancedBinTree(model->tree);
    free(model);
}

GameModel *createGameModel(char *productId, char *name, char *publisher, 
    char *genre, bool taxable, float price, int quantity)
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

bool loadGamesCsv(GamesCsvModel *model, char *fileName)
{
    FILE *fp = fileName == NULL ? NULL : fopen(fileName, "r");
    char buffer[INPUT_BUFFER];
    float priceF;

    char *productId, *name, *publisher, *genre, *taxable, *price, *quantity;

    if (fp == NULL || model == NULL) {
        return false;
    }

    while (fgets(buffer, INPUT_BUFFER, fp) != NULL) {
        if (strncmp(CSV_HEADER, buffer, strlen(CSV_HEADER)) == 0) {
            continue;
        }

        productId = strtokEmpty(buffer, CSV_DELIM);
        name = strtokEmpty(NULL, CSV_DELIM);
        publisher = strtokEmpty(NULL, CSV_DELIM);
        genre = strtokEmpty(NULL, CSV_DELIM);
        taxable = strtokEmpty(NULL, CSV_DELIM);
        price = strtokEmpty(NULL, CSV_DELIM);
        quantity = strtokEmpty(NULL, CSV_DELIM);
        if (productId == NULL) {
            continue;
        }

        if (price != NULL && strlen(price) > 0) {
            priceF = (float) atof(price + 1);
        } else {
            priceF = 0;
        }
        if (taxable == NULL) {
            taxable = "0";
        }
        if (quantity == NULL) {
            quantity = "0";
        }

        addGameToModel(model, productId, name, publisher, genre, 
            (char) atoi(taxable), priceF, atoi(quantity));
    }

    fclose(fp);
    return true;
}

bool saveGamesCsv(GamesCsvModel *model, char *fileName)
{
    bool success;
    FILE *fp = model == NULL ? NULL : fopen(fileName, "w");

    if (fp == NULL) {
        return false;
    }

    fprintf(fp, "%s\n", CSV_HEADER);
    success = gameInOrderPrint(fp, model->tree->root);

    fclose(fp);

    return success;
}

bool gameInOrderPrint(FILE *fp, TreeNode *node)
{
    GameModel *game;
    bool success;

    if (fp == NULL || node == NULL || node->data == NULL) {
        return fp != NULL && (node == NULL || node->data != NULL);
    }

    game = (GameModel *) node->data;

    success = gameInOrderPrint(fp, node->left);
    success = success && (fprintf(fp, "%s,%s,%s,%s,%s,$%.2f,%i\n", 
        game->productId, game->name, game->publisher, game->genre, 
        game->taxable ? "1" : "0", game->price, 
        game->quantity) > 0);
    success = success && gameInOrderPrint(fp, node->right);

    return success;
}

void addGameToModel(GamesCsvModel *model, char *productId, char *name, 
    char *publisher, char *genre, bool taxable, float price, int quantity)
{
    if (model == NULL || productId == NULL || strlen(productId) == 0 || quantity < 1) {
        return;
    }

    if (containsGameFromModel(model, productId, 1)) {
        lookupGameFromModel(model, productId)->quantity += quantity;
    } else {
        treeInsertNode(model->tree, createGameModel(productId, name, publisher, 
            genre, taxable, price, quantity));
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

List *searchByName(GamesCsvModel *model, char *search)
{
    List *list;

    if (model == NULL || search == NULL) {
        return NULL;
    }

    list = initializeList(NULL, deleteNothing, gameModelNameCompare);
    recursiveSearch(list, model->tree->root, search);

    return list;
}

void recursiveSearch(List *list, TreeNode *root, char *search)
{
    GameModel *model;

    if (root == NULL || search == NULL) {
        return;
    }

    recursiveSearch(list, root->left, search);

    model = (GameModel *) root->data;
    if (strcasestr(model->name, search) != NULL) {
        insertSorted(list, model);
    }

    recursiveSearch(list, root->right, search);
}

int gameKeyCompare(void *key1, void *key2)
{
    if (key1 == NULL && key2 == NULL) {
        return 0;
    } else if (key1 == NULL) {
        return -1;
    } else if (key2 == NULL) {
        return 1;
    } else {
        return strcmp((*((GameKey *) key1)).productId, 
            (*((GameKey *) key2)).productId);
    }
}

int gameModelNameCompare(const void *key1, const void *key2)
{
    if (key1 == NULL && key2 == NULL) {
        return 0;
    } else if (key1 == NULL) {
        return -1;
    } else if (key2 == NULL) {
        return 1;
    } else {
        return strcmp(((GameModel *) key1)->name, ((GameModel *) key2)->name);
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

    return createGameModel(model->productId, model->name, model->publisher, 
        model->genre, model->taxable, model->price, model->quantity);
}

void printGameModel(void *modelPtr)
{
    GameModel *game = (GameModel *) modelPtr;
    if (modelPtr != NULL && game != NULL) {
        printf("%s, %s, %s, %s, %s, $%.2f, %i\n", game->productId, game->name, 
            game->publisher, game->genre, 
            game->taxable ? "Taxable" : "Non-taxable", game->price, 
            game->quantity);
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

char *strtokEmpty(char *str, char const *delim)
{
    static char *full = NULL;
    char *ptr;
    char *result = 0;

    if (str != NULL) {
        full = str;
    } else if (full == NULL) {
        return NULL;
    }

    ptr = strpbrk(full, delim);
    if (ptr != NULL) {
        *ptr = 0;
        result = full;
        full = ++ptr;
    } else if (*full) {
        result = full;
        full = NULL;
    }

    return result;
}

void deleteNothing(void *toBeDeleted)
{
    return;
}
