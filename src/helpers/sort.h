#ifndef SORT_H
#define SORT_H

#include <stdio.h>
#include <helpers/linkedlist.h>
#include <objects/object2d.h>

#define VOFFSET(i, s) (i * s)

typedef int(ComparationSortFunction)(void*, void*);
typedef void(SwapSortFunction)(void*, void*);

// quick sort
int _partition(void* V, int lo, int hi, int size, ComparationSortFunction cmp, SwapSortFunction swp);
void quickSort(void* V, int lo, int hi, int size, ComparationSortFunction cmp, SwapSortFunction swp);

int _partitionDPointer(void** V, int lo, int hi, ComparationSortFunction cmp, SwapSortFunction swp);
void quickSortDPointer(void** V, int lo, int hi, ComparationSortFunction cmp, SwapSortFunction swp);

// merge sort for linkedlists
void mergeSort(Node** head);
Node* sortedMerge(Node* a, Node* b);
void frontBackSplit(Node* source, Node** front, Node** back);

#endif