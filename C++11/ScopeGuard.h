/*************************************************************************
	> File Name: ScopeGuard.h
	> Author: tangzh
	> Mail: tangzhnju@gmail.com 
	> Created Time: Wed 05 Jun 2013 06:19:02 PM CST
 ************************************************************************/

#ifndef SCOPEGUARD_H
#define SCOPEGUARD_H

#include <functional>

using namespace std;

// This class is taken from mindhacks.cn.
// http://mindhacks.cn/2012/08/27/modern-cpp-practices/
// It is used to manage resources with RAII just like smart pointers.
// The deference between them is that smart pointers manage memory resources
// and ScopeGuard manage other common resources.
// This is a uniform paradigm to manage resources.
namespace CodeMood {
	class ScopeGuard
	{
	public:
		ScopeGuard(function<void()>);
		~ScopeGuard();
		void Dismiss();
	private:
		function<void()> onScopeExit_;
		bool dismissed_;
	private:
		ScopeGuard(const ScopeGuard&);
		ScopeGuard& operator=(const ScopeGuard&);
	};
}

#endif //SCOPEGUARD_H



