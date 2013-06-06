/*************************************************************************
	>    File Name: ExceptionSafe.cpp
	>       Author: tangzh
	>         Mail: tangzhnju@gmail.com 
	> Created Time: Wed 05 Jun 2013 06:30:16 PM CST
 ************************************************************************/

#include <iostream>
#include <string>
#include <memory>
#include <array>
#include <vector>
#include <algorithm>

using namespace std;

namespace CodeMood {
class Inner {
public:
	static int count;
	Inner() : data_(0)
	{
		cout << "Inner ctor~" << endl;
		//if (++count == 3)
			//throw "exception on purpose";
	}
	~Inner()
	{
		cout << "Inner dtor~" << endl;
	}
private:
	int data_;
};
int Inner::count = 0;

class Stack {
public:
	Stack() : inner_(new Inner[10]), size_(10)
	{
		cout << "Stack ctor~" << endl;
		throw "Stack ctor exception";
	}
	~Stack()
	{
		cout << "Stack dtor~" << endl;
	}
private:
	Stack(const Stack&);			//noncopyable
	Stack& operator=(const Stack&);	//nonassignable
	Inner *inner_;
	//unique_ptr<Inner[]> inner_;
	//array<Inner, 10> inner_;
	int size_;
};

class Assert
{
public:
	Assert(string expr) : SMART_ASSERT_A(*this), SMART_ASSERT_B(*this), expr_(expr)
	{

	}
	// If copy constructor is left default, this class won't work well
	// because SMART_ASSERT_A and SMART_ASSERT_B don't point to current object but the original one.
	Assert(const Assert& ass) : SMART_ASSERT_A(*this), SMART_ASSERT_B(*this), expr_(ass.expr_)
	{

	}
	Assert& SMART_ASSERT_A;
	Assert& SMART_ASSERT_B;
	// whatever member functions
	template<class T>
	Assert& print_current_val(T& val, const char* var)
	{
		cout << "\t" << var << " = " << val << "\n";  
		return *this;
	}
	// partial specialization for vector
	template<class T>
	Assert& print_current_val(vector<T>& vi, const char* str2)
	{
		cout << "\t" << str2 << " = [";
		for_each(begin(vi), end(vi), [](T& x){
			cout << x << ",";
		});
		cout << "]\n";  
		return *this;
	}
	Assert& print_context(const char* file, int line)
	{
		string filename = file;
		cout << "\nAssertion failed in " << filename.substr(filename.find_last_of("\\")+1) << ": " << line << "\n"
			 << "Expression: \"" << expr_ << "\"\n"
			 << "Values:";  
		return *this;
	}
private:
	Assert& operator=(const Assert&);	//nonassignable
	string expr_;
};

// copy constructor called implicitly
Assert make_assert(const char* expr) {
	return Assert(expr);
}

#define SMART_ASSERT_A(x) SMART_ASSERT_OP(x, B)
#define SMART_ASSERT_B(x) SMART_ASSERT_OP(x, A)
#define SMART_ASSERT_OP(x, next) \
	SMART_ASSERT_A.print_current_val((x), #x).SMART_ASSERT_ ## next

#define SMART_ASSERT(expr) \
	if ( (expr) ) ; \
	else make_assert(#expr).print_context( __FILE__, __LINE__).SMART_ASSERT_A

#define ENSURE SMART_ASSERT


class ExceptionWithMiniDump {
public:
	string GetMiniDumpFilePath()
	{
		return dump_file_path_;
	}
private:
	string dump_file_path_;
};


void LaunchProblemReporter(ExceptionWithMiniDump& ex, string filepath)
{

}
void LaunchProblemReporter(std::exception& ex, string errstr)
{

}
void LaunchProblemReporter(string errstr)
{

}

inline void ReportCxxException(std::exception_ptr ex_ptr)
{
	try
	{
		std::rethrow_exception(ex_ptr);
	}
	catch(ExceptionWithMiniDump& ex)
	{
		LaunchProblemReporter(ex, ex.GetMiniDumpFilePath());
	}
	catch(std::exception& ex)
	{
		LaunchProblemReporter(ex, ex.what());
	}
	catch(...)
	{
		LaunchProblemReporter("Unknown C++ Exception");
	}
}
}

int main(int argc, char* argv[])
{
	using namespace CodeMood;
	try {
		Stack stack;
	}
	catch (const char* str)
	{
		cout << str << endl;
	}
	string s1 = "abc", s2 = "123";
	bool b = true;
	vector<int> vi;
	vi.push_back(100);
	vi.push_back(200);

	// A very useful debug tool like Assert, but with more dump info
	// created by Andrei Alexandrescu and adopted by pongba
	ENSURE(!s1.empty() && !s2.empty() && b && vi.empty())(s1)(s2)(b)(vi);

	cout << endl;
	return 0;
}


