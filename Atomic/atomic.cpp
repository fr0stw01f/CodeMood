/*************************************************************************
  >    File Name: atomic.cpp
  >       Author: tangzh
  >         Mail: tangzhnju@gmail.com 
  > Created Time: Wed 05 Jun 2013 07:08:07 PM CST
 ************************************************************************/

#include <atomic> 
#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <mutex>
#include <chrono>
#include <iomanip>
#include <tbb/atomic.h>
#include <gtest/gtest.h>

using namespace std;

#define TIME_STD(X) { \
	auto t0 = chrono::high_resolution_clock::now(); \
	{X;} \
	auto t1 = chrono::high_resolution_clock::now(); \
	cout << setw(10) << fixed << (double)chrono::duration_cast<chrono::nanoseconds>(t1-t0).count() / (double)1000000000 << " " << #X << endl; \
}

const int THREADS_COUNT = 100;
const int CLICK_COUNT = 10000;
//long total = 0; 
atomic_long total(0);
//tbb::atomic<long> total;
mutex m;

// 点击函数
void click()
{
	for(int i=0; i<CLICK_COUNT; ++i)
	{
		// 对全局数据进行无锁访问 
		++total;
	}
	//cout << "click" << endl;
}

void click_lock()
{
	for(int i=0; i<CLICK_COUNT; ++i)
	{
		// 对全局数据进行有锁访问
		lock_guard<mutex> _(m);
		++total;
	}
}

TEST(AtomicTest, atomic)
{
	auto simulation = []() {
		// 创建100个线程模拟点击统计
		vector<thread> threads(THREADS_COUNT);
		//threads.reserve(COUNT);
		for(int i=0; i<THREADS_COUNT; ++i) 
		{
			//threads.push_back(thread(click));
			threads[i] = thread(click);
		}
		for_each(begin(threads), end(threads), bind(&thread::join, placeholders::_1));
	};

	TIME_STD(simulation());

	// 输出结果
	cout<<"result:"<<total<<endl;
	//cout<<"duration:"<<finish -start<<"ms"<<endl;
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}


