/**
 * @file vaultFile.c
 * @author Kanoa Haley - 0956712 - khaley@mail.uoguelph.ca
 * @date June 24, 2017
 * @brief File containing the implementations for the file storage for the vault application
 */

#include "VaultFile.h"

/**
 * Retrieves the password from the applications configuration file or NULL if no file has been made
 *@returns The applications password or NULL if no file exists
 *@param configFile The name of the configuration file for this application
 */
char *getPassword(char *configFile)
{
    return NULL;
}

/**
 * Loads a vault file given a file name
 *@returns Hash table containing data in the vault with the data in nodes being Entry structs or NULL of no file exists
 *@param vaultFile The file name for a password vault file
 */
HTable *loadVault(char *vaultFile)
{
    return NULL;
}

/**
 * Saves a hash table into a specified vault file
 *@param table The hash table containing the vault data
 *@param vaultFile The file name for the password vault
 */
void saveVault(HTable *table, char *vaultFile)
{

}
