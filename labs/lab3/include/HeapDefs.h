/**
 * @file HeapDefs.h
 * @author Kanoa Haley - 0956712 - khaley@mail.uoguelph.ca
 * @date July 7, 2017
 * @brief File containing the definitions for extended heap 
 * functions as well as the structures required for a binary 
 * tree based heap
 */

#ifndef _HEAP_DEFS_
#define _HEAP_DEFS_

#include <stdlib.h>

#define MIN_HEAP 0
#define MAX_HEAP 1
#define HEAP_TYPE unsigned char

/* Node struct for use in a binary tree based heap */
typedef struct Node {
    void *data;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
} Node;

/* Heap struct for binary tree based implemention of a heap */
typedef struct Heap {
    Node *heap;
    HEAP_TYPE type;
    Node *lastPosition;
    void (*destroyData)(void *data);
    void (*printNode)(void *toBePrinted);
    int (*compare)(const void *first, const void *second);
} Heap;

#endif
