/**
 * @file gamesCsvModel.h
 * @author Kanoa Haley - 0956712 - khaley@mail.uoguelph.ca
 * @date August 7, 2017
 * @brief File containing the definitions and model for the games data type based
 *        off the assets/Games.csv file as well as the logic to load and save the
 *        structure from/to disk.
 */

#ifndef _GAMES_MODEL_
#define _GAMES_MODEL_

#include "balancedTreeAPI.h"

/** Number of bytes to read in each line for loading from a CSV file */
#define INPUT_BUFFER 4096
/** The header of the CSV file to skip on load */
#define CSV_HEADER "Product ID,Product Name,Publisher,Genre,Taxable,price,Quantity"
/** The delimter used in the CSV file */
#define CSV_DELIM ","
/** Boolean values for ease of use */
#ifndef false
#define false 0
#endif
#ifndef true
#define true !true
#endif

typedef char bool;

/** A key for use in searches based off the product id */
typedef struct GameKey {
    char *productId;
} GameKey;

/** The struct containing all the data from a CSV file */
typedef struct GamesCsvModel {
    Tree *tree;
    char *fileName;
} GamesCsvModel;

/** A single line from a games CSV file */
typedef struct GameModel {
    GameKey key;
    char *productId;
    char *name;
    char *publisher;
    char *genre;
    bool taxable;
    float price;
    int quantity;
} GameModel;

/**This function allocates a new gamesCsv model for use.
 *@param fileName where to save this model when saveGamesCsv() is called
 *@return a newly allocated empty structure
 */
GamesCsvModel *createGamesCsv(char *fileName);

/**This function allocates a new gameModel with the correct information as given.
 * Used internally.
 *@param productId Product ID of the game
 *@param name Name of the game
 *@param publisher Publisher of the game
 *@param genre Genre of the game
 *@param taxable Whether to tax the game
 *@param price The price of the game in dollars
 *@param quantity The number of games in stock
 *@return newly created and allocated gameCsvModel
 */
GameModel *createGameModel(char *productId, char *name, char *publisher, char *genre, bool taxable, float price, int quantity);

/**This function creates a new gameKey object which can be used in comparisions.
 * User internally.
 *@param productId the id to create a key for
 *@return newly allocated key for searching
 */
GameKey *createGameKey(char *productId);

/**This function frees a game key from memory.
 *@param key the key to free
 */
void destroyGameKey(GameKey *key);

/**This function loads a gamesCsvModel from a CSV file.
 *@param fileName the csv file with game data
 *@return a newly allocated and filled gamesCsvModel
 */
GamesCsvModel *loadGamesCsv(char *fileName);

/**This functions saves a gamesCsvModel to a csv file as specified within the model.
 *@param model the data to save
 *@return whether saving was successful
 */
bool saveGamesCsv(GamesCsvModel *model);

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
void addGameToModel(GamesCsvModel *model, char *productId, char *name, char *publisher, char *genre, bool taxable, float price, int quantity);

/**This function removes a number of games from the inventory of a gamesCsvModel.
 *@param model the inventory model
 *@param productId the product to remove
 *@param count the number to remove
 */
void removeGameFromModel(GamesCsvModel *model, char *productId, int count);

/**This function retrieves a gameModel from a gamesCsvModel based on a product id.
 *@param model the data to look for the gameModel in
 *@param productId the product id to search for
 *@return a gameModel if found or NULL if it does not exist
 */
GameModel *lookupGameFromModel(GamesCsvModel *model, char *productId);

/**This function checks if a gamesCsvModel contains a gameModel based on a product id with enough quantity.
 *@param model the data to look in
 *@param productId the product id to look for
 *@param count the minimum number for quantity
 */
bool containsGameFromModel(GamesCsvModel *model, char *productId, int count);

/**This function retrieves the quantity of games in a gamesCsvModel.
 *@param model the data to look in
 *@param productId the product id to look for
 */
int numGameFromModel(GamesCsvModel *model, char *productId);

/**This function is for use in a tree to compare two seperate gameKeys.
 *@param key1 a pointer to a GameKey (or a GameModel)
 *@param key2 a pointer to a GameKey (or a GameModel)
 *@return how much 'more' key1 is than key two
 */
int gameKeyCompare(void *key1, void *key2);

/**This function frees the memory around a gameModel.
 *@param modelPtr a gameModel to free
 */
void destroyGameModel(void *modelPtr);

/**This function clones a gameModel.
 *@param modelPtr the model to clone
 *@return a new cloned gameModel
 */
void *copyGameModel(void *modelPtr);

/**This function prints a game model to stdout using a comma seperated list of info.
 *@param modelPtr the model to print
 */
void printGameModel(void *modelPtr);

/**This function creates a new copy of the string src.
 *@param src the source string
 *@return a direct clone of src
 */
char *copyString(char *src);

#endif
