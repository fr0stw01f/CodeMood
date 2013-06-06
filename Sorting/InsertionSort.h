/*************************************************************************
	> File Name: InsertionSort.h
	> Author: tangzh
	> Mail: tangzhnju@gmail.com 
	> Created Time: Wed 05 Jun 2013 05:25:30 PM CST
 ************************************************************************/

#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

#include "Common.h"

namespace CodeMood {

void insertion_sort(vector<int>& vec)
{
	for (int i = 1; i < M; ++i) {
		int tmp = vec[i];
		int j = i - 1;
		for (; j >= 0 && vec[j] > tmp; --j) {
			vec[j+1] = vec[j];
		}
		vec[j+1] = tmp;
	}
}

} //!namespace CodeMood

#endif //!INSERTION_SORT_H
