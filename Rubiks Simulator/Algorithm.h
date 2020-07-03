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
	Move getMove(unsigned index) const;

	std::string toStr() const;

	friend Algorithm generateScramble();

private:
	std::vector<Move> alg;
};

Algorithm generateScramble();
