/**
 * @file vaultUtilities.c
 * @author Kanoa Haley - 0956712 - khaley@mail.uoguelph.ca
 * @date June 24, 2017
 * @brief File containing various utilities and hashing functions for the password vault application
 */

#include <math.h>
#include "VaultUtilities.h"
#include "VaultFile.h"

int hashDescriptor(size_t tableSize, char *descriptor)
{
    int bigHash = 1;
    long testHash;
    int i;

    for (i = 0; i < strlen(descriptor); i++) {
        testHash = bigHash + (descriptor[i] + 1) * pow(31, strlen(descriptor) - 1 - i);
        if (testHash < INT_MAX) {
            bigHash = testHash;
        } else {
            bigHash = descriptor[i];
        }
    }

    return bigHash % tableSize;
}

void stripNewline(char *str)
{
    if (str[strlen(str) - 1] == '\n') {
        str[strlen(str) - 1] = 0;
    }
}

void freeEntry(void *data)
{
    Entry *entry = (Entry *) data;
    if (entry->descriptor != NULL) {
        free(entry->descriptor);
    }
    if (entry->password != NULL) {
        free(entry->password);
    }
    free(entry);
}
