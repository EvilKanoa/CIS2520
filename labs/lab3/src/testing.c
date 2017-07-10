/**
 * @file testing.c
 * @author Kanoa Haley - 0956712 - khaley@mail.uoguelph.ca
 * @date July 7, 2017
 * @brief File containing tests for a heap
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "HeapDefs.h"
#include "KTest.h"

#define PROGRAM_NAME "Heap Library"

void destroyData(void *data);
void printData(void *data);
int compare(const void *first, const void *second);

int main()
{
    Heap *nullHeap = NULL;
    Heap *emptyHeap;
    Heap *dataHeap;
    Heap *fullHeap;

    int data1 = 1;
    int data2 = 2;
    int data3 = 3;
    int data4 = 4;
    int data5 = 5;
    int data6 = 6;
    int data7 = 7;
    int data8 = 8;
    int data9 = 9;

    int *ptr1 = &data1;
    int *ptr2 = &data2;
    int *ptr3 = &data3;
    int *ptr4 = &data4;
    int *ptr5 = &data5;
    int *ptr6 = &data6;
    int *ptr7 = &data7;
    int *ptr8 = &data8;
    int *ptr9 = &data9;

    TestingContext *context = newContext(PROGRAM_NAME);
    begin(context);

    /* Testing createHeap */
    section(context, "createHeap");

    emptyHeap = createHeap(-10, MAX_HEAP, destroyData, printData, compare);
    test(context, "should create heap", emptyHeap != NULL);
    deleteHeap(emptyHeap);

    emptyHeap = createHeap(-10, MIN_HEAP, destroyData, printData, compare);
    test(context, "should create heap", emptyHeap != NULL);
    deleteHeap(emptyHeap);

    test(context, "should not create heap", createHeap(-10, MIN_HEAP, NULL, printData, compare) == NULL);
    test(context, "should not create heap", createHeap(-10, MAX_HEAP, destroyData, NULL, compare) == NULL);
    test(context, "should not create heap", createHeap(-10, 100, destroyData, printData, compare) == NULL);
    test(context, "should not create heap", createHeap(-10, -60, destroyData, printData, compare) == NULL);

    emptyHeap = createHeap(0, MAX_HEAP, destroyData, printData, compare);
    test(context, "should create heap", emptyHeap != NULL);
    deleteHeap(emptyHeap);

    emptyHeap = createHeap(0, MIN_HEAP, destroyData, printData, compare);
    test(context, "should create heap", emptyHeap != NULL);
    deleteHeap(emptyHeap);

    test(context, "should not create heap", createHeap(0, MIN_HEAP, NULL, printData, compare) == NULL);
    test(context, "should not create heap", createHeap(0, MAX_HEAP, destroyData, NULL, compare) == NULL);
    test(context, "should not create heap", createHeap(0, 100, destroyData, printData, compare) == NULL);
    test(context, "should not create heap", createHeap(0, -60, destroyData, printData, compare) == NULL);

    emptyHeap = createHeap(25, MAX_HEAP, destroyData, printData, compare);
    test(context, "should create heap", emptyHeap != NULL);
    deleteHeap(emptyHeap);

    emptyHeap = createHeap(25, MIN_HEAP, destroyData, printData, compare);
    test(context, "should create heap", emptyHeap != NULL);
    deleteHeap(emptyHeap);

    test(context, "should not create heap", createHeap(25, MIN_HEAP, NULL, printData, compare) == NULL);
    test(context, "should not create heap", createHeap(25, MAX_HEAP, destroyData, NULL, compare) == NULL);
    test(context, "should not create heap", createHeap(25, 100, destroyData, printData, compare) == NULL);
    test(context, "should not create heap", createHeap(25, -60, destroyData, printData, compare) == NULL);

    emptyHeap = createHeap(500, MAX_HEAP, destroyData, printData, compare);
    test(context, "should create heap", emptyHeap != NULL);
    deleteHeap(emptyHeap);

    emptyHeap = createHeap(500, MIN_HEAP, destroyData, printData, compare);
    test(context, "should create heap", emptyHeap != NULL);
    deleteHeap(emptyHeap);

    test(context, "should not create heap", createHeap(500, MIN_HEAP, NULL, printData, compare) == NULL);
    test(context, "should not create heap", createHeap(500, MAX_HEAP, destroyData, NULL, compare) == NULL);
    test(context, "should not create heap", createHeap(500, 100, destroyData, printData, compare) == NULL);
    test(context, "should not create heap", createHeap(500, -60, destroyData, printData, compare) == NULL);

    /* Testing createHeapNode */
    section(context, "createHeapNode");

    test(context, "should return NULL", createHeapNode(NULL) == NULL);
    test(context, "should return NULL", createHeapNode(ptr1) == NULL);

    /* Testing insertHeapNode */
    section(context, "insertHeapNode");

    /* Testing deleteMinOrMax */
    section(context, "deleteMinOrMax");

    /* Testing getMinOrMax */
    section(context, "getMinOrMax");

    /* Testing changeHeapType */
    section(context, "changeHeapType");

    /* Testing deleteHeap */
    section(context, "deleteHeap");


    done(context);
    return context->failCount;
}

void destroyData(void *data)
{
    printf("deleted %d ", *((int *) data));
}

void printData(void *data)
{
    printf("%d", *((int *) data));
}

int compare(const void *first, const void *second)
{
    return *((int *) first) - *((int *) second);
}
