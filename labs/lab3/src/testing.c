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
    int fails;

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
    emptyHeap = createHeap(1, MAX_HEAP, destroyData, printData, compare);
    dataHeap = createHeap(1, MAX_HEAP, destroyData, printData, compare);
    fullHeap = createHeap(1, MAX_HEAP, destroyData, printData, compare);

    insertHeapNode(emptyHeap, NULL);
    test(context, "should not insert data", emptyHeap->size == 0);

    insertHeapNode(NULL, ptr1);
    test(context, "should not insert data", emptyHeap->size == 0);

    insertHeapNode(dataHeap, ptr1);
    insertHeapNode(dataHeap, ptr5);
    insertHeapNode(dataHeap, ptr2);
    insertHeapNode(dataHeap, ptr9);
    test(context, "should insert 4 pieces of data", dataHeap->size == 4);

    insertHeapNode(fullHeap, ptr2);
    insertHeapNode(fullHeap, ptr9);
    insertHeapNode(fullHeap, ptr5);
    insertHeapNode(fullHeap, ptr6);
    insertHeapNode(fullHeap, ptr8);
    insertHeapNode(fullHeap, ptr3);
    insertHeapNode(fullHeap, ptr4);
    insertHeapNode(fullHeap, ptr1);
    insertHeapNode(fullHeap, ptr7);
    test(context, "should insert 9 pieces of data", fullHeap->size == 9);

    /* Testing deleteMinOrMax */
    section(context, "deleteMinOrMax");

    deleteMinOrMax(NULL);
    test(context, "should do nothing for NULL heap", 1);
    deleteMinOrMax(emptyHeap);
    test(context, "shouldn't do anything when empty", emptyHeap->size == 0);
    tprint(context, "Will be tested alongside getMinOrMax");

    /* Testing changeHeapType */
    section(context, "changeHeapType");

    changeHeapType(NULL);
    test(context, "should do nothing for NULL heap", 1);
    changeHeapType(emptyHeap);
    test(context, "should make max heap min heap", emptyHeap->type == MIN_HEAP);
    changeHeapType(emptyHeap);
    test(context, "should make min heap max heap", emptyHeap->type == MAX_HEAP);
    tprint(context, "Will be tested alongside getMinOrMax");

    /* Testing getMinOrMax */
    section(context, "getMinOrMax");

    test(context, "should return max for full heap", getMinOrMax(fullHeap) == ptr9);
    test(context, "should return max for semi-full heap", getMinOrMax(dataHeap) == ptr9);

    changeHeapType(fullHeap);
    test(context, "should return min for full heap", getMinOrMax(fullHeap) == ptr1);
    changeHeapType(dataHeap);
    test(context, "should return min for semi-full heap", getMinOrMax(dataHeap) == ptr1);

    deleteMinOrMax(dataHeap);
    test(context, "should return new min for semi-full heap", getMinOrMax(dataHeap) == ptr2);
    insertHeapNode(dataHeap, ptr4);
    deleteMinOrMax(dataHeap);
    test(context, "should return new min for semi-full heap", getMinOrMax(dataHeap) == ptr4);

    deleteMinOrMax(fullHeap);
    test(context, "should return new min for full heap", getMinOrMax(fullHeap) == ptr2);
    deleteMinOrMax(fullHeap);
    test(context, "should return new min for full heap", getMinOrMax(fullHeap) == ptr3);
    insertHeapNode(fullHeap, ptr1);
    test(context, "should return new min for full heap", getMinOrMax(fullHeap) == ptr1);
    changeHeapType(fullHeap);
    test(context, "should return new max for full heap", getMinOrMax(fullHeap) == ptr9);
    deleteMinOrMax(fullHeap);
    test(context, "should return new max for full heap", getMinOrMax(fullHeap) == ptr8);
    changeHeapType(fullHeap);
    deleteMinOrMax(fullHeap);
    test(context, "should return new min for full heap", getMinOrMax(fullHeap) == ptr3);
    changeHeapType(fullHeap);
    test(context, "should return new max for full heap", getMinOrMax(fullHeap) == ptr8);

    /* Testing deleteHeap */
    section(context, "deleteHeap");
    tprint(context, "should print deleted 1 ... deleted 9");
    deleteHeap(fullHeap);

    printf("\n");
    tprint(context, "should print deleted 1 ... and 3 more");
    deleteHeap(dataHeap);

    printf("\n");
    tprint(context, "shouldn't print anything");
    deleteHeap(emptyHeap);

    tprint(context, "shouldn't print anything");
    deleteHeap(NULL);

    fails = context->failCount;
    done(context);
    return fails;
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
    int i1 = *((int *) first);
    int i2 = *((int *) second);
    return i2 - i1;
}
