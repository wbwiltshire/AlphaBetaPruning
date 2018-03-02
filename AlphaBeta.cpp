#include "AlphaBeta.h"

#pragma region Node
// ctor
Node::Node(std::string n, int v, bool dbg = false) : name(n), value(v), debug(dbg) {
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
