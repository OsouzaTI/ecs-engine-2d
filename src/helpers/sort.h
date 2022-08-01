#ifndef SORT_H
#define SORT_H

#include <stdio.h>

#define VOFFSET(i, s) (i * s)

typedef int(ComparationSortFunction)(void*, void*);
typedef void(SwapSortFunction)(void*, void*);

// quick sort
int _partition(void* V, int lo, int hi, int size, ComparationSortFunction cmp, SwapSortFunction swp);
void quickSort(void* V, int lo, int hi, int size, ComparationSortFunction cmp, SwapSortFunction swp);

int _partitionDPointer(void** V, int lo, int hi, ComparationSortFunction cmp, SwapSortFunction swp);
void quickSortDPointer(void** V, int lo, int hi, ComparationSortFunction cmp, SwapSortFunction swp);

#endif