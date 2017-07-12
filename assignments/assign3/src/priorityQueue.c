/**
 * @file priorityQueue.c
 * @author Kanoa Haley - 0956712 - khaley@mail.uoguelph.ca
 * @date July 12, 2017
 * @brief File containing the implementions for heap based priority queue.
 */

#include "PriorityQueueAPI.h"

PriorityQueue *createPriorityQueue(double agePriorityFactor, char tickOnPush, PRIORITY_QUEUE_TYPE type, void (*destroyData)(void *data), void (*printData)(void *data))
{
    return NULL;
}

void pushPriorityQueue(PriorityQueue *pQueue, void *data, int priority)
{

}

void *popPriorityQueue(PriorityQueue *pQueue)
{
    return NULL;
}

void *peekPriorityQueue(PriorityQueue *pQueue)
{
    return NULL;
}

void tickPriorityQueue(PriorityQueue *pQueue)
{

}

void destroyPriorityQueue(PriorityQueue *pQueue)
{

}
