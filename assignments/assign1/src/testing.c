/**
 * @file testing.c
 * @author Kanoa Haley
 * @date June 2, 2017
 * @brief File containing tests for a queue (and linkedlist)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/QueueAPI.h"
#include "../include/KTest.h"

#define PROGRAM_NAME "Queue Library"

void printFunction(void *data);
void deleteFunction(void *data);
int compareFunction(const void *first, const void *second);

int main()
{
    TestingContext *context = newContext("LinkedList Library");
    begin(context);

    int data[3];
    data[0] = 1;
    data[1] = 2;
    data[2] = 3;
    void *ptr[3];
    ptr[0] = (void *) &(data[0]);
    ptr[1] = (void *) &(data[1]);
    ptr[2] = (void *) &(data[2]);

    section(context, "initializeList");
    List *list = initializeList(&printFunction, &deleteFunction, &compareFunction);
    List *emptyList = initializeList(&printFunction, &deleteFunction, &compareFunction);
    test(context, "should have null head", list->head == NULL);
    test(context, "should have null tail", list->tail == NULL);
    test(context, "should have print function", list->printData == &printFunction);
    test(context, "should have delete function", list->deleteData == &deleteFunction);
    test(context, "should have compare function", list->compare == &compareFunction);

    section(context, "initializeNode");
    Node *node1 = initializeNode(ptr[0]);
    Node *node2 = initializeNode(ptr[1]);
    Node *node3 = initializeNode(ptr[2]);
    test(context, "should have null next", node1->next == NULL);
    test(context, "should have null previous", node2->previous == NULL);
    test(context, "should have data of int 1", *((int *) node1->data) == 1);
    test(context, "should have data of int 2", *((int *) node2->data) == 2);
    test(context, "should have data of int 3", *((int *) node3->data) == 3);

    section(context, "insertFront");
    insertFront(list, ptr[0]);
    test(context, "should have head data == 1", *((int *) list->head->data) == data[0]);
    test(context, "should have tail data == 1", *((int *) list->tail->data) == data[0]);
    insertFront(list, ptr[1]);
    test(context, "should have head data == 2", *((int *) list->head->data) == data[1]);
    test(context, "should have tail data == 1", *((int *) list->tail->data) == data[0]);

    section(context, "insertBack");
    insertBack(list, ptr[2]);
    test(context, "should have head data == 2", *((int *) list->head->data) == data[1]);
    test(context, "should have head>next data == 1", *((int *) list->head->next->data) == data[0]);
    test(context, "should have tail data == 3", *((int *) list->tail->data) == data[2]);
    test(context, "should have tail>previous data == 1", *((int *) list->tail->previous->data) == data[0]);

    section(context, "getFromFront");
    test(context, "should get data == 2 from front", *((int *) getFromFront(list)) == data[1]);
    test(context, "should get NULL from empty list", getFromFront(emptyList) == NULL);

    section(context, "getFromBack");
    test(context, "should get data == 3 from back", *((int *) getFromBack(list)) == data[2]);
    test(context, "should get NULL from empty list", getFromBack(emptyList) == NULL);

    section(context, "deleteList");
    deleteList(list);
    printf("\n");
    test(context, "should print \"delete 2 delete 1 delete 3 \"", 1);
    deleteList(emptyList);

    section(context, "insertSorted 1");
    List *list1 = initializeList(&printFunction, &deleteFunction, &compareFunction);
    insertSorted(list1, ptr[1]);
    insertSorted(list1, ptr[2]);
    insertSorted(list1, ptr[0]);
    test(context, "should have head 1", list1->head->data == ptr[0]);
    test(context, "should have head>next 2", list1->head->next->data == ptr[1]);
    test(context, "should have head>previous NULL", list1->head->previous == NULL);
    test(context, "should have tail 3", list1->tail->data == ptr[2]);
    test(context, "should have tail>previous 2", list1->tail->previous->data == ptr[1]);
    test(context, "should have tail>next NULL", list1->tail->next == NULL);
    deleteList(list1);

    section(context, "insertSorted 2");
    List *list2 = initializeList(&printFunction, &deleteFunction, &compareFunction);
    insertSorted(list2, ptr[0]);
    insertSorted(list2, ptr[1]);
    insertSorted(list2, ptr[2]);
    test(context, "should have head 1", list2->head->data == ptr[0]);
    test(context, "should have head>next 2", list2->head->next->data == ptr[1]);
    test(context, "should have head>previous NULL", list2->head->previous == NULL);
    test(context, "should have tail 3", list2->tail->data == ptr[2]);
    test(context, "should have tail>previous 2", list2->tail->previous->data == ptr[1]);
    test(context, "should have tail>next NULL", list2->tail->next == NULL);
    deleteList(list2);

    section(context, "insertSorted 3");
    List *list3 = initializeList(&printFunction, &deleteFunction, &compareFunction);
    insertSorted(list3, ptr[2]);
    insertSorted(list3, ptr[1]);
    insertSorted(list3, ptr[0]);
    test(context, "should have head 1", list3->head->data == ptr[0]);
    test(context, "should have head>next 2", list3->head->next->data == ptr[1]);
    test(context, "should have head>previous NULL", list3->head->previous == NULL);
    test(context, "should have tail 3", list3->tail->data == ptr[2]);
    test(context, "should have tail>previous 2", list3->tail->previous->data == ptr[1]);
    test(context, "should have tail>next NULL", list3->tail->next == NULL);
    deleteList(list3);

    section(context, "deleteDataFromList");
    List *list4 = initializeList(&printFunction, &deleteFunction, &compareFunction);
    insertFront(list4, ptr[0]);
    insertBack(list4, ptr[1]);
    insertBack(list4, ptr[2]);
    deleteDataFromList(list4, ptr[2]);
    test(context, "should have head>next 2", list4->head->next->data == ptr[1]);
    test(context, "should have tail 2", list4->tail->data == ptr[1]);
    test(context, "should have tail>next NULL", list4->tail->next == NULL);
    deleteDataFromList(list4, ptr[0]);
    test(context, "should have head 2", list4->head->data == ptr[1]);
    test(context, "should have tail 2", list4->tail->data == ptr[1]);
    test(context, "should have head>previous NULL", list4->head->previous == NULL);
    test(context, "should have tail>next NULL", list4->tail->next == NULL);
    deleteList(list4);

    section(context, "printForward");
    List *list5 = initializeList(&printFunction, &deleteFunction, &compareFunction);
    insertBack(list5, ptr[0]);
    insertBack(list5, ptr[1]);
    insertBack(list5, ptr[2]);
    printForward(list5);
    printf("\n");
    test(context, "should print \"data 1 data 2 data 3 \"", 1);

    section(context, "printBackwards");
    printBackwards(list5);
    printf("\n");
    test(context, "should print \"data 3 data 2 data 1 \"", 1);
    deleteList(list5);

    done(context);
    printf("\n\n");

    context = newContext(PROGRAM_NAME);
    begin(context);

    int i1 = 1, i2 = 2, i3 = 3;
    int *p1 = &i1, *p2 = &i2, *p3 = &i3;
    void *dat;

    section(context, "queueCreate");
    Queue *q = queueCreate(printFunction, deleteFunction);
    test(context, "should have correct printFunction", printFunction == q->list->printData);
    test(context, "should have correct deleteFunction", deleteFunction == q->list->deleteData);
    test(context, "should have length 0", q->length == 0);
    test(context, "should have null front", q->front == NULL);

    section(context, "enqueue");
    tprint(context, "adding '1'");
    enqueue(q, p1);
    test(context, "should have front of '1'", q->front == p1);
    tprint(context, "adding '2'");
    enqueue(q, p2);
    test(context, "should have length of 2", q->length == 2);
    tprint(context, "adding '3'");
    enqueue(q, p3);
    test(context, "should have front of '1'", q->front == p1);

    section(context, "dequeue");
    dat = dequeue(q);
    test(context, "should return '1'", dat == p1);
    test(context, "should have length of 2", q->length == 2);

    section(context, "queuePeak");
    dat = queuePeak(q);
    test(context, "should return '2'", dat == p2);
    test(context, "should have length of 2", q->length == 2);

    section(context, "queueLength");
    int length = queueLength(q);
    test(context, "should return the same as the length variable", length == q->length);

    section(context, "queueDestroy");
    tprint(context, "destroying queue, expect output");
    queueDestroy(q);
    test(context, "should have printed 'delete 2 delete 3 '", 1);

    done(context);
}

void printFunction(void *data) {
    printf("data %d ", *((int *) data));
}

void deleteFunction(void *data) {
    printf("delete %d ", *((int *) data));
}

int compareFunction(const void *first, const void *second) {
    int i1 = *((int *) first);
    int i2 = *((int *) second);
    return i1 - i2;
}
