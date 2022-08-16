#include "sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int _partition(void* V, int lo, int hi, int size, ComparationSortFunction cmp, SwapSortFunction swp)
{
    int i = lo + 1;
    int j = hi;
    while(1)
    {
        while(cmp(V+VOFFSET(i,size), V+VOFFSET(lo,size)) == -1)
        {
            i++;
            if(i >= hi) break;
        }

        while (cmp(V+VOFFSET(j,size), V+VOFFSET(lo,size)) >= 0)
        {
            j--;
            if(j == lo) break;
        }
        
        if(i >= j) break;
        swp(V+VOFFSET(i,size), V+VOFFSET(j,size));
        
    }
    swp(V+VOFFSET(lo,size), V+VOFFSET(j,size));
    return j;
}

void quickSort(void* V, int lo, int hi, int size, ComparationSortFunction cmp, SwapSortFunction swp) 
{

    if(lo >= hi) return;

    int p = _partition(V, lo, hi, size, cmp, swp);
    quickSort(V, lo, p - 1, size, cmp, swp);
    quickSort(V, p + 1, hi, size, cmp, swp);

}

int _partitionDPointer(void** V, int lo, int hi, ComparationSortFunction cmp, SwapSortFunction swp){
    int i = lo + 1;
    int j = hi;
    while(1)
    {
        while(cmp(V[i], V[lo]) == -1)
        {
            i++;
            if(i >= hi) break;
        }

        while (cmp(V[j], V[lo]) >= 0)
        {
            j--;
            if(j == lo) break;
        }
        
        if(i >= j) break;
        swp(V[i], V[j]);
        
    }
    swp(V[lo], V[j]);
    return j;
}

void quickSortDPointer(void** V, int lo, int hi, ComparationSortFunction cmp, SwapSortFunction swp) {
    if(lo >= hi) return;
    int p = _partitionDPointer(V, lo, hi, cmp, swp);
    quickSortDPointer(V, lo, p - 1, cmp, swp);
    quickSortDPointer(V, p + 1, hi, cmp, swp);
}

void mergeSort(Node** headRef) {
    Node* head = *headRef;
    Node* a;
    Node* b;
  
    /* Base case -- length 0 or 1 */
    if ((head == NULL) || (head->next == NULL)) {
        return;
    }
  
    /* Split head into 'a' and 'b' sublists */
    frontBackSplit(head, &a, &b);
  
    /* Recursively sort the sublists */
    mergeSort(&a);
    mergeSort(&b);
  
    /* answer = merge the two sorted lists together */
    *headRef = sortedMerge(a, b);
}


Node* sortedMerge(Node* a, Node* b){
    Node* result = NULL;
  
    /* Base cases */
    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);
  
    /* Pick either a or b, and recur */
    Object2D* _a = (Object2D*)a->data;
    Object2D* _b = (Object2D*)b->data;
    if (_a->layer <= _b->layer) {
        result = a;
        result->next = sortedMerge(a->next, b);
    }
    else {
        result = b;
        result->next = sortedMerge(a, b->next);
    }
    return (result);        
}

void frontBackSplit(Node* source, Node** frontRef, Node** backRef) {
    Node* fast;
    Node* slow;
    slow = source;
    fast = source->next;
  
    /* Advance 'fast' two nodes, and advance 'slow' one node */
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }
  
    /* 'slow' is before the midpoint in the list, so split it in two 
    at that point. */
    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
}

#ifdef SORT_DEBUG
typedef struct teste
{
    int id;
    float speed;
} Teste;

int cmp(void* a, void* b) {
    Teste* _a = (Teste*)a;
    Teste* _b = (Teste*)b;    
    if(_a->id > _b->id){
        return 1;
    } else if (_a->id < _b->id) {
        return -1;
    } 
    return  0;
}

void swp(void* a, void* b) {
    Teste* _a = (Teste*)a;
    Teste* _b = (Teste*)b;  
    Teste temp = *_a;
    *_a = *_b;
    *_b = temp;
}

int main() {
    srand(time(NULL));
    Teste array[10];
    for (int i = 0; i < 10; i++)
    {
        array[i].id = rand()%255;
    }
	
    quickSort((void*)array, 0, 9, sizeof(Teste), cmp, swp);
    // qsort((void*)array, 10, sizeof(Teste), cmp);

	for(int i = 0; i < 10; i++)
	{
		printf("%d ", array[i].id);
	}

    return 0;
}
#endif