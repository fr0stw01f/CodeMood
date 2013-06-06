/*************************************************************************
	>    File Name: main.cpp
	>       Author: tangzh
	>        Email: tangzhnju@gmail.com 
	> Created Time: Mon 03 Jun 2013 09:13:53 PM CST
 ************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <memory>
#include <functional>
#include "ScopeGuard.h"

using namespace std;

namespace CodeMood {
	// decltype
	template<class T1, class T2>
	auto add(T1 t1, T2 t2) -> decltype(t1 + t2)
	{
		return t1 + t2;
	}

	class Node {
	public:
		// Default Constructor
		Node(int data = 0, Node* next = nullptr) : data_(data), next_(next)
		{
			cout << "ctor" << endl;
		}
		// Copy Constructor
		Node(const Node& node) : data_(node.data_), next_(node.next_)
		{
			cout << "cpctor" << endl;
		}
		// Move Constructor
		Node(Node&& node) : data_(node.data_), next_(node.next_)
		{
			cout << "mvctor" << endl;
		}
		// operator= must be a member function
		// a = b = c is legal
		// (a = b) = c is illegal
		const Node& operator=(const Node& node) {
			this->data_ = node.data_;
			this->next_ = node.next_;
			return *this;
		}
		// Destructor
		~Node()
		{
			cout << "dtor" << endl;
		}
	private:
		int		data_;
		Node*	next_;
	};

	// Move semantics
	Node getNode(int data = 0, Node* next = nullptr) {
		Node node(data, next);
		return node;	// Destructor will still be called.
	}

	// Member function templates cannot be virtual
	template<class T1>
	class XXOO {
		//template<class T2>
		virtual int xxoo2(T1) = 0;
	};

	class Shape {
	public:
		void bb() {}
		virtual void aa(int x) {
			cout << "Shape::aa " << x << endl;
		}
		virtual void draw() {
			cout << "Shape draw" << endl;
		}
	};

	class Square : public Shape {
	public:
		virtual void xx() {}
		virtual void draw() {
			cout << "Square draw" << endl;
		}
	};

	class Circle : public Shape {
	public:
		virtual void xx() {}
		virtual void draw() {
			cout << "Circle draw" << endl;
		}
	};
	
	class ClassPureVirtulaDtor {
	public:
		virtual ~ClassPureVirtulaDtor() = 0;
	};
	// Pure virtual function can be implemented.
	// The class itself cannot be instantiated, but its subclass can use it.
	ClassPureVirtulaDtor::~ClassPureVirtulaDtor() {
		cout << "fuck pure virtual dtor" << endl;
	}

	class ClassA : ClassPureVirtulaDtor {
	public:
		~ClassA() {
			cout << "fuck others" << endl;
		}
	};

	struct A {
		int a;
		virtual void print()
		{
			cout << "A" << endl;
		}
	};

	struct B : A {
		int b;
		virtual void print()
		{
			cout << "B" << endl;
		}
	};

	struct C : A {
		int c1, c2;
		virtual void print()
		{
			cout << "C" << endl;
		}
	};
	struct X {
		char a;
		double b;
		int c;
		char d;
	};
}

int main(int argc, char* argv[])
{
	using namespace CodeMood;
	cout << "Hello, C++11!" << endl;

	// Not supported by VS11
	// vector<int> vi{1, 2, 3};

	int ai[] = {1, 2, 3, 4, 5};
	vector<int> vi(begin(ai), end(ai));	// begin() and end() function

	// Lambda expression
	for_each(begin(vi), end(vi), [](int i) {
		cout << i << " ";
	});

	cout << endl;
	// Copy algorithm, elegant!
	copy(begin(vi), end(vi), ostream_iterator<int>(cout, " "));

	cout << add(121.4, 2) << endl;

	// Move constructor is called
	Node node = getNode();

	{
		shared_ptr<Node> spn = shared_ptr<Node>(new Node);
		// Equals with above one
		auto spn2 = make_shared<Node>();
	}

	// Compiler dependent implementation
	// From Microsoft 2013 intern.
	{  
		int x = 10 ;  
		int y = 10 ;  
		x = x++ ;  
		y = ++y ;  
		printf("%d, %d\n",x,y);  
	}

	Node node1;
	Node node2;
	Node node3;
	// legal
	node1 = node2 = node3;
	// illegal
	//(node1 = node2) = node3;

	//typedef vector<shared_ptr<Shape>> VSPS;
	using VSPS = vector<shared_ptr<Shape>>;		// new in C++11, same as
												// typedef vector<shared_ptr<Shape>> VSPS;
												// using can also deal with templates
	VSPS vshape;
	vshape.push_back(make_shared<Shape>());
	vshape.push_back(make_shared<Square>());
	vshape.push_back(make_shared<Circle>());
	// the addresses of member functions are unknown until they are binded to a object
	//cout << "address:" << &mem_fn(&Shape::draw) << ", " << &mem_fn(&Shape::bb) << ", " << &getNode << endl;
	// new mem_fn function in C++11, it can deal with smart pointers
	for_each(vshape.begin(), vshape.end(), mem_fn(&Shape::draw));	// Three diffefent ways to achieve this
	for_each(vshape.begin(), vshape.end(), bind(&Shape::draw, std::placeholders::_1));
	for_each(vshape.begin(), vshape.end(), [](shared_ptr<Shape>& sps){
		sps->draw();
	});

	auto bind_func = bind(&Shape::aa, vshape[0], 12345);
	bind_func();

	Shape s;
	std::function<void()> func;
	func = bind(&Shape::draw, s);

	// Test ScopeGuard, created by Andrei Alexandrescu and adopted by pongba
	ScopeGuard onExit([](){cout << "Good!" << endl;});

	// draw line test
	//DrawLineOnCPUMonitor();

	//
	ClassA cpvd;

	//
	vector<A> veca;
	veca.push_back(A());
	veca.push_back(B());
	veca.push_back(C());

	for_each(begin(veca), end(veca), mem_fn(&A::print));

	int x = 0;
	//x = x++;
	x = ++x+x++;
	cout << "x:" << x << endl;

	cout << sizeof(X) << endl;
	int p = 41;
	// test offset of a struct
	// c: offsetof
	//cout << (&(((X*)p)->a)) << endl;
	printf("%u\n", &(((X*)p)->a));
	cout << (size_t)&(((X*)0)->b) << endl;
	cout << (size_t)&(((X*)0)->c) << endl;
	cout << (size_t)&(((X*)0)->d) << endl;

	// manual
	X xx;
	cout << (size_t)&(xx.a) - (size_t)&(xx) << " "
		 << (size_t)&(xx.b) - (size_t)&(xx) << " "
		 << (size_t)&(xx.c) - (size_t)&(xx) << " "
		 << (size_t)&(xx.d) - (size_t)&(xx) << endl;

	// STL partial_sort
	int ia[12] = {69, 23, 80, 42, 17, 15, 26, 51, 19, 12, 35, 8};
	vector<int> vec(ia, ia + 12);
	ostream_iterator<int> oite(cout, " ");
	partial_sort(begin(vec), begin(vec)+7, end(vec));
	copy(begin(vec), end(vec), oite);

	cout << "\nEnjoy coding with C++~" << endl;

}


