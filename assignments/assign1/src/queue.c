/**
 * @file queue.c
 * @author Kanoa Haley
 * @date June 2, 2017
 * @brief File containing the implementations for a queue
 */

#include <stdio.h>
#include <stdlib.h>
#include "../include/QueueAPI.h"

Queue *queueCreate(void (*printFunction)(void *toBePrinted), void (*deleteFunction)(void *toBeDeleted))
{
    Queue *queue = malloc(sizeof(Queue));
    queue->list = initializeList(printFunction, deleteFunction, NULL);
    queue->front = NULL;
    queue->length = 0;
    return queue;
}

void queueDestroy(Queue *queue)
{
    deleteList(queue->list);
    queue->front = NULL;
    queue->length = 0;
    free(queue);
}

void enqueue(Queue *queue, void *data)
{
    insertBack(queue->list, data);
    queue->length++;
    if (queue->front == NULL) {
        queue->front = data;
    }
}

void *dequeue(Queue *queue)
{
    if (queue->length == 0) {
        return NULL;
    }
    void *data = getFromFront(queue->list);
    queue->list->head = queue->list->head->next;
    queue->list->head->previous = NULL;
    queue->length--;
    queue->front = getFromFront(queue->list);
    return data;
}

void *queuePeak(Queue *queue)
{
    if (queue->length == 0) {
        return NULL;
    } else {
        return getFromFront(queue->list);
    }
}

int queueLength(Queue *queue)
{
    return queue->length;
}
