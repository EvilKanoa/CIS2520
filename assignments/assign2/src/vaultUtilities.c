/**
 * @file vaultUtilities.c
 * @author Kanoa Haley - 0956712 - khaley@mail.uoguelph.ca
 * @date June 24, 2017
 * @brief File containing various utilities and hashing functions for the password vault application
 */

#include "VaultUtilities.h"

int hashDescriptor(size_t tableSize, char *descriptor)
{
    int bigHash = 1;
    long testHash;
    int i;

    for (i = 0; i < strlen(descriptor); i++) {
        testHash = bigHash * descriptor[i];
        if (testHash < INT_MAX) {
            bigHash = testHash;
        } else {
            bigHash = descriptor[i];
        }
    }

    return bigHash % tableSize;
}
