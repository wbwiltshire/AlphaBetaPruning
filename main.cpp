/**************************************************************/
// Simple Alpha Beta Pruning in C++
// Link: https://en.wikipedia.org/wiki/Alpha%E2%80%93beta_pruning
//       https://www.youtube.com/watch?v=Ewh-rF7KSEg 
//       http://eric-yuan.me/alpha-beta-pruning/
//       https://www.cs.cornell.edu/courses/cs312/2002sp/lectures/rec21.htm
/**************************************************************/
#include <algorithm>
#include <iostream>
#include <string>
#include <limits>
#include <vector>

// Local includes
#include "AlphaBeta.h"
#include "SimpleAlphaBeta.h"
#include "elapseTimer.h"

// Forward Class / Function definitions
int initTreeTest1(Node*, int, int);
int initTreeTest2(Node*, int, int);
int initTreeTest3(Node*, int, int);
int initTreeTest4(Node*, int, int);

// Main program
int main(int argc,char* argv[]) {
	Node* root = nullptr;
	SimpleAlphaBeta alphaBeta;
	int min = std::numeric_limits<int>::min();			// minimum value
	int max = std::numeric_limits<int>::max();
	int depth = 6;
	int totalNodes = 0;
	int abValue = 0;
	std::string abName;
	ElapsedTimer timer;


	std::cout << "Alpha Beta Pruning example!" << std::endl;
	std::cout << std::endl << "Intialize tree: ";
	root = new Node("(0)", max, true);

	int test = 4;
	timer.Start();
	switch (test) {
		case 1:
			//First test
			totalNodes = initTreeTest1(root, min, max);
			root->name = "(0)";
			std::cout << std::endl;
			std::cout << std::endl << "Start Test 1 with " << totalNodes << " total nodes: " << std::endl;
			alphaBeta.clearSearchCount();
			abValue = alphaBeta.search(root, depth, min, max, true);		// standard MinMax
			break;
		case 2:
			// Second test
			totalNodes = initTreeTest2(root, min, max);
			std::cout << std::endl;
			std::cout << std::endl << "Start Test 2 with " << totalNodes << " total nodes: " << std::endl;
			alphaBeta.clearSearchCount();
			abValue = alphaBeta.search(root, depth, min, max, true);		// standard MinMax
			break;
		case 3:
			// Misere test
			totalNodes = initTreeTest3(root, min, max);
			root->name = "I-II-II";
			std::cout << std::endl;
			std::cout << std::endl << "Start Misere Test with " << totalNodes << " total nodes: " << std::endl;
			alphaBeta.clearSearchCount();
			abValue = alphaBeta.search(root, depth, max, min, true);			// Misere MinMax
			break;
		case 4:
			// Normal test
			totalNodes = initTreeTest4(root, min, max);
			root->name = "I-II-II";
			std::cout << std::endl;
			std::cout << std::endl << "Start Normal Test  with " << totalNodes << " total nodes: " << std::endl;
			alphaBeta.clearSearchCount();
			abValue = alphaBeta.search(root, depth, min, max, true);		// standard MinMax
			break;
	}
	timer.Stop();


	// Print result
	std::cout << "\tResult: " << abValue << std::endl;
	abName = [root, abValue]() -> std::string {
		for (Node* n : root->children) {
			if (n->value == abValue)
				return n->name;
		}
		return "Not found";
	}();			// auto run as closure

	std::cout << "\tResult node: " << abName << std::endl;
	std::cout << std::endl << "Searched " << alphaBeta.searchCount() << " nodes." << std::endl;
	std::cout << "Duration: " << timer.DurationMillis() << "ms (milliseconds)" << std::endl;

	// Cleanup
	std::cout << std::endl << "Cleanup:" << std::endl;
	delete root;

	return 0;
}

#pragma region Initialization
// Result is 6 with 
// cutoff at (4, 3), (4, 10), and (2, 4)
// Tree from Wikipedia
int initTreeTest1(Node* n, int min, int max) {
	Node* node = nullptr;
	int totalNodes = 0;

	//Create first level as min
	(*n).AddChild("(1,0)", min).AddChild("(1,1)",min).AddChild("(1,2)", min);
	totalNodes += 3;

	//Create second level as max
	node = n->children[0];
	(*node).AddChild("(2,0)", max).AddChild("(2,1)", max);
	node = n->children[1];
	(*node).AddChild("(2,2)",max).AddChild("(2,3)", max);
	node = n->children[2];
	(*node).AddChild("(2,4)", max).AddChild("(2.5)", max);
	totalNodes += 6;

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
	totalNodes += 9;

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
	totalNodes += 14;

	return totalNodes;
}

// Result is 4 with 
// cutoff at (2,3) and (2,5)
int initTreeTest2(Node* n, int min, int max) {
	Node* node = nullptr;
	int totalNodes = 0;

	//Create first level as min
	(*n).AddChild("(1,0)", min).AddChild("(1,1)", min).AddChild("(1,2)", min);
	totalNodes += 3;

	//Create second level as max
	node = n->children[0];
	(*node).AddChild("(2,0)", 4).AddChild("(2,1)", 5);
	node = n->children[1];
	(*node).AddChild("(2,2)", 6).AddChild("(2,3)", max).AddChild("(2,4)", max);
	node = n->children[2];
	(*node).AddChild("(2,5)", 3).AddChild("(2,6)", 8);
	totalNodes += 6;

	//Create third level as min
	node = n->children[1]->children[1];
	(*node).AddChild("(3,0)", 3).AddChild("(3.1)", 4);
	node = n->children[1]->children[2];
	(*node).AddChild("(3,2)", 7).AddChild("(3,3)", 9);
	totalNodes += 4;

	return totalNodes;
}

// Result is 0-II-II (100)
// Tree for Misere test
int initTreeTest3(Node* n, int min, int max) {
	Node* node = nullptr;
	int totalNodes = 0;

	//Create first level as min
	(*n).AddChild("0-II-II", min).AddChild("I-I-II", min).AddChild("I-0-II", min).AddChild("I-II-I", min).AddChild("I-II-0", min);
	totalNodes += 5;

	//Create second level as max
	node = n->children[0];
	(*node).AddChild("0-I-II", max).AddChild("0-0-II", max).AddChild("0-II-I", max).AddChild("0-II-0", max);
	node = n->children[1];
	(*node).AddChild("0-I-II", max).AddChild("I-0-II", max).AddChild("I-I-I", max).AddChild("I-I-0", max);
	node = n->children[2];
	(*node).AddChild("0-0-II", max).AddChild("I-0-I", max).AddChild("I-0-0", max);
	node = n->children[3];
	(*node).AddChild("0-II-I", max).AddChild("I-I-I", max).AddChild("I-0-I", max).AddChild("I-II-0", max);
	node = n->children[4];
	(*node).AddChild("0-II-0", max).AddChild("I-I-0", max).AddChild("I-0-0", max);
	totalNodes += 18;

	//Create third level as min
	node = n->children[0]->children[0];
	(*node).AddChild("0-0-II", min).AddChild("0-I-I", min).AddChild("0-I-0", min);
	node = n->children[0]->children[1];
	(*node).AddChild("0-0-I", min).AddChild("0-0-0", 100);
	node = n->children[0]->children[2];
	(*node).AddChild("0-I-I", min).AddChild("0-0-I", min).AddChild("0-II-0", min);
	node = n->children[0]->children[3];
	(*node).AddChild("0-I-0", min).AddChild("0-0-0", 100);
	node = n->children[1]->children[0];
	(*node).AddChild("0-0-II", min).AddChild("0-I-I", min).AddChild("0-I-0", min);
	node = n->children[1]->children[1];
	(*node).AddChild("0-0-II", min).AddChild("I-0-I", min).AddChild("I-0-0", min);
	node = n->children[1]->children[2];
	(*node).AddChild("0-I-I", min).AddChild("I-0-I", min).AddChild("0-0-I", min);
	node = n->children[1]->children[3];
	(*node).AddChild("0-I-0", min).AddChild("I-0-0", min);
	node = n->children[2]->children[0];
	(*node).AddChild("0-0-I", min).AddChild("0-0-0", 100);
	node = n->children[2]->children[1];
	(*node).AddChild("0-0-I", min).AddChild("I-0-0", min);
	node = n->children[2]->children[2];
	(*node).AddChild("0-0-0", 100);
	node = n->children[3]->children[0];
	(*node).AddChild("0-I-I", min).AddChild("0-0-I", min).AddChild("0-II-0", min);
	node = n->children[3]->children[1];
	(*node).AddChild("0-I-I", min).AddChild("I-0-I", min).AddChild("I-0-0", min);
	node = n->children[3]->children[2];
	(*node).AddChild("0-0-I", min).AddChild("I-0-0", min);
	node = n->children[3]->children[3];
	(*node).AddChild("0-II-0", min).AddChild("I-I-0", min).AddChild("I-0-0", min);
	node = n->children[4]->children[0];
	(*node).AddChild("0-I-0", min).AddChild("0-0-0", 100);
	node = n->children[4]->children[1];
	(*node).AddChild("0-I-0", min).AddChild("I-0-0", min);
	node = n->children[4]->children[2];
	(*node).AddChild("0-0-0", 100);
	totalNodes += 3;

	//Create fourth level as max
	node = n->children[0]->children[0]->children[0];
	(*node).AddChild("0-0-I", max).AddChild("0-0-0", -100);
	totalNodes += 2;

	//Create fifth level with real values
	node = n->children[0]->children[0]->children[0]->children[0];
	(*node).AddChild("0-0-0", 100);
	totalNodes += 1;

	return totalNodes;
}
// Result is 0-II-II (100); 
// Path is 0-II-II (+) -> 0-I-II (-) -> 0-I-I (+) -> 0-0-I (-) -> 0-0-0 (+) wins 
// Tree for Normal test
int initTreeTest4(Node* n, int min, int max) {
	Node* node = nullptr;
	int totalNodes = 0;

	//Create first level as min
	(*n).AddChild("0-II-II", min).AddChild("I-I-II", min).AddChild("I-0-II", min).AddChild("I-II-I", min).AddChild("I-II-0", min);
	totalNodes += 5;

	//Create second level as max
	node = n->children[0];
	(*node).AddChild("0-I-II", max).AddChild("0-0-II", max).AddChild("0-II-I", max).AddChild("0-II-0", max);
	node = n->children[1];
	(*node).AddChild("0-I-II", max).AddChild("I-0-II", max).AddChild("I-I-I", max).AddChild("I-I-0", max);
	node = n->children[2];
	(*node).AddChild("0-0-II", max).AddChild("I-0-I", max).AddChild("I-0-0", max);
	node = n->children[3];
	(*node).AddChild("I-II-0", max).AddChild("0-II-I", max).AddChild("I-I-I", max).AddChild("I-0-I", max);
	node = n->children[4];
	(*node).AddChild("0-II-0", max).AddChild("I-I-0", max).AddChild("I-0-0", max);
	totalNodes += 18;

	//Create third level as min
	node = n->children[0]->children[0];
	(*node).AddChild("0-0-II", min).AddChild("0-I-I", min).AddChild("0-I-0", min);
	node = n->children[0]->children[1];
	(*node).AddChild("0-0-I", min).AddChild("0-0-0", 100);
	node = n->children[0]->children[2];
	(*node).AddChild("0-I-I", min).AddChild("0-0-I", min).AddChild("0-II-0", min);
	node = n->children[0]->children[3];
	(*node).AddChild("0-I-0", min).AddChild("0-0-0", 100);
	node = n->children[1]->children[0];
	(*node).AddChild("0-0-II", min).AddChild("0-I-I", min).AddChild("0-I-0", min);
	node = n->children[1]->children[1];
	(*node).AddChild("0-0-II", min).AddChild("I-0-I", min).AddChild("I-0-0", min);
	node = n->children[1]->children[2];
	(*node).AddChild("0-I-I", min).AddChild("I-0-I", min).AddChild("I-I-0", min);
	node = n->children[1]->children[3];
	(*node).AddChild("0-I-0", min).AddChild("0-0-I", min);
	node = n->children[2]->children[0];
	(*node).AddChild("0-0-I", min).AddChild("0-0-0", 100);
	node = n->children[2]->children[1];
	(*node).AddChild("0-0-I", min).AddChild("I-0-0", min);
	node = n->children[2]->children[2];
	(*node).AddChild("0-0-0", 100);
	node = n->children[3]->children[0];
	(*node).AddChild("0-II-0", min).AddChild("I-I-0", min).AddChild("I-0-0", min);
	node = n->children[3]->children[1];
	(*node).AddChild("0-II-0", min).AddChild("0-I-I", min).AddChild("0-0-I", min);
	node = n->children[3]->children[2];
	(*node).AddChild("0-I-I", min).AddChild("I-0-I", min).AddChild("I-I-0", min);
	node = n->children[3]->children[3];
	(*node).AddChild("0-0-I", min).AddChild("I-0-0", min);
	node = n->children[4]->children[0];
	(*node).AddChild("0-I-0", min).AddChild("0-0-0", 100);
	node = n->children[4]->children[1];
	(*node).AddChild("0-I-0", min).AddChild("I-0-0", min);
	node = n->children[4]->children[2];
	(*node).AddChild("0-0-0", 100);
	totalNodes += 42;

	//Create fourth level as max
	node = n->children[0]->children[0]->children[0];
	(*node).AddChild("0-0-I", max).AddChild("0-0-0", -100);
	node = n->children[0]->children[0]->children[1];
	(*node).AddChild("0-0-I", max).AddChild("0-I-0", max);
	node = n->children[0]->children[0]->children[2];
	(*node).AddChild("0-0-0", -100);
	node = n->children[0]->children[1]->children[0];
	(*node).AddChild("0-0-0", -100);
	node = n->children[0]->children[2]->children[0];
	(*node).AddChild("0-0-I", max).AddChild("0-0-0", -100);
	node = n->children[0]->children[2]->children[1];
	(*node).AddChild("0-0-0", -100);
	node = n->children[0]->children[2]->children[2];
	(*node).AddChild("0-I-0", max).AddChild("0-0-0", -100);
	node = n->children[0]->children[3]->children[0];
	(*node).AddChild("0-0-0", -100);
	node = n->children[1]->children[0]->children[0];
	(*node).AddChild("0-0-I", max).AddChild("0-0-0", -100);
	node = n->children[1]->children[0]->children[1];
	(*node).AddChild("0-0-I", max).AddChild("0-I-0", max);
	node = n->children[1]->children[0]->children[2];
	(*node).AddChild("0-0-0", -100);
	node = n->children[1]->children[1]->children[0];
	(*node).AddChild("0-0-0", -100).AddChild("0-0-I", max);
	node = n->children[1]->children[1]->children[1];
	(*node).AddChild("0-0-I", max).AddChild("I-0-0", max);
	node = n->children[1]->children[1]->children[2];
	(*node).AddChild("0-0-0", -100);
	node = n->children[1]->children[2]->children[0];
	(*node).AddChild("0-0-I", max).AddChild("0-I-0", max);
	node = n->children[1]->children[2]->children[1];
	(*node).AddChild("I-0-0", max).AddChild("0-0-I", max);
	node = n->children[1]->children[2]->children[2];
	(*node).AddChild("0-I-0", max).AddChild("0-0-0", -100);
	node = n->children[1]->children[3]->children[0];
	(*node).AddChild("0-0-0", -100);
	node = n->children[1]->children[3]->children[1];
	(*node).AddChild("0-0-0", -100);
	node = n->children[2]->children[0]->children[0];
	(*node).AddChild("0-0-0", -100);
	node = n->children[2]->children[1]->children[0];
	(*node).AddChild("0-0-0", -100);
	node = n->children[2]->children[1]->children[1];
	(*node).AddChild("0-0-0", -100);
	node = n->children[3]->children[0]->children[0];
	(*node).AddChild("0-0-I", max).AddChild("0-0-0", -100);
	node = n->children[3]->children[0]->children[1];
	(*node).AddChild("0-I-0", max).AddChild("I-0-0", max);
	node = n->children[3]->children[0]->children[2];
	(*node).AddChild("0-0-0", -100);
	node = n->children[3]->children[1]->children[0];
	(*node).AddChild("0-0-0", -100).AddChild("0-I-0", max);
	node = n->children[3]->children[1]->children[1];
	(*node).AddChild("0-0-I", max).AddChild("0-I-0", max);
	node = n->children[3]->children[1]->children[2];
	(*node).AddChild("0-0-0", -100);
	node = n->children[3]->children[2]->children[0];
	(*node).AddChild("0-0-I", max).AddChild("0-I-0", max);
	node = n->children[3]->children[2]->children[1];
	(*node).AddChild("I-0-0", max).AddChild("0-0-I", max);
	node = n->children[3]->children[2]->children[2];
	(*node).AddChild("0-I-0", max).AddChild("0-0-0", -100);
	node = n->children[3]->children[3]->children[0];
	(*node).AddChild("0-0-0", -100);
	node = n->children[3]->children[3]->children[1];
	(*node).AddChild("0-0-0", -100);
	node = n->children[4]->children[0]->children[0];
	(*node).AddChild("0-0-0", -100);
	node = n->children[4]->children[1]->children[0];
	(*node).AddChild("0-0-0", -100);
	node = n->children[4]->children[1]->children[1];
	(*node).AddChild("0-0-0", -100);

	totalNodes += 57;

	//Create fifth level with leaf values
	node = n->children[0]->children[0]->children[0]->children[0];
	(*node).AddChild("0-0-0", 100);
	node = n->children[0]->children[0]->children[1]->children[0];
	(*node).AddChild("0-0-0", 100);
	node = n->children[0]->children[0]->children[1]->children[1];
	(*node).AddChild("0-0-0", 100);
	node = n->children[0]->children[2]->children[0]->children[0];
	(*node).AddChild("0-0-0", 100);
	node = n->children[0]->children[2]->children[0]->children[1];
	(*node).AddChild("0-0-0", 100);
	node = n->children[0]->children[2]->children[2]->children[0];
	(*node).AddChild("0-0-0", 100);
	node = n->children[1]->children[0]->children[0]->children[0];
	(*node).AddChild("0-0-0", 100);
	node = n->children[1]->children[0]->children[1]->children[0];
	(*node).AddChild("0-0-0", 100);
	node = n->children[1]->children[0]->children[1]->children[1];
	(*node).AddChild("0-0-0", 100);
	node = n->children[1]->children[1]->children[0]->children[1];
	(*node).AddChild("0-0-0", 100);
	node = n->children[1]->children[1]->children[1]->children[0];
	(*node).AddChild("0-0-0", 100);
	node = n->children[1]->children[1]->children[1]->children[1];
	(*node).AddChild("0-0-0", 100);
	node = n->children[1]->children[2]->children[0]->children[0];
	(*node).AddChild("0-0-0", 100);
	node = n->children[1]->children[2]->children[0]->children[1];
	(*node).AddChild("0-0-0", 100);
	node = n->children[1]->children[2]->children[1]->children[0];
	(*node).AddChild("0-0-0", 100);
	node = n->children[1]->children[2]->children[1]->children[1];
	(*node).AddChild("0-0-0", 100);
	node = n->children[1]->children[2]->children[2]->children[0];
	(*node).AddChild("0-0-0", 100);
	node = n->children[3]->children[0]->children[0]->children[0];
	(*node).AddChild("0-0-0", 100);
	node = n->children[3]->children[0]->children[1]->children[0];
	(*node).AddChild("0-0-0", 100);
	node = n->children[3]->children[0]->children[1]->children[1];
	(*node).AddChild("0-0-0", 100);
	node = n->children[3]->children[1]->children[0]->children[1];
	(*node).AddChild("0-0-0", 100);
	node = n->children[3]->children[1]->children[1]->children[0];
	(*node).AddChild("0-0-0", 100);
	node = n->children[3]->children[1]->children[1]->children[1];
	(*node).AddChild("0-0-0", 100);
	node = n->children[3]->children[2]->children[0]->children[0];
	(*node).AddChild("0-0-0", 100);
	node = n->children[3]->children[2]->children[0]->children[1];
	(*node).AddChild("0-0-0", 100);
	node = n->children[3]->children[2]->children[1]->children[0];
	(*node).AddChild("0-0-0", 100);
	node = n->children[3]->children[2]->children[1]->children[1];
	(*node).AddChild("0-0-0", 100);
	node = n->children[3]->children[2]->children[2]->children[0];
	(*node).AddChild("0-0-0", 100);
	totalNodes += 28;

	return totalNodes;
}
#pragma endregion