/**
 * @file linkedlist.c
 * @author Kanoa Haley
 * @date May 27, 2017
 * @brief File containing the function implementations of a doubly linked list
 */

#include <stdio.h>
#include <stdlib.h>
#include "../include/LinkedListAPI.h"

/**Function to point the list head to the appropriate functions. Allocates memory to the struct.
 *@return pointer to the list head
 *@param printFunction function pointer to print a single node of the list
 *@param deleteFunction function pointer to delete a single piece of data from the list
 *@param compareFunction function pointer to compare two nodes of the list in order to test for equality or order
 **/
List *initializeList(void (*printFunction)(void *toBePrinted),void (*deleteFunction)(void *toBeDeleted),int (*compareFunction)(const void *first,const void *second))
{
    List *list = malloc(sizeof(List));
    list->head = NULL;
    list->tail = NULL;
    list->deleteData = deleteFunction;
    list->compare = compareFunction;
    list->printData = printFunction;
    return list;
}

/**Function for creating a node for a linked list. This node contains generic data and may be connected to 
other notes in a list.
*@pre data should be of same size of void pointer on the users machine to avoid size conflicts. data must be valid.
*data must be cast to void pointer before being added.
*@post data is valid to be added to a linked list
*@return On success returns a node that can be added to a linked list. On failure, returns NULL.
*@param data - is a generic pointer to any data type.
**/
Node *initializeNode(void *data)
{
    Node *node = malloc(sizeof(Node));
    if (node != NULL) {
        node->next = NULL;
        node->previous = NULL;
        node->data = data;
    }
    return node;
}

/**Inserts a Node to the front of a linked list. The list then updates accordingly to adhere to the ADT.
*@pre 'List' type must exist and be used in order to keep track of the linked list.
*@param list pointer to the dummy head of the list
*@param toBeAdded a pointer to data that is to be added to the linked list
**/
void insertFront(List *list, void *toBeAdded)
{
    Node *newNode = initializeNode(toBeAdded);
    newNode->next = list->head;
    if (list->head != NULL) {
        list->head->previous = newNode;
    }
    list->head = newNode;
    if (list->tail == NULL) {
        list->tail = list->head;
    }
}

/**Inserts a Node to the back of a linked list. The list then updates accordingly to adhere to the ADT.
*@pre 'List' type must exist and be used in order to keep track of the linked list.
*@param list pointer to the dummy head of the list
*@param toBeAdded a pointer to data that is to be added to the linked list
**/
void insertBack(List *list, void *toBeAdded)
{
    Node *newNode = initializeNode(toBeAdded);
    newNode->previous = list->tail;
    if (list->tail != NULL) {
        list->tail->next = newNode;
    }
    list->tail = newNode;
    if (list->head == NULL) {
        list->head = list->tail;
    }
}

/** Deletes the entire linked list head to tail, starting with the nodes, followed by the list itself.
*@pre 'List' type must exist and be used in order to keep track of the linked list.
*@param list pointer to the List-type dummy node
**/
void deleteList(List *list)
{
    Node *node = list->head;
    while (node != NULL) {
        list->deleteData(node->data);
        Node *tmpNode = node;
        node = node->next;
        free(tmpNode);
    }
    free(list);
}

/** Uses the comparison function in the List struct to place the element in the appropriate position in the list.
*this is intended to be used from the beginning in order to keep the list completely sorted.
*@pre List exists and has memory allocated to it. Node to be added is valid.
*@post The node to be added will be placed immediately before or after the first occurrence of a related node
*@param list a pointer to the dummy head of the list containing function pointers for delete and compare, as well 
as a pointer to the first and last element of the list.
*@param toBeAdded a pointer to data that is to be added to the linked list
**/
void insertSorted(List *list, void *toBeAdded)
{
    Node *newNode = initializeNode(toBeAdded);
    Node *node = list->head;
    if (node == NULL) {
        insertFront(list, node);
    } else {
        while (node != NULL) {
            if (list->compare(node->data, newNode->data) >= 0) {
                newNode->next = node;
                newNode->previous = node->previous;
                if (node->previous != NULL) {
                    node->previous->next = newNode;
                } else {
                    list->head = newNode;
                }
                node->previous = node;
                return;
            }
            node = node->next;
        }
    }
}

/**Function to remove a node from the list and alter the pointers accordingly to not disrupt the order of the
 *data structure. 
 *@pre List must exist and have memory allocated to it
 *@post toBeDeleted will have its memory freed if it exists in the list.
 *@param list pointer to the dummy head of the list containing deleteFunction function pointer
 *@param toBeDeleted pointer to data that is to be removed from the list
 *@return returns EXIT_SUCCESS on success, and EXIT_FAILURE when empty. Returns -1 when the node cannot be found.
 **/
int deleteDataFromList(List *list, void *toBeDeleted)
{
    Node *node = list->head;
    if (node == NULL) {
        return EXIT_FAILURE;
    }
    while (node != NULL) {
        if (node->data == toBeDeleted) {
            if (node->previous != NULL) {
                node->previous->next = node->next;
            } else {
                list->head = node->next;
            }
            if (node->next != NULL) {
                node->next->previous = node->previous;
            } else {
                list->tail = node->previous;
            }
            list->deleteData(toBeDeleted);
            free(node);
            return EXIT_SUCCESS;
            
        }
        node = node->next;
    }
    return -1;
}

/**Function to return the data at the front of the list.
 *@pre The list exists and has memory allocated to it
 *@param list pointer to the dummy head of the list containing the head of the list
 *@return pointer to the data located at the head of the list
 **/
void *getFromFront(List *list)
{
    return list->head == NULL ? NULL : list->head->data;
}

/**Function to return the data at the back of the list.
 *@pre The list exists and has memory allocated to it
 *@param list pointer to the dummy head of the list containing the tail of the list
 *@return pointer to the data located at the tail of the list
 **/
void *getFromBack(List *list)
{
    return list->tail == NULL ? NULL : list->tail->data;
}

/**Function to print list from head to tail. This will utilize the list's printData function pointer to print.
 *@pre List must exist, but does not have to have elements.
 *@param list Pointer to linked list dummy head.
 **/
void printForward(List *list)
{
    Node *node = list->head;
    while (node != NULL) {
        list->printData(node->data);
        node = node->next;
    }
}

/**Function to print list from tail to head. This will utilize the list's printData function pointer to print.
 *@pre List must exist, but does not have to have elements.
 *@param list Pointer to linked list dummy head.
 **/
void printBackwards(List *list)
{
    Node *node = list->tail;
    while (node != NULL) {
        list->printData(node->data);
        node = node->previous;
    }
}
