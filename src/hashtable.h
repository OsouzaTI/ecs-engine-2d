#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"

typedef struct hashNode {
    char key[255];
    char* value;
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
void freeHashTable(HashTable* hashtable);
void addHashNode(HashTable** hashTable, const char* key, const char* value);
HashNode* findHashNode(HashTable* hashTable,const char* key);
void printHashTable(HashTable* hashTable);

#endif