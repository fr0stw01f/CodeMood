/*************************************************************************
	>    File Name: PrintBinaryTreeByLevel.cpp
	>       Author: tangzh
	>         Mail: tangzhnju@gmail.com 
	> Created Time: Wed 05 Jun 2013 07:03:10 PM CST
 ************************************************************************/

#include "BinaryTree.h"

#define M 9

using namespace CodeMood;

int main(int argc, char* argv[])
{
	Node<int> nodes[M];
	for (int i = 0; i < M; ++i) {
		nodes[i].data_ = i;
	}

	// build binary tree
	link(nodes, 1, 2, 3);
	link(nodes, 2, 4, 5);
	link(nodes, 3, -1, 6);
	link(nodes, 5, 7, 8);

	PrintTreeNodeByLevelVector(&nodes[1]);
	cout << endl;

	PrintTreeNodeByLevelDeque(&nodes[1]);
	cout << endl;

	return 0;
}

