/**
 * @file testing.c
 * @author Kanoa Haley - 0956712 - khaley@mail.uoguelph.ca
 * @date July 7, 2017
 * @brief File containing tests for a priority queue
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "PriorityQueueAPI.h"
#include "KTest.h"

#define PROGRAM_NAME "Priority Queue Library"

int main()
{
    int fails;

    TestingContext *context = newContext(PROGRAM_NAME);
    begin(context);

    fails = context->failCount;
    done(context);
    return fails;
}
