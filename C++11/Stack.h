/*************************************************************************
	>    File Name: Stack.h
	>       Author: tangzh
	>         Mail: tangzhnju@gmail.com 
	> Created Time: Wed 05 Jun 2013 06:22:37 PM CST
 ************************************************************************/

// There are three main alternatives we can choose from when it comes to
// guaranteeing exception-safety:
// 1)   Basic guarantee: No memory leak.
// 2)  Strong guarantee: Program state remain unchanged.
// 3) Nothrow guarantee: Won't emit an exception under any circumstances.
// 
// All iterators returned from from standard containers are exception-safe
// and can be copied without throwing an exception.
//
// All standard containers must implement the basic guarantee for all
// operations: They are always destructible, and they are always in a
// consistent (if not predictable) state even in presence of exceptions.
//
// Certain important functions are required to implement the nothrow
// guarantee-including swap, allocator<T>::deallocate and certain
// operations of template parameter types themselves (especially, the
// destructor).
//
// All standard containers must also implement the strong guarantee for
// all operations(with two exceptions).
//
// For all containers, multi-element inserts are never strongly exception-
// safe.
//
// For vector<T> and deque<T> only, inserts and erases are strongly
// exception-safe as long as T's copy constructor and assignment operator
// do not throw.
//
// These particular limitations are because to roll back either kind of
// operation isn't possible without extra space/time overhead, and the
// standard did not want to require that overhead in the name of exception-
// safety.
//
// If you write a class that has a container member and you perform range
// insertions, or you write a class that has a member of type vector<T> or
// deque<T>, and T's copy constructor or assignment operator can throw,
// then you are responsible for doing the extra work to ensure that your
// own class's state is predictable if exceptions do occur. Fortunately,
// this "extra work" is pretty simple. Whenever you want to insert into or
// erase from the container, first take a copy of the container, then
// perform the change on the copy. Finally, use swap to switch over to
// using that new version after you know that the copy-and-change steps
// have succeeded.
//
// Keys to C++ resource management: RAII, Exception, Pimpl, Nothrow-Swap.
// 
// Observe the canonical exception-safe rules:
// 1) Never allow an exception to escape from a destructor or from an
//    overloaded operator delete() or operator delete[](); write every
//    destructor and deallocation function as though it had an exception
//    specification of "throw()".
// 2) Always use the "resource acquisition is initialization" idiom to
//    isolate resource ownership and management.
// 3) In each function, take all the code that might emit an exception and
//    do all that work safely off to the side. Only then, when you know
//    that the real work has succeeded, should you modify the program
//    state (and clean up) using only nonthrowing operations.

#ifndef STACK_H
#define STACK_H

#include <algorithm>

namespace CodeMood {

	template<class T1, class T2>
	void construct(T1* p, const T2& value)
	{
		new (p) T1(value);						// placement new, call ctor
	}

	template<class T>
	void destory(T* p)
	{
		p->~T();									// call dtor manually, never throw
	}

	template<class FwdIter>
	void destory(FwdIter first, FwdIter last)
	{
		while (first != last)
		{
			destory(&*first);
			++first;
		}
	}

	template <class T>
	void swap(T& a, T& b)
	{
		T temp(a);
		a = b;
		b = temp;
	}

	template<class T> class StackImpl
	{
	public:
		StackImpl(size_t size = 0);
		~StackImpl();
		void Swap(StackImpl& other) throw();	// never throw

		T*      v_;								// ptr to a memory area big
		size_t  vsize_;							// enough for 'vsize_' T's
		size_t  vused_;							// # of T's actually in use

	private:
		StackImpl(const StackImpl&);
		StackImpl& operator=( const StackImpl&);
	};

	template<class T>
	StackImpl<T>::StackImpl(size_t size)
		: v_(static_cast<T*>
		(size == 0
		? 0
		: operator new (sizeof (T) * size))),	// alloc memory
		vsize_(size),
		vused_(0)
	{
	}

	template<class T>
	StackImpl<T>::~StackImpl()					// never throw
	{
		destory(v_, v_ + vused_);				// call dtor
		operator delete(v_);					// release memory
	}

	template<class T>
	void StackImpl<T>::Swap(StackImpl& other) throw()	// simple but important
	{
		using std::swap;
		swap(v_,      other.v_);				// never throw
		swap(vsize_,  other.vsize_);			// never throw
		swap(vused_,  other.vused_);			// never throw
	}

	template<class T>
	class Stack
	{
	public:
		Stack(size_t size = 0)
			: impl_(size)
		{
		}

		~Stack()                // elegant
		{                       // do nothing but call StackImpl::~StackImpl()
		}                       // never throw

		Stack(const Stack& other)
			: impl_(other.impl_.vsize_)					// alloc memory
		{
			while (impl_.vused_ < other.impl_.vused_)
			{
				construct(impl_.v_ + impl_.vused_,		// call ctor
					other.impl_.v_[impl_.vused_]);
				++impl_.vused_;
			}
		}

		const Stack& operator=( const Stack& other)		// incredibly elegant and nifty
		{
			Stack temp(other);							// does all the work
			impl_.Swap(temp.impl_);						// never throw, exception-safe
			return *this;
		}

		size_t Count() const
		{
			return impl_.vused_;
		}

		void Push(const T& t)
		{
			if (impl_.vused_ == impl_.vsize_)			// grow if necessary
			{
				Stack temp(impl_.vsize_ * 2 + 1);
				while (temp.Count() < impl_.vused_)
				{
					temp.Push(impl_.v_[temp.Count()]);
				}
				temp.Push(t);
				impl_.Swap(temp.impl_);					// never throw, exception-safe
			}
			else
			{
				construct(impl_.v_ + impl_.vused_, t);
				++impl_.vused_;
			}
		}

		T& Top()										// if empty, throws exception
		{
			if (impl_.vused_ == 0)
			{
				throw "empty stack" ;
			}
			return impl_.v_[impl_.vused_ - 1];
		}

		void Pop()										// if empty, throws exception
		{
			if (impl_.vused_ == 0)
			{
				throw "pop from empty stack" ;
			}
			else
			{
				--impl_.vused_;
				destory(impl_.v_ + impl_.vused_);
			}
		}

	private:
		StackImpl<T> impl_;								// Pimpl, private implementation
	};
}

#endif //STACK_H


