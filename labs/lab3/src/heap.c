/**
 * @file heap.c
 * @author Kanoa Haley - 0956712 - khaley@mail.uoguelph.ca
 * @date July 7, 2017
 * @brief File containing the implementions for a binary tree based 
 * heap library based on the HeapAPI as well as the extra functions 
 * as defined n the HeapDefs.h file
 */

#include "HeapAPI.h"

Heap *createHeap(size_t initialSize, HEAP_TYPE htype, void (*destroyDataFP)(void *data),void (*printNodeFP)(void *toBePrinted),int (*compareFP)(const void *first, const void *second))
{
   Heap *heap = malloc(sizeof(Heap));
   heap->type = htype;
   heap->destroyData = destroyDataFP;
   heap->printNode = printNodeFP;
   heap->compare = compareFP;
   return heap;
}

Node *createHeapNode(void *data)
{
    Node *node = malloc(sizeof(Node));
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    node->data = data;
    return node;
}

/**Inserts a Node into the heap. Uses createHeapNode to place the data in a Node structure, and then puts the newly
 *created Node in the heap by adding at the bottom and comparing it to each parent node until it fits the Heap structure.
 *If the heap is a min heap, if the Node is lesser than the parent, it is swapped. The opposite is true for a max heap.
 *@pre Heap must exist and have data allocated to it
 *@param heap Pointer to a heap
 *@param data Pointer to generic data that is to be inserted into the heap
**/
void insertHeapNode(Heap *heap, void *data)
{

}

/**Function to remove the maximum or minimum Node of the heap (depending on min heap or max heap).
 *Once the Node has been deleted, the Node at the deepest point in the Heap is placed in the min/max position.
 *Finally, the heap is heapified to maintain heap property.
 *@pre Heap must exist and have memory allocated to it
 *@param heap Pointer to a heap.
 **/
void deleteMinOrMax(Heap *heap)
{

}

/**Function to rearrange a heap to maintain heap property. Starting at the min/max, each Node is compared with its
 *two children to determine the smallest/largest of the three. If the parent is smaller/larger than the child,
 *it is swapped. Heapify is then recursively called on the child in order to continue heapifying until it reaches the bottom of the heap.
 *@param heap Pointer to a heap to be heapified
 **/
void *getMinOrMax(Heap *heap)
{
    return NULL;
}

/**Function to switch the type of heap from min-to-max or max-to-min. This changes the htype flag from MIN_HEAP
 *to MAX_HEAP and vice versa. Once the flag has been changed, heapify is called on the heap to rearrange it to 
 *fit the new heap property.
 *@param heap Pointer to a heap to switch from min-to-max or max-to-min.
 **/
void changeHeapType(Heap *heap)
{

}

/**Function delete a heap. This function calls deleteMinOrMax the same amount of times as the size of the
 *heap, which heapifies after each deletion. Finally, it frees the Heap structure.
 *@param heap Pointer of a heap to be deleted.
 **/
void deleteHeap(Heap *heap)
{

}

void heapify(Heap *heap, Node *newNode)
{
    Node *parent = newNode->parent;

    while (heap->compare(newNode->data, parent->data) * heap->type == MAX_HEAP ? 1 : -1 > 0) {
        // swap new node <-> parent node
        // parent node = get new parent node from new newnode
    }
}
