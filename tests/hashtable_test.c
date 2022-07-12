#include <stdio.h>
#include "hashtable.h"

int main(void)
{
    HashTable* hashtable = createHashTable(10);
    for (int i = 0; i < 20; i++)
    {
        char buff[255];
        sprintf(buff, "Teste asset path %d", i);
        addHashTable(&hashtable, "cahve1", buff);
    }
    

    printHashTable(hashtable);
    return 0;
}