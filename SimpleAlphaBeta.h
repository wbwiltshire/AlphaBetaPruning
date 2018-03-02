#pragma once
#include "AlphaBeta.h"

class SimpleAlphaBeta : public AlphaBeta {
public:
	int search(Node*, int, int, int, bool) override;
	int staticEvaluator() override;
};
