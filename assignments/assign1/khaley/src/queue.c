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

Queue *queueFromList(List *data)
{
    Queue *queue = malloc(sizeof(Queue));
    queue->list = data;
    queue->front = getFromFront(data);
    queue->length = -1;
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
    if (queueLength(queue) == 0) {
        return NULL;
    }
    void *data = getFromFront(queue->list);
    if (queueLength(queue) > 1) {
        queue->list->head = queue->list->head->next;
        queue->list->head->previous = NULL;
        queue->front = getFromFront(queue->list);
    } else {
        queue->list->head = NULL;
        queue->front = NULL;
    }
    queue->length--;
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
    if (queue->length < 0) {
        // need to calculate size of queue
        Node *node = queue->list->head;
        int length = 0;
        while (node != NULL) {
            length++;
            node = node->next;
        }
        queue->length = length;
    }
    return queue->length;
}
