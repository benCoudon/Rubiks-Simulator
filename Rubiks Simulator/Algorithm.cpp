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

	int currentIndex = 0;
	while (currentIndex < s.size())
	{
		int nextIndex = s.substr(currentIndex).find(" ");	// Finds the first space after the current move
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

Move Algorithm::getMove(int index) const
{
	if (index < 0 || index >= alg.size())
		return Move();
	else
		return alg[index];
}

std::string Algorithm::toStr() const
{
	std::string tmp = "";
	for (int i = 0; i < alg.size(); i++)
	{
		tmp += alg[i].toStr();
		tmp += ' ';
	}

	tmp = tmp.substr(0, tmp.size() - 1);	// Remove the extra space at the end

	return tmp;
}
