/*************************************************************************
	> File Name: HeapSort.h
	> Author: tangzh
	> Mail: tangzhnju@gmail.com 
	> Created Time: Wed 05 Jun 2013 05:24:35 PM CST
 ************************************************************************/

#ifndef HEAP_SORT_H
#define HEAP_SORT_H

#include "Common.h"

namespace CodeMood {

void heapify(vector<int>& vec, int i, int heap_size)
{
	int l = 2*i, r = 2*i+1, largest = i;
	if (l <= heap_size && vec[l] > vec[i])
		largest = l;
	if (r <= heap_size && vec[r] > vec[largest])
		largest = r;

	if (largest != i) {
		swap(vec[i], vec[largest]);
		heapify(vec, largest, heap_size);
	}
}

void build_heap(vector<int>& vec)
{
	int i = (M-1)/2;
	for ( ; i >= 1; --i)
		heapify(vec, i, M-1);
}

void heap_sort(vector<int>& vec)
{
	build_heap(vec);
	for (int i = M-1; i > 1; --i) {
		swap(vec[1], vec[i]);
		heapify(vec, 1, i-1);
	}
}

} //!namespace CodeMood

#endif //!HEAP_SORT_H
