#include "linkedlist.h"

int main() {
    LinkedList* l = createLinkedList();
    int V[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++)
    {
        Node* node = createNode((void*)V[i]);
        pushLinkedList(l, node);        
    }
    destroyLinkedList(&l);
    return 0;
}