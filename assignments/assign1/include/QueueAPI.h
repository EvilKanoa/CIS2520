/**
 * @file QueueAPI.h
 * @author Kanoa Haley
 * @date June 2, 2017
 * @brief File containing the function definitions for a queue wrapper for a
 *        doubly linked list
 */

 #ifndef _QUEUE_API_
 #define _QUEUE_API_

#include "LinkedListAPI.h"

typedef struct QueueStruct {
    List *list;
    Node *front;
    int length;
} Queue;

/**
 * Function to create a new queue backed by a linked list
 * @post a queue is created empty
 * @return newly created empty queue
 */
Queue *queueCreate();

/**
 * Function to destory and free a previously created queue
 * @pre queue must be a created queue
 * @post queue is destoryed and all associated memory is freed
 */
void queueDestroy(Queue *queue);

void enqueue(Queue *queue, void *data);

void *dequeue(Queue *queue);

void *queuePeak(Queue *queue);

int queueLength(Queue *queue);

 #endif
