/**
 * @file vault.c
 * @author Kanoa Haley - 0956712 - khaley@mail.uoguelph.ca
 * @date June 24, 2017
 * @brief File containing the implemention for the vault application including its main method
 */

#include "VaultUtilities.h"

int main()
{
    int hash;
    hash = hashDescriptor(100, "amazon");
    printf("Hash is: %d\n", hash);
    return 0;
}
