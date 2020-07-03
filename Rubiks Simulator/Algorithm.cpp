#include "Algorithm.h"

Algorithm::Algorithm()
{
}

Algorithm::Algorithm(Move m)
{
	alg.push_back(m);
}

Algorithm::Algorithm(std::string s)
{
	setAlgorithm(s);
}

void Algorithm::setAlgorithm(const std::string &s)
{
	if (s.size() == 0)
		alg.push_back(Move());

	unsigned currentIndex = 0;
	while (currentIndex < s.size())
	{
		unsigned nextIndex = s.substr(currentIndex).find(" ");	// Finds the first space after the current move
		if (nextIndex == std::string::npos)					// If nextIndex is string::npos then there are no more space characters in s
		{
			alg.push_back(Move(s.substr(currentIndex)));	// There is still a final move, even though it is not followed by a space
			return;
		}

		alg.push_back(Move(s.substr(currentIndex, nextIndex)));	// Create a new move from the substring

		nextIndex += currentIndex;	// nextIndex is just an offset from currentIndex so currentIndex is added back once the move is created

		while (s[nextIndex] == ' ' && nextIndex < s.size())	// Skip to the next non-space character
			nextIndex++;

		currentIndex = nextIndex;
	}
}

Move Algorithm::getMove(unsigned index) const
{
	if (index < 0 || index >= alg.size())
		return Move();
	else
		return alg[index];
}

std::string Algorithm::toStr() const
{
	std::string tmp = "";
	for (unsigned i = 0; i < alg.size(); i++)
	{
		tmp += alg[i].toStr();
		tmp += ' ';
	}

	tmp = tmp.substr(0, tmp.size() - 1);	// Remove the extra space at the end

	return tmp;
}

Algorithm generateScramble()
{
	Algorithm scramble;

	int f = rand() % 6;
	int t = rand() % 3;
	scramble.alg.push_back(Move((Move::MoveTarget)f, (Move::MoveType)t));
	
	while (scramble.alg.size() < 25)
	{
		f = rand() % 6;
		while (f == (int)scramble.alg.back().getTarget() || f == ((int)scramble.alg.back().getTarget() + 3) % 6)	// Make sure that the same face or an opposite face are not used in concurrent moves
		{
			f = rand() % 6;
		}

		t = rand() % 3;
		
		scramble.alg.push_back(Move((Move::MoveTarget)f, (Move::MoveType)t));
	}

	return scramble;
}
