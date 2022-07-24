#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdlib.h>
#define ISNULL(x) (x == NULL)
#define NOTNULL(x) !ISNULL(x)

typedef struct node
{
    void* data;
    struct node* next;
} Node;


typedef struct linkedlist
{
    Node* head;
    int size;
} LinkedList;

LinkedList* createLinkedList();
Node* createNode(void* data);
void pushLinkedList(LinkedList* linkedlist, Node* node);

void linkedListDestroyRecursivelyNodes(Node* node);
void destroyLinkedList(LinkedList** linkedlist);
#endif