/**
 * @file testing.c
 * @author Kanoa Haley
 * @date June 18, 2017
 * @brief File containing tests for a hashtable
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HashTableAPI.h"
#include "KTest.h"

#define PROGRAM_NAME "HashTable Library"

int main()
{
    TestingContext *context = newContext(PROGRAM_NAME);
    begin(context);
    
    done(context);
    return context->failCount;
}
