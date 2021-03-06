/**
 * @file hashtable.c
 * @author Kanoa Haley - 0956712 - khaley@mail.uoguelph.ca
 * @date June 18, 2017
 * @brief File containing the function implementations of a hash table
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HashTableAPI.h"

HTable *createTable(size_t size, int (*hashFunction)(size_t tableSize, char *key),void (*destroyData)(void *data),void (*printData)(void *toBePrinted))
{
    int i;
    HTable *table = malloc(sizeof(HTable));
    table->size = size;
    table->table = malloc(sizeof(Node *) * size);
    for (i = 0; i < size; i++) {
        table->table[i] = NULL;
    }
    table->destroyData = destroyData;
    table->hashFunction = hashFunction;
    table->printData = printData;
    return table;
}

Node *createNode(char *key, void *data)
{
    Node *node = malloc(sizeof(Node));
    node->next = NULL;
    node->key = key;
    node->data = data;
    return node;
}

void destroyTable(HTable *hashTable)
{
    int i;
    Node *tmp = NULL;
    Node *deleteNode = NULL;

    if (hashTable == NULL) {
        return;
    }

    for (i = 0; i < hashTable->size; i++) {
        tmp = hashTable->table[i];

        while (tmp != NULL) {
            deleteNode = tmp;
            tmp = tmp->next;
            hashTable->destroyData(deleteNode->data);
            free(deleteNode);
        }
    }

    free(hashTable->table);
    free(hashTable);
}

void insertData(HTable *hashTable, char *key, void *data)
{
    Node *node = NULL;
    Node *tmp = NULL;
    int index = -1;

    if (hashTable == NULL) {
        return;
    }

    index = hashTable->hashFunction(hashTable->size, key);
    if (index < 0 || index >= hashTable->size) {
        return;
    }
    node = createNode(key, data);

    if (hashTable->table[index] == NULL || strcmp(hashTable->table[index]->key, key) == 0) {
        hashTable->table[index] = node;
    } else {
        tmp = hashTable->table[index];
        while (tmp->next != NULL) {
            tmp = tmp->next;
        }
        tmp->next = node;
    }
}

void removeData(HTable *hashTable, char *key)
{
    Node *node = NULL;
    Node *previous = NULL;
    int index = -1;

    if (hashTable == NULL) {
        return;
    }

    index = hashTable->hashFunction(hashTable->size, key);
    if (index < 0 || index >= hashTable->size) {
        return;
    }
    node = hashTable->table[index];

    if (node == NULL) {
        return;
    }

    previous = NULL;
    while (strcmp(node->key, key) != 0) {
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

void *lookupData(HTable *hashTable, char *key)
{
    Node *node = NULL;
    int index = -1;

    if (hashTable == NULL) {
        return NULL;
    }

    index = hashTable->hashFunction(hashTable->size, key);
    if (index < 0 || index >= hashTable->size) {
        return NULL;
    }
    node = hashTable->table[index];

    if (node == NULL) {
        return NULL;
    }

    while (node != NULL) {
        if (strcmp(node->key, key) == 0) {
            return node->data;
        }
        node = node->next;
    }

    return NULL;
}
