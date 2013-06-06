/*************************************************************************
	>    File Name: ParallelSort.cpp
	>       Author: tangzh
	>         Mail: tangzhnju@gmail.com 
	> Created Time: Wed 05 Jun 2013 09:02:03 PM CST
 ************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cassert>
#include <chrono>
#include <iomanip>
#include <tbb/task_scheduler_init.h>
#include <tbb/parallel_sort.h>

using namespace std;

const int SIZE = 10000000;

#define TIME_STD(X) { \
	auto t0 = chrono::high_resolution_clock::now(); \
	{X;} \
	auto t1 = chrono::high_resolution_clock::now(); \
	cout << setw(10) << fixed << (double)chrono::duration_cast<chrono::nanoseconds>(t1-t0).count() / (double)1000000000 << "ms " << #X << endl; \
}

int main(int argc, char* argv[])
{
	vector<int> vec_int(SIZE);
	iota(begin(vec_int), end(vec_int), 0);
	srand(0);
	random_shuffle(begin(vec_int), end(vec_int));
	
	//TIME_STD(sort(begin(vec_int), end(vec_int)));
	TIME_STD(tbb::task_scheduler_init _; tbb::parallel_sort(begin(vec_int), end(vec_int)));
	assert(is_sorted(begin(vec_int), end(vec_int)));

	return 0;
}


