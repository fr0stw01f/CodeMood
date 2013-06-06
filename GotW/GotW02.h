/*************************************************************************
	>    File Name: GotW02.h
	>       Author: tangzh
	>         Mail: tangzhnju@gmail.com 
	> Created Time: Wed 05 Jun 2013 06:38:52 PM CST
 ************************************************************************/

#ifndef GOTW02_H
#define GOTW02_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <sstream>
#include <functional>
#include <chrono>

using namespace std;

namespace CodeMood {

#define COUNT 10000		// loop count
#define EMPS  10000		// emps size

#define TIME(X) { \
	auto t0 = chrono::high_resolution_clock::now(); \
	{X;} \
	auto t1 = chrono::high_resolution_clock::now(); \
	cout << setw(10) << fixed << (double)chrono::duration_cast<chrono::nanoseconds>(t1-t0).count() / (double)1000000000 << " " << #X << endl; \
}

struct Employee {
	Employee(const string& name, const string& addr)
		: name_(name), addr_(addr)
	{}
	~Employee()
	{
		++count_;
	}
	static long long count_;
	string name_;
	string addr_;
};

long long Employee::count_ = 0;

typedef string (*find_addr_func)(const vector<Employee>&, const string&);

// original for loop
string find_addr_01(const vector<Employee>& emps, const string& name)
{
	auto emps_end = end(emps);
	for (auto iter = begin(emps); iter != emps_end; ++iter) {
		if (iter->name_ == name) {
			return iter->addr_;
		}
	}
	return "";
}

// Range-based for loop(since C++11)
string find_addr_02(const vector<Employee>& emps, const string& name)
{
	for (const auto& employee : emps) {
		if (employee.name_ == name) {
			return employee.addr_;
		}
	}
	return "";
}

// find_if with lambda expression
string find_addr_03(const vector<Employee>& emps, const string& name){
	const auto& iter = find_if(begin(emps), end(emps), [&](const Employee& employee) -> bool {
		return employee.name_ == name;
	});
	return iter != end(emps) ? iter->addr_ : "";
}

// original for loop without if inside while
string find_addr_04(const vector<Employee>& emps, const string& name)
{
	auto iter = begin(emps);
	while (iter != end(emps) && iter->name_ != name) ++iter;
	return iter != end(emps) ? iter->addr_ : "";
}

// function object
struct EmpCompare {
	EmpCompare(const string& name) : name_(name)
	{}
	bool operator()(const Employee& emp)
	{
		return emp.name_ == name_;
	}
	string name_;
};

// find_if with function object
string find_addr_05(const vector<Employee>& emps, const string& name){
	const auto& iter = find_if(begin(emps), end(emps), EmpCompare(name));
	return iter != end(emps) ? iter->addr_ : "";
}

bool emp_compare(const Employee& emp, const string& name)
{
	return emp.name_ == name;
}

// find_if with bind and function pointer
string find_addr_06(const vector<Employee>& emps, const string& name){
	const auto& iter = find_if(begin(emps), end(emps), bind(emp_compare, placeholders::_1, name));
	return iter != end(emps) ? iter->addr_ : "";
}

void test_average(const vector<Employee>& emps,  find_addr_func find_addr)
{
	for (int i = 0; i < COUNT; i++) {
		string addr = find_addr(emps, "name5000");
		assert(addr == "addr5000");
	}
}

}	// end of namespace CodeMood

#endif // !GOTW02_H

