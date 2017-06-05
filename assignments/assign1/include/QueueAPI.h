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

/**
 * The basis of the queue. Uses a backing linkedlist and also contains easy
 * access to the front of the queue and the length.
 */
typedef struct queueContainer {
    List *list;
    void *front;
    int length;
} Queue;

/**
 * Function to create a new queue backed by a linked list
 * @post a queue is created empty
 * @param printFunction function pointer to print a single node of the queue
 * @param deleteFunction function pointer to delete a single piece of data from the queue
 * @return newly created empty queue
 */
Queue *queueCreate(void (*printFunction)(void *toBePrinted), void (*deleteFunction)(void *toBeDeleted));

/**
 * Function to destory and free a previously created queue
 * @pre queue must be a created queue
 * @post queue is destoryed and all associated memory is freed
 */
void queueDestroy(Queue *queue);

/**
 * Adds a piece of data to the back of the queue
 * @pre queue must be a created queue
 */
void enqueue(Queue *queue, void *data);

/**
 * Removes a piece of data from the front of the queue
 * @pre queue must be a created queue
 * @post the data from the front of the queue is removed
 * @return the data from the front of the queue
 */
void *dequeue(Queue *queue);

/**
 * Gets the data from the front of the queue without removing it
 * @pre queue must be a created queue
 * @return the data from the front of the queue
 */
void *queuePeak(Queue *queue);

/**
 * Checks the current length of the queue
 * @pre queue must be a created queue
 * @return length of the queue
 */
int queueLength(Queue *queue);

#endif
