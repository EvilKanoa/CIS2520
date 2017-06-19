/**
 * @file testing.c
 * @author Kanoa Haley
 * @date June 18, 2017
 * @brief File containing tests for a hashtable
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "HashTableAPI.h"
#include "KTest.h"

#define PROGRAM_NAME "HashTable Library"

int hashFunction(size_t tableSize, int key);
void destroyData(void *data);
void printData(void *data);

int main()
{
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

    /* Testing: hashtable#createNode */
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

    /* Testing: hashtable#createTable */
    section(context, "createTable");

    test(context, "should have correct size", table->size == size);
    test(context, "should have non null table array", table->table != NULL);
    test(context, "should have correct hashFunction", table->hashFunction == hashFunction);
    test(context, "should have correct destoryData function", table->destroyData == destroyData);
    test(context, "should have correct printData function", table->printData == printData);

    /* Testing: hashtable#insertData */
    section(context, "insertData");

    /* Testing: hashtable#lookupData */
    section(context, "lookupData");

    /* Testing: hashtable#removeData */
    section(context, "removeData");

    /* Testing: hashtable#destroyTable */
    section(context, "destroyTable");

    done(context);
    return context->failCount;
}

int hashFunction(size_t tableSize, int key)
{
    return -1;
}

void destroyData(void *data)
{
    free((char *) data);
}

void printData(void *data)
{
    printf("%s", (char *) data);
}
