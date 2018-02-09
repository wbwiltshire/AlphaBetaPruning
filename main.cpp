/**************************************************************/
// Simple Alpha Beta Pruning in C++
// Link: https://en.wikipedia.org/wiki/Alpha%E2%80%93beta_pruning
//       https://www.youtube.com/watch?v=Ewh-rF7KSEg 
//       http://eric-yuan.me/alpha-beta-pruning/
/**************************************************************/
#include <algorithm>
#include <iostream>
#include <string>
#include <limits>
#include <vector>

// Classes
class Node {
public:
	std::vector<Node*> children;
	std::string name;
	int value;

	//ctor
	Node(std::string n, int v) : name(n), value(v) {
		std::cout << " - Creatinging node: " << name;
	}
	//dtor
	~Node() {
		std::cout << "\tDestroying node: " << name << std::endl;
		for (Node* c : children) {
			delete c;
		}
	}
	Node& AddChild(std::string n, int v) {
		child = new Node(n, v);
		children.push_back(child);
		return *this;
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
	root = new Node("(0)", max);

	int test = 2;
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
				std::cout << "\tcutoff: " << n->name << std::endl;
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
				std::cout << "\tcutoff" << n->name << std::endl;
				break;
			}
		}
	}
	return bestValue;
}

// Result is 6 with 
// cutoff at (4, 3), (4, 10), and (2, 4)
void initTreeTest1(Node* n, int min, int max) {
	Node* node = nullptr;

	//Create first level as min
	(*n).AddChild("(1,0)", min).AddChild("(1,1)",min).AddChild("(1,2)", min);

	//Create second level as max
	node = n->children[0];
	(*node).AddChild("(2,0)", max).AddChild("(2,1)", max);
	node = n->children[1];
	(*node).AddChild("(2,2)",max).AddChild("(2,3)", max);
	node = n->children[2];
	(*node).AddChild("(2,4)", max).AddChild("(2.5)", max);

	//Create third level as min
	node = n->children[0]->children[0];
	(*node).AddChild("(3,0)", min).AddChild("(3,1)", min);
	node = n->children[0]->children[1];
	(*node).AddChild("(3,2)", min);
	node = n->children[1]->children[0];
	(*node).AddChild("(3,3)", min).AddChild("(3,4)", min);
	node = n->children[1]->children[1];
	(*node).AddChild("(3,5)", min);
	node = n->children[2]->children[0];
	(*node).AddChild("(3,6)", min);
	node = n->children[2]->children[1];
	(*node).AddChild("(3,7)", min).AddChild("(3,8)", min);

	//Create fourth level with real values
	node = n->children[0]->children[0]->children[0];
	(*node).AddChild("(4,0)", 5).AddChild("(4,1)", 6);
	node = n->children[0]->children[0]->children[1];
	(*node).AddChild("(4,2)", 7).AddChild("(4,3)", 4).AddChild("(4,4)", 5);
	node = n->children[0]->children[1]->children[0];
	(*node).AddChild("(4,5)", 3);
	node = n->children[1]->children[0]->children[0];
	(*node).AddChild("(4,6)", 6);
	node = n->children[1]->children[0]->children[1];
	(*node).AddChild("(4,7)", 6); node->AddChild("(4,8)", 9);
	node = n->children[1]->children[1]->children[0];
	(*node).AddChild("(4,9)", 7);
	node = n->children[2]->children[0]->children[0];
	(*node).AddChild("(4,10)", 5);
	node = n->children[2]->children[1]->children[0];
	(*node).AddChild("(4,11)", 9); node->AddChild("(4,12)", 8);
	node = n->children[2]->children[1]->children[1];
	(*node).AddChild("(4,13)", 6);

}
// Result is 4 with 
// cutoff at (2,3) and (2,5)
void initTreeTest2(Node* n, int min, int max) {
	Node* node = nullptr;

	//Create first level as min
	(*n).AddChild("(1,0)", min).AddChild("(1,1)", min).AddChild("(1,2)", min);

	//Create second level as max
	node = n->children[0];
	(*node).AddChild("(2,0)", 4).AddChild("(2,1)", 5);
	node = n->children[1];
	(*node).AddChild("(2,2)", 6).AddChild("(2,3)", max).AddChild("(2,4)", max);
	node = n->children[2];
	(*node).AddChild("(2,5)", 3).AddChild("(2,6)", 8);

	//Create third level as min
	node = n->children[1]->children[1];
	(*node).AddChild("(3,0)", 3).AddChild("(3.1)", 4);
	node = n->children[1]->children[2];
	(*node).AddChild("(3,2)", 7).AddChild("(3,3)", 9);

}
