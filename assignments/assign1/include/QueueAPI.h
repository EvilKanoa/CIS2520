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
    Node *back;
    int length;
} Queue;

 #endif
