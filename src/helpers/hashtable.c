#include "hashtable.h"

int stringHash(const char* str, int M) {
    unsigned h = 0;
    for (int i = 0; str[i] != '\0'; i++) 
        h = (h * 256 + str[i]) % M;
    return h;
}

void freeHashTable(HashTable* hashtable) {
    for (int i = 0; i < hashtable->N; i++)
    {
        if(hashtable->data[i] != NULL) {
            free(hashtable->data[i]);
        }
    }
    free(hashtable->data);
}

HashTable* createHashTable(int N) {
    HashTable* hashtable = (HashTable*)malloc(sizeof(HashTable));
    if(hashtable == NULL){
        printf("Erro ao alocar memoria para tabela hash.\n");
    }

    hashtable->size = 0;
    hashtable->N = N;
    hashtable->data = (HashNode**)malloc(sizeof(HashNode*) * N);
    for (int i = 0; i < N; i++)
        hashtable->data[i] = NULL;
    return hashtable;    
}

void rehashing(HashTable** hashtable) {
    HashTable* oldHashTable = *hashtable;
    HashTable* newHashTable = createHashTable(oldHashTable->N * 1.947);
    // passando todos os valores antigos
    for (int i = 0; i < oldHashTable->N; i++)
    {
        if(oldHashTable->data[i] != NULL)
            addHashNode(&newHashTable, oldHashTable->data[i]->key, oldHashTable->data[i]->value);
    }
    // limpando a antiga tabela hash
    freeHashTable(oldHashTable);
    *hashtable = newHashTable;
}

void rehashingGenericNodes(HashTable** hashtable) {
    HashTable* oldHashTable = *hashtable;
    HashTable* newHashTable = createHashTable(oldHashTable->N * 1.947);
    // passando todos os valores antigos
    for (int i = 0; i < oldHashTable->N; i++)
    {
        if(oldHashTable->data[i] != NULL)
            addGenericHashNode(&newHashTable, oldHashTable->data[i]->key, oldHashTable->data[i]->data);
    }
    // limpando a antiga tabela hash
    freeHashTable(oldHashTable);
    *hashtable = newHashTable; 
}

void addHashNode(HashTable** hashTable, const char* key, const char* value) {
    HashTable* myHashTable = *hashTable;

    int code = stringHash(key, myHashTable->N);
        
    // detectando colisao
    if(myHashTable->data[code] != NULL) {
        int index = code;
        while(1) {
            // encontrou posicao valida
            if(ISNULL(myHashTable->data[index])) {
                myHashTable->data[index] = (HashNode*)malloc(sizeof(HashNode));
                myHashTable->data[index]->value = (char*)malloc(sizeof(char) * strlen(value));
                strcpy(myHashTable->data[index]->key, key);
                strcpy(myHashTable->data[index]->value, value);
                myHashTable->size++;
                break;
            } else {
                index++;
                index %= myHashTable->N;
            }
        }
    } else {
        myHashTable->data[code] = (HashNode*)malloc(sizeof(HashNode));
        myHashTable->data[code]->value = (char*)malloc(sizeof(char) * strlen(value));
        strcpy(myHashTable->data[code]->key, key);
        strcpy(myHashTable->data[code]->value, value);
        myHashTable->size++;
    }

    if((myHashTable->size / (float)myHashTable->N) > .75)
        rehashing(hashTable);
}

void addGenericHashNode(HashTable** hashTable, const char* key, void* data) {
    HashTable* myHashTable = *hashTable;

    int code = stringHash(key, myHashTable->N);
        
    // detectando colisao
    if(myHashTable->data[code] != NULL) {
        int index = code;
        while(1) {
            // encontrou posicao valida
            if(ISNULL(myHashTable->data[index])) {
                myHashTable->data[index] = (HashNode*)malloc(sizeof(HashNode));
                myHashTable->data[index]->data = data;
                strcpy(myHashTable->data[index]->key, key);                
                myHashTable->size++;
                break;
            } else {
                index++;
                index %= myHashTable->N;
            }
        }
    } else {
        myHashTable->data[code] = (HashNode*)malloc(sizeof(HashNode));
        myHashTable->data[code]->data = data;
        strcpy(myHashTable->data[code]->key, key);        
        myHashTable->size++;
    }

    if((myHashTable->size / (float)myHashTable->N) > .75)
        rehashing(hashTable);
}

HashNode* findHashNode(HashTable* hashTable,const char* key){
    int code = stringHash(key, hashTable->N);    
    HashNode* hashNode = hashTable->data[code];  
    if(ISNULL(hashNode)) {
        return NULL;
    } 
    
    if(strcmp(key, hashNode->key) != 0) {
        for (int i = code+1; i <= hashTable->size; i++)
        {
            hashNode = hashTable->data[i];
            if(strcmp(key, hashNode->key) == 0){
                return hashNode;
            }
        }        
    } else {
        return hashNode;        
    }

    return NULL;
}

void printHashTable(HashTable* hashTable) {
    for (int i = 0; i < hashTable->N; i++){
        if(hashTable->data[i] != NULL)
            printf("[%d]: %s | %s | %p\n", i, hashTable->data[i]->key, hashTable->data[i]->value , hashTable->data[i]->data);
        else
            printf("[%d]: NULL\n", i);
    }
}

int hashTableMemoryAllocated(HashTable* hashTable) {
    if(hashTable == NULL) {
        return 0;
    }
    return sizeof(HashTable) + (sizeof(HashNode) * hashTable->size) + (sizeof(HashNode**) * hashTable->N);
}