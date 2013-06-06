/*************************************************************************
	> File Name: Sorting.cpp
	> Author: tangzh
	> Mail: tangzhnju@gmail.com 
	> Created Time: Wed 05 Jun 2013 05:04:06 PM CST
 ************************************************************************/

#include <gtest/gtest.h>

#include "QuickSort.h"
#include "InsertionSort.h"
#include "HeapSort.h"

using namespace CodeMood;

TEST(SortingTest, insertion_sort)
{
	vector<int> vec = generate_random();	
	TIME_STD(test_sorting(insertion_sort, vec));
	EXPECT_TRUE(is_sorted(begin(vec), end(vec)));
}

TEST(SortingTest, heap_sort)
{
	vector<int> vec = generate_random(1);
	TIME_STD(test_sorting(heap_sort, vec));
	EXPECT_TRUE(is_sorted(begin(vec), end(vec)));
}

TEST(SortingTest, quick_sort)
{
	vector<int> vec = generate_random();	
	TIME_STD(test_sorting(quick_sort, vec));
	EXPECT_TRUE(is_sorted(begin(vec), end(vec)));
}

TEST(SortingTest, std_sort)
{
	vector<int> vec = generate_random();	
	TIME_STD(std::sort(begin(vec), end(vec)));
	EXPECT_TRUE(is_sorted(begin(vec), end(vec)));
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
