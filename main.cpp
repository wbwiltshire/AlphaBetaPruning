/**************************************************************/
// Simple Alpha Beta Pruning in C++
// Link: https://en.wikipedia.org/wiki/Alpha%E2%80%93beta_pruning
//       https://www.youtube.com/watch?v=Ewh-rF7KSEg 
//       http://eric-yuan.me/alpha-beta-pruning/
/**************************************************************/
#include <algorithm>
#include <iostream>
#include <vector>
#include <limits>

// Classes
class Node {
public:
	const Node* parent;
	std::vector<Node*> children;
	int value;

	//ctor
	Node(const Node* n, int v) : parent(n), value(v) {
		std::cout << " - Creatinging node: " << value;
	}
	//dtor
	~Node() {
		std::cout << "\tDestroying node: " << value << std::endl;
		for (Node* c : children) {
			delete c;
		}

	}
	void AddChild(int v) {
		child = new Node(this, v);
		children.push_back(child);
	}
private:
	Node * child;
};

// Function definitions
void initTreeTest1(Node*, int, int);
void initTreeTest2(Node*, int, int);
int alphaBeta(Node*, int, int, int, bool);

// Main program
int main(int argc,char* argv[]) {
	Node* root = nullptr;
	int min = std::numeric_limits<int>::min();			// minimum value
	int max = std::numeric_limits<int>::max();
	int depth = 4;

	std::cout << "Alpha Beta Pruning example!" << std::endl;
	std::cout << std::endl << "Intialize tree: ";
	root = new Node(nullptr, max);
	root->value = max;

	int test = 1;
	switch (test) {
		case 1:
			//First test
			initTreeTest1(root, min, max);
			std::cout << std::endl;
			std::cout << std::endl << "Start Test 1: " << std::endl;
			break;
		case 2:
			// Second test
			initTreeTest2(root, min, max);
			std::cout << std::endl;
			std::cout << std::endl << "Start Test 2: " << std::endl;
			break;
	}

	// Print result
	std::cout << std::endl << "\tResult: " << alphaBeta(root, depth, min, max, true) << std::endl;

	// Cleanup
	std::cout << std::endl << "Cleanup:" << std::endl;
	delete root;

	return 0;
}

// AlphaBeta Pruning function
int alphaBeta(Node* node, int depth, int alpha, int beta, bool isMax) {
	int bestValue = 0;
	int childValue = 0;
	std::vector<Node*> temp;

	if ((depth == 0) || (node->children.size() == 0)) {
		bestValue = node->value;
	}
	else if (isMax) {
		bestValue = alpha;

		// Recurse for all children of node.
		for (Node* n : node->children) {
			childValue = alphaBeta(n, depth - 1, bestValue, beta, false);
			bestValue = std::max(bestValue, childValue);
			if (beta <= bestValue) {
				std::cout << "\tcutoff" << std::endl;
				break;
			}
		}
	}
	else {
		bestValue = beta;

		// Recurse for all children of node.
		for (Node* n : node->children) {
			childValue = alphaBeta(n, depth - 1, alpha, bestValue, true);
			bestValue = std::min(bestValue, childValue);
			if (bestValue <= alpha) {
				std::cout << "\tcutoff" << std::endl;
				break;
			}
		}
	}
	return bestValue;
}

// Result is 6 with 
// cutoff at (0,0,1,2), (1,0,1,1), and (2,1)
void initTreeTest1(Node* n, int min, int max) {
	Node* node = nullptr;

	//Create first level as min
	n->AddChild(min); n->AddChild(min);	n->AddChild(min);

	//Create second level as max
	node = n->children[0];
	node->AddChild(max); node->AddChild(max);
	node = n->children[1];
	node->AddChild(max); node->AddChild(max);
	node = n->children[2];
	node->AddChild(max); node->AddChild(max);

	//Create third level as min
	node = n->children[0]->children[0];
	node->AddChild(min); node->AddChild(min);
	node = n->children[0]->children[1];
	node->AddChild(min);
	node = n->children[1]->children[0];
	node->AddChild(min); node->AddChild(min);
	node = n->children[1]->children[1];
	node->AddChild(min);
	node = n->children[2]->children[0];
	node->AddChild(min);
	node = n->children[2]->children[1];
	node->AddChild(min); node->AddChild(min);

	//Create fourth level with real values
	node = n->children[0]->children[0]->children[0];
	node->AddChild(5); node->AddChild(6);
	node = n->children[0]->children[0]->children[1];
	node->AddChild(7); node->AddChild(4); node->AddChild(5);
	node = n->children[0]->children[1]->children[0];
	node->AddChild(3);
	node = n->children[1]->children[0]->children[0];
	node->AddChild(6);
	node = n->children[1]->children[0]->children[1];
	node->AddChild(6); node->AddChild(9);
	node = n->children[1]->children[1]->children[0];
	node->AddChild(7);
	node = n->children[2]->children[0]->children[0];
	node->AddChild(5);
	node = n->children[2]->children[1]->children[0];
	node->AddChild(9); node->AddChild(8);
	node = n->children[2]->children[1]->children[1];
	node->AddChild(6);

}
// Result is 4 with 
// cutoff at (1,2) and (2,1)
void initTreeTest2(Node* n, int min, int max) {
	Node* node = nullptr;

	//Create first level as min
	n->AddChild(min); n->AddChild(min);	n->AddChild(min);

	//Create second level as max
	node = n->children[0];
	node->AddChild(4); node->AddChild(5);
	node = n->children[1];
	node->AddChild(6); node->AddChild(max); node->AddChild(max);
	node = n->children[2];
	node->AddChild(3); node->AddChild(8);

	//Create third level as min
	node = n->children[1]->children[1];
	node->AddChild(3); node->AddChild(4);
	node = n->children[1]->children[2];
	node->AddChild(7); node->AddChild(9);

}
