#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <core/constants.h>

typedef struct hashNode {
    char key[255];
    char* value;
    void* data;
} HashNode;

typedef struct hashtable
{
    // tamanho da tabela hash
    int N;
    // items inseridos
    int size;
    // lista de HashNode
    HashNode** data;
} HashTable;

HashTable* createHashTable(int N);
void rehashing(HashTable** hashtable);
void rehashingGenericNodes(HashTable** hashtable);
void freeHashTable(HashTable* hashtable);
void addHashNode(HashTable** hashTable, const char* key, const char* value);
void addGenericHashNode(HashTable** hashTable, const char* key, void* data);
HashNode* findHashNode(HashTable* hashTable,const char* key);
void printHashTable(HashTable* hashTable);
int hashTableMemoryAllocated(HashTable* hashTable);
#endif