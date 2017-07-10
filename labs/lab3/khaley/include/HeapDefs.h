/**
 * @file HeapDefs.h
 * @author Kanoa Haley - 0956712 - khaley@mail.uoguelph.ca
 * @date July 7, 2017
 * @brief File containing the definitions for extended heap 
 * functions as well as the structures required for an array 
 * based heap
 */

#ifndef _HEAPTYPES_
#define _HEAPTYPES_
#ifndef _HEAP_API_
#define MIN_HEAP 0
#define MAX_HEAP 1
#define HEAP_TYPE unsigned char
#endif
#endif

#ifndef _HEAP_DEFS_
#define _HEAP_DEFS_

#include <stdlib.h>

/** Node struct for use in a binary tree based heap **/
typedef void * Node;

/** Heap struct for binary tree based implemention of a heap **/
typedef struct Heap {
    Node *data;
    int size;
    int maxSize;
    HEAP_TYPE type;
    void (*destroyData)(void *data);
    void (*printNode)(void *toBePrinted);
    int (*compare)(const void *first, const void *second);
} Heap;

#include "heap.h"

/**Ensures that the heap follows the standard heap structure for it's given type around a new node
 *@param heap The heap to ensure has a correct structure
 *@param node The node to base the correction around
 **/
void heapifyUp(Heap *heap, int node);

/**Rearranges a heap recursively downwards
 *@param heap The heap to ensure has a correct structure
 *@param node The node to base the correction around
 **/
void heapifyDown(Heap *heap, int node);

/**Checks to make sure that the heap's size is less than it's max size,
 * if it isn't, it doubles the heaps size
 *@param heap Heap to ensure is the correct size
 **/
void checkSize(Heap *heap);

/**Determines if the checked node should go "below" the against node. For a max heap this checks
 * if the check node is less than the against node and vice-versa for a min heap.
 * Can also be considered (for max heap) "isLessThan"
 *@param heap Heap that the nodes belong to
 *@param check Node to check
 *@param against Node to compare check against
 *@return 1 if the check node should be below the against node, 0 otherwise
 **/
int isBelow(Heap *heap, Node check, Node against);

#endif
