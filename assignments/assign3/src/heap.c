/**
 * @file heap.c
 * @author Kanoa Haley - 0956712 - khaley@mail.uoguelph.ca
 * @date July 7, 2017
 * @brief File containing the implementions for an array based 
 * heap library based on the HeapAPI as well as the extra functions 
 * as defined in the HeapDefs.h file
 */

#include "HeapDefs.h"

Heap *createHeap(size_t initialSize, HEAP_TYPE htype, void (*destroyDataFP)(void *data),void (*printNodeFP)(void *toBePrinted),int (*compareFP)(const void *first, const void *second))
{
    Heap *heap;

    if (destroyDataFP == NULL || compareFP == NULL ||
            (htype != MIN_HEAP && htype != MAX_HEAP)) {
        return NULL;
    }

    heap = malloc(sizeof(Heap));

    heap->type = htype;
    heap->destroyData = destroyDataFP;
    heap->printNode = printNodeFP;
    heap->compare = compareFP;

    if (initialSize > 0) {
        heap->data = malloc(sizeof(Node) * initialSize);
    }
    heap->maxSize = (int) initialSize;
    heap->size = 0;

    return heap;
}

Node *createHeapNode(void *data)
{
    return NULL;
}

void insertHeapNode(Heap *heap, void *data)
{
    if (heap == NULL || data == NULL) {
        return;
    }

    checkSize(heap);
    heap->data[heap->size] = data;

    heapifyUp(heap, heap->size++);
}

void deleteMinOrMax(Heap *heap)
{
    if (heap == NULL || heap->size == 0) {
        return;
    }

    heap->destroyData(heap->data[0]);
    heap->data[0] = heap->data[--heap->size];

    heapifyDown(heap, 0);
}

void *getMinOrMax(Heap *heap)
{
    if (heap == NULL || heap->size == 0) {
        return NULL;
    }

    heapifyDown(heap, 0);
    return (void *) heap->data[0];
}

void changeHeapType(Heap *heap)
{
    if (heap == NULL) {
        return;
    }

    heap->type = heap->type == MAX_HEAP ? MIN_HEAP : MAX_HEAP;

    if (heap->size > 0) {
        heapifyDown(heap, 0);
    }
}

void deleteHeap(Heap *heap)
{
    int i;

    if (heap == NULL) {
        return;
    }

    for (i = 0; i < heap->size; i++) {
        heap->destroyData(heap->data[i]);
    }
    free(heap->data);
    free(heap);
}

void heapifyUp(Heap *heap, int node)
{
    Node temp;

    /* continue bubbling the node up the heap while:
       - it is not the top node 
       - it is larger (max) / smaller (min) than its parent */
    while (node != 0 && isBelow(heap, heap->data[(node - 1) / 2], heap->data[node])) {
        temp = heap->data[node];
        heap->data[node] = heap->data[(node - 1) / 2];
        heap->data[(node - 1) / 2] = temp;
        node = (node - 1) / 2;
    }
}

void heapifyDown(Heap *heap, int node)
{
    int i;
    for (i = heap->size - 1; i > 0; i--) {
        heapifyUp(heap, i);
    }
}

void checkSize(Heap *heap)
{
    if (heap->size >= heap->maxSize) {
        heap->maxSize = heap->maxSize * 2;
        if (heap->size == 0) {
            heap->data = malloc(heap->maxSize * sizeof(Node));
        } else {
            heap->data = realloc(heap->data, heap->maxSize * sizeof(Node));
        }
    }
}

int isBelow(Heap *heap, Node check, Node against)
{
    if (heap->type == MAX_HEAP && heap->compare(check, against) < 0) {
        return 1;
    } else if (heap->type == MIN_HEAP && heap->compare(check, against) > 0) {
        return 1;
    } else {
        return 0;
    } 
}
