/*************************************************************************
	> File Name: QuickSort.h
	> Author: tangzh
	> Mail: tangzhnju@gmail.com 
	> Created Time: Wed 05 Jun 2013 05:26:03 PM CST
 ************************************************************************/

#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include "Common.h"

namespace CodeMood {

int partition(vector<int>& vec, int l, int r)
{
	int i = l - 1, j = l;
	while (j < r) {
		while (vec[j] > vec[r]) ++j;
		if (j < r)
			swap(vec[++i], vec[j++]);
	}
	swap(vec[++i], vec[r]);
	return i;
}

void quick_sort(vector<int>& vec, int l, int r)
{
	int pivot = partition(vec, l, r);
	if (pivot > l + 1)
		quick_sort(vec, l, pivot - 1);
	if (pivot < r - 1)
		quick_sort(vec, pivot + 1, r);
}

void quick_sort(vector<int>& vec)
{
	quick_sort(vec, 0, M - 1);
}

}	//!namespace CodeMood

#endif	//!QUICK_SORT_H
