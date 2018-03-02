#include "AlphaBeta.h"
#include "SimpleAlphaBeta.h"

#pragma region SimpleAlphaBeta
	// AlphaBeta Pruning function
int SimpleAlphaBeta::search(Node* node, int depth, int alpha, int beta, bool isMax) {
	int bestValue = 0;
	int childValue = 0;
	int bestChildValue = isMax ? min : max;
	std::vector<Node*> temp;

	if ((depth == 0) || (node->children.size() == 0)) {
		bestValue = node->value;
	}
	else if (isMax) {
		bestValue = alpha;

		// Recurse for all children of node.
		for (Node* n : node->children) {
			childValue = search(n, depth - 1, bestValue, beta, false);
			bestValue = childValue > bestValue ? childValue : bestValue;
			if (beta <= bestValue) {
				std::cout << "\tcutoff: " << n->name << std::endl;
				break;
			}
		}
	}
	else {
		bestValue = beta;

		// Recurse for all children of node.
		for (Node* n : node->children) {
			childValue = search(n, depth - 1, alpha, bestValue, true);
			bestValue = childValue < bestValue ? childValue : bestValue;
			if (bestValue <= alpha) {
				std::cout << "\tcutoff: " << n->name << std::endl;
				break;
			}
		}
	}

	// Save the best child value found
	if (node->children.size() > 0)
	{
		// Use lambda for comparison
		if (isMax) {
			bestChildValue = [node]() -> int {
				int min = node->children[0]->value;
				for (Node* n : node->children)
					min = n->value > min ? n->value : min;
				return min;
			}();			// auto run as closure
		}
		else {
			bestChildValue = [node]() -> int {
				int max = node->children[0]->value;
				for (Node* n : node->children)
					max = n->value < max ? n->value : max;
				return max;
			}();		// auto run as closure
		}
		node->value = bestChildValue;
	}
	nodeCount++;
	return bestValue;
}

int SimpleAlphaBeta::staticEvaluator() {
	return 0;
}
#pragma endregion

#pragma region Node
// ctor
Node::Node(std::string n, int v, bool dbg) : name(n), value(v), debug(dbg) {
	if (debug)
		std::cout << " - Creatinging node: " << name;
}
//dtor
Node::~Node() {
	if (debug)
		std::cout << "\tDestroying node: " << name << std::endl;
	for (Node* c : children) {
		delete c;
	}
}
Node& Node::AddChild(std::string n, int v) {
	child = new Node(n, v);
	children.push_back(child);
	return *this;
}
#pragma endregion
