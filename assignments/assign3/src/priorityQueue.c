/**
 * @file priorityQueue.c
 * @author Kanoa Haley - 0956712 - khaley@mail.uoguelph.ca
 * @date July 12, 2017
 * @brief File containing the implementions for heap based priority queue.
 */

#include "PriorityQueueAPI.h"

PriorityQueue *createPriorityQueue(double agePriorityFactor, char tickOnPush, PRIORITY_QUEUE_TYPE type, void (*destroyData)(void *data), void (*printData)(void *data))
{
    PriorityQueue *pQueue;
    HEAP_TYPE hType;

    if ((type != MIN_PRIORITY_QUEUE && type != MAX_PRIORITY_QUEUE) ||
            destroyData == NULL) {
        return NULL;
    }

    hType = type == MIN_PRIORITY_QUEUE ? MIN_HEAP : MAX_HEAP;
    pQueue = malloc(sizeof(PriorityQueue));

    pQueue->heap = createHeap(INITIAL_HEAP_SIZE, hType, priorityDestroy, printData, priorityCompare);

    pQueue->type = type;
    pQueue->tickOnPush = tickOnPush;
    pQueue->agePriorityFactor = agePriorityFactor;
    pQueue->destroyData = destroyData;
    pQueue->tickCount = 0;

    return pQueue;
}

PriorityQueueNode *createPriorityQueueNode(PriorityQueue *pQueue, void *data, int priority)
{
    PriorityQueueNode *node;

    if (pQueue == NULL) {
        return NULL;
    }

    node = malloc(sizeof(PriorityQueueNode));

    node->myData = data;
    node->priority = priority;
    node->creationTick = pQueue->tickCount;
    node->myQueue = pQueue;

    return node;
}

void pushPriorityQueue(PriorityQueue *pQueue, void *data, int priority)
{
    PriorityQueueNode *node = createPriorityQueueNode(pQueue, data, priority);

    if (node == NULL) {
        return;
    }

    if (pQueue->tickOnPush) {
        tickPriorityQueue(pQueue);
    }
    insertHeapNode(pQueue->heap, node);
}

void *popPriorityQueue(PriorityQueue *pQueue)
{
    PriorityQueueNode *node = getMinOrMax(pQueue->heap);
    void *data;

    if (node == NULL) {
        return NULL;
    }

    data = node->myData;
    free(node);

    /* Need to manually delete min/max and heapify since deleteMinOrMax will call destroyData */
    pQueue->heap->data[0] = pQueue->heap->data[--pQueue->heap->size];
    heapifyDown(pQueue->heap, 0);

    return data;
}

void *peekPriorityQueue(PriorityQueue *pQueue)
{
    PriorityQueueNode *node;
    if (pQueue == NULL || pQueue->heap == NULL || pQueue->heap->size < 1) {
        return NULL;
    }
    
    node = pQueue->heap->data[0];

    if (node != NULL) {
        return node->myData;
    } else {
        return NULL;
    }
}

void tickPriorityQueue(PriorityQueue *pQueue)
{
    if (pQueue != NULL) {
        pQueue->tickCount++;
    }
}

int isEmptyPriorityQueue(PriorityQueue *pQueue)
{
    return pQueue->heap->size == 0 ? 1 : 0;
}

void destroyPriorityQueue(PriorityQueue *pQueue)
{
    if (pQueue == NULL) {
        return;
    }

    deleteHeap(pQueue->heap);
    free(pQueue);
}

int priorityCompare(const void *first, const void *second)
{
    PriorityQueueNode *n1 = (PriorityQueueNode *) first;
    PriorityQueueNode *n2 = (PriorityQueueNode *) second;

    double e1 = n1->priority + (n1->myQueue->tickCount - n1->creationTick) * n1->myQueue->agePriorityFactor;
    double e2 = n2->priority + (n2->myQueue->tickCount - n2->creationTick) * n2->myQueue->agePriorityFactor;

    return e1 - e2;
}

void priorityDestroy(void *data)
{
    PriorityQueueNode *node = (PriorityQueueNode *) data;
    node->myQueue->destroyData(node->myData);
    free(node);
}
