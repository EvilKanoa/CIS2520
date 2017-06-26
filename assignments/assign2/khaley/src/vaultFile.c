/**
 * @file vaultFile.c
 * @author Kanoa Haley - 0956712 - khaley@mail.uoguelph.ca
 * @date June 24, 2017
 * @brief File containing the implementations for the file storage for the vault application
 */

#include <stdlib.h>
#include "VaultFile.h"
#include "VaultUtilities.h"

char *getPassword(char *configFile)
{
    FILE *fp = fopen(configFile, "r");
    char *password;
    char input[BUFFER_SIZE];
    
    if (fp == NULL) {
        return NULL;
    } else if (fgets(input, BUFFER_SIZE - 1, fp) == NULL) {
        fclose(fp);
        return NULL;
    } else {
        stripNewline(input);
        password = malloc(sizeof(char) * (strlen(input) + 1));
        strcpy(password, input);
        password[strlen(password)] = 0;
        fclose(fp);
        return password;
    }
}

void savePassword(char *configFile, char *password)
{
    FILE *fp = fopen(configFile, "w");
    stripNewline(password);
    if (fp != NULL) {
        fprintf(fp, "%s\n", password);
        fclose(fp);
    }
}

/**
 * Loads a vault file given a file name
 *@returns Hash table containing data in the vault with the data in nodes being Entry structs
 *@param vaultFile The file name for a password vault file
 */
HTable *loadVault(char *vaultFile)
{
    FILE *fp = fopen(vaultFile, "r");
    HTable *table = createTable(1000, hashDescriptor, freeEntry, NULL);
    Entry *entry;
    char descriptor[BUFFER_SIZE];
    char password[BUFFER_SIZE];

    if (fp == NULL) {
        return table;
    }

    while (fgets(descriptor, BUFFER_SIZE - 1, fp) != NULL && fgets(password, BUFFER_SIZE - 1, fp) != NULL) {
        stripNewline(descriptor);
        stripNewline(password);
        entry = malloc(sizeof(Entry));
        entry->descriptor = malloc(sizeof(char) * (strlen(descriptor) + 1));
        entry->password = malloc(sizeof(char) * (strlen(password) + 1));
        strcpy(entry->descriptor, descriptor);
        strcpy(entry->password, password);
        insertData(table, entry->descriptor, (void *) entry);
    }

    fclose(fp);

    return table;
}

/**
 * Saves a hash table into a specified vault file
 *@param table The hash table containing the vault data
 *@param vaultFile The file name for the password vault
 */
void saveVault(HTable *table, char *vaultFile)
{
    FILE *fp;
    Node *node;
    Entry *entry;
    int i;

    if (table == NULL || vaultFile == NULL) {
        return;
    }

    fp = fopen(vaultFile, "w");

    for (i = 0; i < table->size; i++) {
        node = table->table[i];
        while (node != NULL) {
            entry = (Entry *) node->data;
            fprintf(fp, "%s\n%s\n", entry->descriptor, entry->password);
            node = node->next;
        }
    }

    destroyTable(table);
    free(vaultFile);
    fclose(fp);
}
