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

PriorityQueue *createPriorityQueue(double agePriorityFactor, char tickOnPush, PRIORITY_QUEUE_TYPE type, void (*destroyData)(void *data), void (*printData)(void *data));

void pushPriorityQueue(PriorityQueue *pQueue, void *data, int priority);

void *popPriorityQueue(PriorityQueue *pQueue);

void *peekPriorityQueue(PriorityQueue *pQueue);

void tickPriorityQueue(PriorityQueue *pQueue);

void destroyPriorityQueue(PriorityQueue *pQueue);

#endif
