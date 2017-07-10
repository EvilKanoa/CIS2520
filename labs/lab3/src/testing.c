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

int main()
{
    TestingContext *context = newContext(PROGRAM_NAME);
    begin(context);

    printf("Hello, World!");

    done(context);
    return context->failCount;

    /* Old testing suite for reference
    int size = 10;
    char *data1 = "myData 1";
    char *data2 = "myData 2";
    char *data3 = "myData 3";
    void *ptr1 = (void *) data1;
    void *ptr2 = (void *) data2;
    void *ptr3 = (void *) data3;
    Node *node1 = createNode(1, ptr1);
    Node *node2 = createNode(-100, ptr2);
    Node *node3 = createNode(INT_MAX, ptr3);
    Node *node4 = createNode(INT_MIN, NULL);
    HTable *table = createTable(size, hashFunction, destroyData, printData);

    TestingContext *context = newContext(PROGRAM_NAME);
    begin(context);

    // Testing: hashtable#createNode
    section(context, "createNode");

    test(context, "should have correct key", node1->key == 1);
    test(context, "should have correct data", node1->data == ptr1);
    test(context, "should understand negative key", node2->key == -100);
    test(context, "should store data with negative key", node2->data == ptr2);
    test(context, "should understand max key", node3->key == INT_MAX);
    test(context, "should understand min key", node4->key == INT_MIN);
    test(context, "should store data with max key", node3->data == ptr3);
    test(context, "should store null data", node4->data == NULL);

    free(node1);
    free(node2);
    free(node3);
    free(node4);

    // Testing: hashtable#createTable
    section(context, "createTable");

    test(context, "should have correct size", table->size == size);
    test(context, "should have non null table array", table->table != NULL);
    test(context, "should have correct hashFunction", table->hashFunction == hashFunction);
    test(context, "should have correct destoryData function", table->destroyData == destroyData);
    test(context, "should have correct printData function", table->printData == printData);

    // Testing: hashtable#insertData
    section(context, "insertData");

    insertData(table, 1, ptr1);
    insertData(table, 2, ptr2);
    insertData(table, 2, ptr2);
    insertData(table, 3, ptr3);

    test(context, "should have inserted data in the correct position 1", table->table[0]->data == ptr1);
    test(context, "should have inserted data in the correct position 2", table->table[1]->data == ptr2);
    test(context, "should have inserted data in the correct position 3", table->table[2]->data == ptr3);
    insertData(NULL, 0, NULL);
    test(context, "should do nothing if table is null", 1);

    // Testing: hashtable#lookupData
    section(context, "lookupData");

    test(context, "should retrieve correct data 1", lookupData(table, 1) == ptr1);
    test(context, "should retrieve correct data 2", lookupData(table, 2) == ptr2);
    test(context, "should retrieve correct data 3", lookupData(table, 3) == ptr3);
    test(context, "should return null for null table", lookupData(NULL, 0) == NULL);
    test(context, "should return null for non-existant key", lookupData(table, 0) == NULL);

    // Testing: hashtable#removeData 
    section(context, "removeData");

    removeData(table, 1);

    printf("\n");
    test(context, "should have removed data with key 1", lookupData(table, 1) == NULL);
    tprint(context, "should have printed \"myData 1\"");

    // Testing: hashtable#destroyTable 
    section(context, "destroyTable");

    destroyTable(table);
    printf("\n");
    tprint(context, "should have printed \"myData 2 myData 3\"");

    done(context);
    return context->failCount; */
}
