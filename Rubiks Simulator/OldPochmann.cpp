#include "OldPochmann.h"

#include "AlgorithmList.h"

Algorithm setupMoveC(CubeFace f, int targetPos);
Algorithm setupMoveE(CubeFace f, int targetPos);

int checkCorners(const Cube &c);
int checkEdges(const Cube &c);

std::vector<Algorithm> createSolutionOldPochmann(const Cube &c)
{
	std::vector<Algorithm> solution;

	Cube currentCube = c;
	Cube solved;

	// Asume cube is already oriented correctly
	int cornersSolved = checkCorners(currentCube);
	while (cornersSolved != -1)
	{
		Cube::Corner buffer = currentCube.getCorner(CubeFace::UP, 2);

		CubeColor targetFace;
		int targetPos;

		if (cornersSolved == -2)	// We don't start a new cycle so just swap the buffer to its proper location
		{
			targetFace = buffer.p;
			for (targetPos = 0; targetPos < 4; targetPos++)
			{
				Cube::Corner compare = solved.getCorner((CubeFace)targetFace, targetPos);
				if (buffer.p == compare.p && buffer.s == compare.s && buffer.t == compare.t)
				{
					break;
				}
			}
		}
		else	// We must start a new cycle so swap with a random unsolved piece
		{
			targetFace = (CubeColor)(cornersSolved / 4);
			targetPos = cornersSolved % 4;
		}

		Algorithm setup = setupMoveC((CubeFace)targetFace, targetPos);
		Algorithm reverse = setup.inverse();

		printf("%s\n%s\n%s\n\n", setup.toStr().c_str(), yPerm.toStr().c_str(), reverse.toStr().c_str());

		solution.push_back(setup);
		solution.push_back(yPerm);
		solution.push_back(reverse);

		currentCube.setAlg(setup);
		currentCube.executeAlg();
		currentCube.setAlg(yPerm);
		currentCube.executeAlg();
		currentCube.setAlg(reverse);
		currentCube.executeAlg();

		cornersSolved = checkCorners(currentCube);
	}

	int edgesSolved = checkEdges(currentCube);
	while (edgesSolved != -1)
	{
		Cube::Edge buffer = currentCube.getEdge(CubeFace::UP, 1);

		CubeColor targetFace;
		int targetPos;

		if (edgesSolved == -2)	// We don't start a new cycle so just swap the buffer to its proper location
		{
			targetFace = buffer.p;
			for (targetPos = 0; targetPos < 4; targetPos++)
			{
				Cube::Edge compare = solved.getEdge((CubeFace)targetFace, targetPos);
				if (buffer.p == compare.p && buffer.s == compare.s)
				{
					break;
				}
			}
		}
		else	// We must start a new cycle so swap with a random unsolved piece
		{
			targetFace = (CubeColor)(edgesSolved / 4);
			targetPos = edgesSolved % 4;
		}

		Algorithm setup = setupMoveE((CubeFace)targetFace, targetPos);
		Algorithm reverse = setup.inverse();

		printf("%s\n%s\n%s\n\n", setup.toStr().c_str(), tPerm.toStr().c_str(), reverse.toStr().c_str());

		solution.push_back(setup);
		solution.push_back(tPerm);
		solution.push_back(reverse);

		currentCube.setAlg(setup);
		currentCube.executeAlg();
		currentCube.setAlg(tPerm);
		currentCube.executeAlg();
		currentCube.setAlg(reverse);
		currentCube.executeAlg();

		edgesSolved = checkEdges(currentCube);
	}

	return solution;
}

Algorithm setupMoveC(CubeFace f, int targetPos)
{
	int target = f * 4 + targetPos;
	switch (target)
	{
	case 0:
		return Algorithm("");

	case 1:
		return Algorithm("R' F R");

	case 2:
		return Algorithm("");

	case 3:
		return Algorithm("F' D R");

	case 4:
		return Algorithm("R");

	case 5:
		return Algorithm("F' R");

	case 6:
		return Algorithm("F2 R");

	case 7:
		return Algorithm("F R");

	case 8:
		return Algorithm("R F'");

	case 9:
		return Algorithm("R2 F'");

	case 10:
		return Algorithm("R' F'");

	case 11:
		return Algorithm("F'");

	case 12:
		return Algorithm("D F2");

	case 13:
		return Algorithm("F2");

	case 14:
		return Algorithm("D R2");

	case 15:
		return Algorithm("R2");

	case 16:
		return Algorithm("");

	case 17:
		return Algorithm("R'");

	case 18:
		return Algorithm("R2");

	case 19:
		return Algorithm("D2 R");

	case 20:
		return Algorithm("F");

	case 21:
		return Algorithm("D R");

	case 22:
		return Algorithm("D F' R");

	case 23:
		return Algorithm("");
	}
}

Algorithm setupMoveE(CubeFace f, int targetPos)
{
	int target = f * 4 + targetPos;
	switch (target)
	{
	case 0:
		return Algorithm("l2 D L2");

	case 1:
		return Algorithm("");

	case 2:
		return Algorithm("l2 D' L2");

	case 3:
		return Algorithm("");

	case 4:
		return Algorithm("d2 L");

	case 5:
		return Algorithm("l D L2");

	case 6:
		return Algorithm("L'");

	case 7:
		return Algorithm("l D' L2");

	case 8:
		return Algorithm("D' l D L2");

	case 9:
		return Algorithm("d L");

	case 10:
		return Algorithm("");

	case 11:
		return Algorithm("d' L'");

	case 12:
		return Algorithm("D L2");

	case 13:
		return Algorithm("L2");

	case 14:
		return Algorithm("D' L2");

	case 15:
		return Algorithm("D2 L2");

	case 16:
		return Algorithm("L");

	case 17:
		return Algorithm("l' D L2");

	case 18:
		return Algorithm("d2 L'");

	case 19:
		return Algorithm("l' D' L2");

	case 20:
		return Algorithm("L d' L");

	case 21:
		return Algorithm("d' L");

	case 22:
		return Algorithm("L' d' L");

	case 23:
		return Algorithm("d L'");
	}
}

int checkCorners(const Cube &c)
{
	Cube solved;

	if (c.getCorner(CubeFace::UP, 2) == solved.getCorner(CubeFace::UP, 2) || c.getCorner(CubeFace::UP, 2) == solved.getCorner(CubeFace::BACK, 0) || c.getCorner(CubeFace::UP, 2) == solved.getCorner(CubeFace::LEFT, 3))
	{
		for (int i = 0; i < 24; i++)
		{
			if (i == 2 || i == 16 || i == 23)	// Skip over the buffer because it will be solved if all other pieces are
				continue;

			if (c.getCorner(CubeFace(i / 4), i % 4) != solved.getCorner(CubeFace(i / 4), i % 4))
				return i;	// Return the first incorrect corner that isn't the buffer so we know to swap with this position
		}
	}
	else	// We run the same code here, but return -2 to indicate that we aren't starting a new cycle
	{
		for (int i = 0; i < 24; i++)
		{
			if (i == 2 || i == 16 || i == 23)	// Skip over the buffer because it will be solved if all other pieces are
				continue;

			if (c.getCorner(CubeFace(i / 4), i % 4) != solved.getCorner(CubeFace(i / 4), i % 4))
				return -2;
		}
	}

	return -1;
}

int checkEdges(const Cube &c)
{
	Cube solved;

	if (c.getEdge(CubeFace::UP, 1) == solved.getEdge(CubeFace::UP, 1) || c.getEdge(CubeFace::UP, 1) == solved.getEdge(CubeFace::RIGHT, 2))
	{
		for (int i = 0; i < 24; i++)
		{
			if (i == 1 || i == 10)	// Skip over the buffer because it will be solved if all other pieces are
				continue;

			if (c.getEdge(CubeFace(i / 4), i % 4) != solved.getEdge(CubeFace(i / 4), i % 4))
				return i;	// Return the first incorrect edge that isn't the buffer so we know to swap with this position
		}
	}
	else	// We run the same code here, but return -2 to indicate that we aren't starting a new cycle
	{
		for (int i = 0; i < 24; i++)
		{
			if (i == 1 || i == 10)	// Skip over the buffer because it will be solved if all other pieces are
				continue;

			if (c.getEdge(CubeFace(i / 4), i % 4) != solved.getEdge(CubeFace(i / 4), i % 4))
				return -2;
		}
	}

	return -1;
}
