/**
 * @file testing.c
 * @author Kanoa Haley
 * @date June 2, 2017
 * @brief File containing tests for a queue
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/QueueAPI.h"
#include "../include/KTest.h"

#define PROGRAM_NAME "Queue Library"

void printFunction(void *data);
void deleteFunction(void *data);

int deleteCount = 0;

int main()
{
    TestingContext *context = newContext(PROGRAM_NAME);
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
    deleteCount = 0;
    tprint(context, "destroying queue, expect output");
    queueDestroy(q);
    test(context, "should have printed 'delete 2 delete 3 '", 1);
    test(context, "should have deleted 2 items", deleteCount == 2);

    done(context);
}

void printFunction(void *data) { }

void deleteFunction(void *data) {
    printf("delete %d ", *((int *) data));
    deleteCount++;
}
