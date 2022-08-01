#ifndef HELPERS_LINKEDLIST_H
#define HELPERS_LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <core/constants.h>

typedef struct node
{
    void* data;
    struct node* next;
} Node;

#define forEach(item, list) \
    for(Node * item = list->head; item != NULL; item = item->next)

typedef struct linkedlist
{
    Node* head;
    int size;
} LinkedList;

LinkedList* createLinkedList();
Node* createNode(void* data);
void pushLinkedList(LinkedList* linkedlist, Node* node);

void linkedListDestroyRecursivelyNodes(Node** node);
void destroyLinkedList(LinkedList** linkedlist);

int linkedListMemoryAllocated(LinkedList* linkedList);
#endif