#pragma once

#include <iostream>
#include <limits>
#include <string>
#include <vector>

class Node {
public:
	std::vector<Node*> children;
	std::string name;
	int value;

	Node(std::string, int, bool dbg = false);	// ctor
	~Node();						// dtor
	Node& AddChild(std::string, int);
private:
	bool debug;
	Node * child;
};

class AlphaBeta {
public:
	virtual int search(Node*, int, int , int, bool) = 0;
	int searchCount() { return nodeCount; };
	void clearSearchCount() { nodeCount = 0; };
	const int min = std::numeric_limits<int>::min();			// minimum value
	const int max = std::numeric_limits<int>::max();
protected:
	int nodeCount = 0;
private:
	virtual int staticEvaluator() = 0;
};

