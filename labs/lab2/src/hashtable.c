/**
 * @file hashtable.c
 * @author Kanoa Haley
 * @date June 18, 2017
 * @brief File containing the function implementations of a hash table
 */
#include <stdio.h>
#include <stdlib.h>
#include "HashTableAPI.h"

HTable *createTable(size_t size, int (*hashFunction)(size_t tableSize, int key),void (*destroyData)(void *data),void (*printData)(void *toBePrinted))
{
    HTable *table = malloc(sizeof(HTable));
    table->size = size;
    table->table = malloc(sizeof(Node *) * size);
    table->destroyData = destroyData;
    table->hashFunction = hashFunction;
    table->printData = printData;
    return table;
}

Node *createNode(int key, void *data)
{
    Node *node = malloc(sizeof(Node));
    node->next = NULL;
    node->key = key;
    node->data = data;
    return node;
}

void destroyTable(HTable *hashTable)
{
    if (hashTable == NULL) {
        return;
    }

    int i;
    for (i = 0; i < hashTable->size; i++) {
        Node *tmp = hashTable->table[i];

        while (tmp != NULL) {
            Node *deleteNode = tmp;
            tmp = tmp->next;
            hashTable->destroyData(deleteNode->data);
            free(deleteNode);
        }
    }

    free(hashTable->table);
    free(hashTable);
}

void insertData(HTable *hashTable, int key, void *data)
{
    if (hashTable == NULL) {
        return;
    }

    Node *node = createNode(key, data);
    int index = hashTable->hashFunction(hashTable->size, key);

    if (hashTable->table[index] == NULL || hashTable->table[index]->key == key) {
        hashTable->table[index] = node;
    } else {
        Node *tmp = hashTable->table[index];
        while (tmp->next != NULL) {
            tmp = tmp->next;
        }
        tmp->next = node;
    }
}

void removeData(HTable *hashTable, int key)
{
    if (hashTable == NULL) {
        return;
    }

    int index = hashTable->hashFunction(hashTable->size, key);
    Node *node = hashTable->table[index];

    if (node == NULL) {
        return;
    }

    Node *previous = NULL;
    while (node->key != key) {
        if (node->next == NULL) {
            return;
        }
        previous = node;
        node = node->next;
    }

    if (previous == NULL) {
        hashTable->table[index] = node->next;
    } else {
        previous->next = node->next;
    }

    hashTable->destroyData(node->data);
    free(node);
}

void *lookupData(HTable *hashTable, int key)
{
    if (hashTable == NULL) {
        return NULL;
    }

    int index = hashTable->hashFunction(hashTable->size, key);
    Node *node = hashTable->table[index];

    if (node == NULL) {
        return NULL;
    }

    while (node != NULL) {
        if (node->key == key) {
            return node->data;
        }
        node = node->next;
    }
}
