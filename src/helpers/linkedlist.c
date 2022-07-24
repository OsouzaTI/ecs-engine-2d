#include "linkedlist.h"

LinkedList* createLinkedList() {
    LinkedList* linkedlist = (LinkedList*)malloc(sizeof(LinkedList));
    linkedlist->size = 0;
    return linkedlist;
}

Node* createNode(void* data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    return node;
}


void pushLinkedList(LinkedList* linkedlist, Node* node) {
    if(linkedlist->size == 0) {
        linkedlist->head = node;
    } else {
        Node* aux;
        for(aux = linkedlist->head; NOTNULL(aux->next); aux = aux->next);
        aux->next = node;
    }
    linkedlist->size++;
}

void linkedListDestroyRecursivelyNodes(Node* node) {
    if(ISNULL(node))
        return;
    linkedListDestroyRecursivelyNodes(node->next);
    free(node);
    node = NULL;
}

void destroyLinkedList(LinkedList** linkedlist) {
    Node* n = (*linkedlist)->head;
    linkedListDestroyRecursivelyNodes(n);
    free(linkedlist);
}