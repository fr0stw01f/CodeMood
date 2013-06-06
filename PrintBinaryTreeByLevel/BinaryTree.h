/*************************************************************************
	>    File Name: BinaryTree.h
	>       Author: tangzh
	>         Mail: tangzhnju@gmail.com 
	> Created Time: Wed 05 Jun 2013 07:03:22 PM CST
 ************************************************************************/

#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

namespace CodeMood {
	template<class T>
	struct Node {
		Node() : data_(0), left_(nullptr), right_(nullptr)
		{}
		T data_;
		Node* left_;
		Node* right_;
	};

	template<class T>
	void link(Node<T>* nodes, int node, int left, int right)
	{
		if (left > 0)
			nodes[node].left_ = &nodes[left];
		if (right > 0)
			nodes[node].right_ = &nodes[right];
	}

	template<class T>
	void PrintTreeNodeByLevelVector(Node<T>* node)
	{
		vector<Node<T>*> vn;
		size_t i = 0, j = 1;
		vn.push_back(node);
		while (i < vn.size()) {
			j = vn.size();
			while (i < j) {
				cout << vn[i]->data_ << " ";
				if (vn[i]->left_ != nullptr)
					vn.push_back(vn[i]->left_);
				if (vn[i]->right_ != nullptr)
					vn.push_back(vn[i]->right_);
				++i;
			}
			cout << endl;
		}
	}

	template<class T>
	void PrintTreeNodeByLevelDeque(Node<T>* node)
	{
		queue<Node<T>*> dn;
		Node<T> *n;
		dn.push(node);
		dn.push(nullptr);
		while (!dn.empty()) {
			n = dn.front();
			dn.pop();
			if (n) {
				cout << n->data_ << " ";
				if (n->left_ != nullptr)
					dn.push(n->left_);
				if (n->right_ != nullptr)
					dn.push(n->right_);
			} else {
				cout << endl;
				if (!dn.empty())	// still need to continue
					dn.push(nullptr);
			}
		}
	}
} //!namespace CodeMood

#endif //!BINARY_TREE_H
