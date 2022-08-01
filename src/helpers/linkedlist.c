#include "linkedlist.h"

LinkedList* createLinkedList() {
    LinkedList* linkedlist = (LinkedList*)malloc(sizeof(LinkedList));
    if(linkedlist == NULL){
        printf("Erro ao alocar memoria para lista lincada.\n");
    }
    linkedlist->size = 0;
    return linkedlist;
}

Node* createNode(void* data) {
    Node* node = (Node*)malloc(sizeof(Node));
    if(node == NULL){
        printf("Erro ao alocar memoria para node da lista lincada.\n");
    }

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

void linkedListDestroyRecursivelyNodes(Node** node) {
    if(ISNULL(*node))
        return;
    linkedListDestroyRecursivelyNodes(&(*node)->next);
    free(*node);
    *node = NULL;
}

void destroyLinkedList(LinkedList** linkedlist) {
    Node* n = (*linkedlist)->head;
    linkedListDestroyRecursivelyNodes(&n);
    free(linkedlist);
}

int linkedListMemoryAllocated(LinkedList* linkedList) {
    if(linkedList == NULL) {
        return 0;
    } 
    return sizeof(LinkedList) + (sizeof(Node) * linkedList->size);
}