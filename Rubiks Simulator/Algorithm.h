#pragma once

#include <vector>

#include "Move.h"

class Algorithm
{
public:
	Algorithm();
	Algorithm(std::string s);
	Algorithm(Move m);

	void setAlgorithm(const std::string &s);

	int getSize() const { return alg.size(); };
	Move getMove(int index) const;

	std::string toStr() const;

private:
	std::vector<Move> alg;
};
