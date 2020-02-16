#ifndef CUBE_H
#define CUBE_H

#include <glm/glm.hpp>

#include "Algorithm.h"

enum CubeColor
{
	WHITE = 0,
	GREEN = 1,
	RED = 2,
	YELLOW = 3,
	BLUE = 4,
	ORANGE = 5
};

enum CubeFace
{
	UP = 0,
	FRONT = 1,
	RIGHT = 2,
	DOWN = 3,
	BACK = 4,
	LEFT = 5
};

glm::vec3 colorArr[6]
{
	glm::vec3(1.0, 1.0, 1.0),
	glm::vec3(0.0, 1.0, 0.0),
	glm::vec3(1.0, 0.0, 0.0),
	glm::vec3(1.0, 1.0, 0.0),
	glm::vec3(0.0, 0.0, 1.0),
	glm::vec3(1.0, 0.5, 0.0)
};

class Cube
{
public:
	struct Edge
	{
		CubeColor p;
		CubeColor s;

		int next;
	};

	struct Corner
	{
		CubeColor p;
		CubeColor s;
		CubeColor t;

		int next;
	};

	Cube();

	CubeColor getCenter(CubeFace f);
	Cube::Edge getEdge(CubeFace f, int pos);
	Cube::Corner getCorner(CubeFace f, int pos);

	void setAlg(Algorithm a);
	void setAlg(Move m);
	
	void executeAlg();
	void stepAlg();

	void turnCube(Move m);
	void rotateCube(Move m);

private:
	CubeColor centerArr[6];
	Edge edgeArr[24];
	Corner cornerArr[24];

	Algorithm currentAlg;
	int algPos;
};

#endif
