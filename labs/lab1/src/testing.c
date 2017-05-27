/**
 * @file testing.c
 * @author Kanoa Haley
 * @date May 27, 2017
 * @brief File containing tests for a doubly linked list
 */

#include <stdio.h>
#include <stdlib.h>
#include "../include/LinkedListAPI.h"

int main()
{
    List *l;
    l = malloc(sizeof(List));
    printf("test complete");
    free(l);
    return 0;
}
