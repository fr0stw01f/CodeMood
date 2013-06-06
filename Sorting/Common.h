/*************************************************************************
	> File Name: Common.h
	> Author: tangzh
	> Mail: tangzhnju@gmail.com 
	> Created Time: Wed 05 Jun 2013 05:22:16 PM CST
 ************************************************************************/

#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <iomanip>
#include <array>
#include <vector>
#include <cassert>
#include <algorithm>
#include <iterator>
#include <numeric>	// for iota
#include <chrono>

using namespace std;

namespace CodeMood {

const int M = 100000;

#define TIME_WIN(X) { \
	LARGE_INTEGER start, stop, freq; \
	QueryPerformanceCounter(&start); \
	{X;} \
	QueryPerformanceCounter(&stop); \
	QueryPerformanceFrequency(&freq); \
	double duration = (double)(stop.QuadPart - start.QuadPart) / (double)(freq.QuadPart); \
	cout << setw(10) << fixed << duration << " " << #X << endl; \
}

#define TIME_STD(X) { \
	auto t0 = chrono::high_resolution_clock::now(); \
	{X;} \
	auto t1 = chrono::high_resolution_clock::now(); \
	cout << setw(10) << fixed << (double)chrono::duration_cast<chrono::nanoseconds>(t1-t0).count() / (double)1000000000 << " " << #X << endl; \
}

void print(const vector<int>& vec)
{
	for (int i = 0; i < M; i++)
		cout << vec[i] << " ";
	cout << endl;
}

typedef void (*sorting_algorithm)(vector<int>& vec);

void test_sorting(sorting_algorithm algo, vector<int>& vec)
{
	//cout << "sort start" << endl;
	algo(vec);
	//cout << "sort end" << endl;
	//assert(is_sorted(begin(arr), end(arr)));
}

struct GenIota {
	GenIota(int i = 0) : i_(i)
	{}
	int operator()() 
	{
		return i_++;
	}
	int i_;
};

vector<int> generate_random(size_t start = 0)
{
	vector<int> vec(M);
	// 3 ways to generate 0...M
	/*for (int i = 0; i < M; ++i) {
		arr[i] = i;
	}*/
	iota(begin(vec), end(vec), 0);
	//generate(begin(arr), end(arr), GenIota());
	srand(0);
	random_shuffle(begin(vec) + start, end(vec));
	return vec;
}

}	//!namespace CodeMood

#endif	//!COMMON_H
