/**
 * @file PriorityQueueAPI.h
 * @author Kanoa Haley
 * @date July 12, 2017
 * @brief File containing the function definitions for a priority queue based
 *        on a heap using the aging anti-starvation algoritm.
 */

#ifndef _PRIORITY_QUEUE_API_
#define _PRIORITY_QUEUE_API_

#include "HeapDefs.h"

/**Priority queue can either respect lower priorities as more important (min)
 * or high priorities as more important (max).
 */
#define PRIORITY_QUEUE_TYPE unsigned char
#define MIN_PRIORITY_QUEUE 0
#define MAX_PRIORITY_QUEUE 1

/**Priority queue for heap based implementation of a priority queue using the
 * aging anti-starvation algoritm.
 */
typedef struct PriorityQueue {
    Heap *heap;
    PRIORITY_QUEUE_TYPE type;
    char tickOnPush;
    double agePriorityFactor;
    void (*destroyData)(void *data);
    void (*printData)(void *data);
} PriorityQueue;

/** Data node for a priority queue */
typedef struct PriorityQueueNode {
    void *myData;
    int priority;
    long creationTick; /** The current tick count at insertion of this item */
}

/**Function to allocate memory for the queue and initialize properly
 *@param agePriorityFactor decimal number used to denote the importance of age against priority, [0.0, 1.0]
 *@param tickOnPush whether the queue should tick on every push, 1 for yes, 0 for no
 *@param type if min or max priority is higher
 *@param destroyData function to free a single piece of data
 *@param printData function to print a single piece of data
 *@return pointer to the priority queue
 */
PriorityQueue *createPriorityQueue(double agePriorityFactor, char tickOnPush, PRIORITY_QUEUE_TYPE type, void (*destroyData)(void *data), void (*printData)(void *data));

/**Function to insert an item with a given priority into the queue
 *@param pQueue priority queue to use
 *@param data item to insert
 *@param priority item's priority
 */
void pushPriorityQueue(PriorityQueue *pQueue, void *data, int priority);

/**Function to remove and return the next item with the most important effective priority a queue
 *@param pQueue priority queue to use
 *@return item with the higher (max) / lower (min) priority
 */
void *popPriorityQueue(PriorityQueue *pQueue);

/**Function to return the next item with the most important effective priority a queue
 *@param pQueue priority queue to use
 *@return item with the higher (max) / lower (min) priority
 */
void *peekPriorityQueue(PriorityQueue *pQueue);

/**Function to grow the age factor on the items currently in the queue
 *@param pQueue priority queue to use
 */
void tickPriorityQueue(PriorityQueue *pQueue);

/**Function to free the queue and all its items
 *@param pQueue priority queue to destroy
 */
void destroyPriorityQueue(PriorityQueue *pQueue);

#endif
