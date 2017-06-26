/**
 * @file VaultFile.h
 * @author Kanoa Haley - 0956712 - khaley@mail.uoguelph.ca
 * @date June 24, 2017
 * @brief File containing the definitions for the data storage for the vault application
 */

#ifndef _VAULT_FILE_
#define _VAULT_FILE_

#include "HashTableAPI.h"
#include "VaultUtilities.h"

/**
 * The struct containing the information for a saved password with its descriptor
 */
typedef struct Entry {
    char *descriptor;
    char *password;
} Entry;

/*
 * A struct used to store entries into a file
 */
typedef struct EntryData {
    long descriptorPos;
    long passwordPos;
} EntryData;

/*
 * The struct containing all the information for a password/vault file
 */
typedef struct Vault {
    int length;
    Entry *entries;
} Vault;

/**
 * Retrieves the password from the applications configuration file or NULL if no file has been made
 *@returns The applications password or NULL if no file exists
 *@param configFile The name of the configuration file for this application
 */
char *getPassword(char *configFile);

/**
 * Loads a vault file given a file name
 *@returns Hash table containing data in the vault with the data in nodes being Entry structs or NULL of no file exists
 *@param vaultFile The file name for a password vault file
 */
HTable loadVault(char *vaultFile);

/**
 * Saves a hash table into a specified vault file
 *@param table The hash table containing the vault data
 *@param vaultFile The file name for the password vault
 */
void saveVault(HTable *table, char *vaultFile);

#endif
