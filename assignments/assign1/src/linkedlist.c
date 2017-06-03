/**
 * @file linkedlist.c
 * @author Kanoa Haley
 * @date May 27, 2017
 * @brief File containing the function implementations of a doubly linked list
 */

#include <stdio.h>
#include <stdlib.h>
#include "../include/LinkedListAPI.h"

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

void insertFront(List *list, void *toBeAdded)
{
    if (list == NULL) {
        return;
    }
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

void insertBack(List *list, void *toBeAdded)
{
    if (list == NULL) {
        return;
    }
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

void deleteList(List *list)
{
    if (list == NULL) {
        return;
    }
    Node *node = list->head;
    while (node != NULL) {
        list->deleteData(node->data);
        Node *tmpNode = node;
        node = node->next;
        free(tmpNode);
    }
    free(list);
}

void insertSorted(List *list, void *toBeAdded)
{
    if (list == NULL) {
        return;
    }
    Node *node = list->head;
    if (node == NULL) {
        insertFront(list, toBeAdded);
    } else {
        while (node != NULL && list->compare(toBeAdded, node->data) >= 0) {
            node = node->next;
        }
        Node *new = initializeNode(toBeAdded);
        if (node == NULL) {
            new->previous = list->tail;
            list->tail->next = new;
            list->tail = new;
        } else if (node->previous == NULL) {
            list->head = new;
            new->next = node;
            node->previous = new;
        } else {
            node->previous->next = new;
            new->previous = node->previous;
            new->next = node;
            node->previous = new;
        }
    }
}

int deleteDataFromList(List *list, void *toBeDeleted)
{
    if (list == NULL) {
        return EXIT_FAILURE;
    }
    Node *node = list->head;
    if (node == NULL) {
        return EXIT_FAILURE;
    }

    while (node != NULL && node->data != toBeDeleted) {
        node = node->next;
    }

    if (node == NULL) {
        return -1;
    } else {
        if (node->previous == NULL) {
            list->head = node->next;
            list->head->previous = NULL;
        } else if (node->next == NULL) {
            list->tail = node->previous;
            list->tail->next = NULL;
        } else {
            node->previous->next = node->next;
            node->next->previous = node->previous;
        }
        list->deleteData(node->data);
        free(node);
        return EXIT_SUCCESS;
    }
}

void *getFromFront(List *list)
{
    return list == NULL ? NULL : (list->head == NULL ? NULL : list->head->data);
}

void *getFromBack(List *list)
{
    return list == NULL ? NULL : (list->tail == NULL ? NULL : list->tail->data);
}

void printForward(List *list)
{
    if (list == NULL) {
        return;
    }
    Node *node = list->head;
    while (node != NULL) {
        list->printData(node->data);
        node = node->next;
    }
}

void printBackwards(List *list)
{
    if (list == NULL) {
        return;
    }
    Node *node = list->tail;
    while (node != NULL) {
        list->printData(node->data);
        node = node->previous;
    }
}
