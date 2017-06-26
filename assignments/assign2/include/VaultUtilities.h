/**
 * @file VaultUtilities.h
 * @author Kanoa Haley - 0956712 - khaley@mail.uoguelph.ca
 * @date June 24, 2017
 * @brief File containing the definitions for various utilities and hashing functions for the password vault application
 */

#ifndef _VAULT_UTILITIES_
#define _VAULT_UTILITIES_

#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "HashTableAPI.h"

/** Function to hash a descriptor/key for the vault to a valid index using a multiplicative approach
 *@return The relative index for the descriptor
 *@param tableSize The size of the hashTable
 *@param descriptor The descriptor which is used as a key during the vault application process
 */
int hashDescriptor(size_t tableSize, char *descriptor);

#endif
