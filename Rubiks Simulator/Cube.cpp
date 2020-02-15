#include "Cube.h"

Cube::Cube()
{
	for (int i = 0; i < 6; i++)
	{
		centerArr[i] = (CubeColor)i;
	}

	for (int i = 0; i < 24; i++)
	{
		edgeArr[i].p = (CubeColor)(i / 4);
		edgeArr[i].s = (CubeColor)((i / 4 + i % 4 + (i % 4 < 2 ? 1 : 2)) % 6);	// Offset from the primary color by 1, 2, 4, 5
		edgeArr[i].next = nullptr;
	}

	for (int i = 0; i < 24; i++)
	{
		for (int o = 0; o < 24; o++)
		{
			if (edgeArr[i].p == edgeArr[o].s && edgeArr[i].s == edgeArr[o].p)
			{
				edgeArr[i].next = &edgeArr[o];
				break;
			}
		}
	}

	for (int i = 0; i < 24; i++)
	{
		cornerArr[i].p = (CubeColor)(i / 4);
		cornerArr[i].s = (CubeColor)((i / 4 + i % 4 + (i % 4 < 2 ? 1 : 2)) % 6);
		cornerArr[i].t = (CubeColor)((i / 4 + i % 4 + (i % 4 < 1 ? 2 : i % 4 != 3 ? 3 : 4)) % 6);
		cornerArr[i].next = nullptr;
	}

	for (int i = 0; i < 24; i++)
	{
		for (int o = 0; o < 24; o++)
		{
			if (cornerArr[i].p == cornerArr[o].s && cornerArr[i].s == cornerArr[o].p)
			{
				cornerArr[i].next = &cornerArr[o];
				break;
			}
		}
	}

	currentAlg = Algorithm("");
	algPos = 0;
}

CubeColor Cube::getCenter(CubeFace f)
{
	return CubeColor(centerArr[f]);
}

Cube::Edge Cube::getEdge(CubeFace f, int pos)
{
	return edgeArr[f * 4 + pos];
}

Cube::Corner Cube::getCorner(CubeFace f, int pos)
{
	return cornerArr[f * 4 + pos];
}

void Cube::setAlg(Algorithm a)
{
	currentAlg = a;
}

void Cube::setAlg(Move m)
{
	currentAlg = Algorithm(m);
}

void Cube::executeAlg()
{
	for (int i = algPos; i < currentAlg.getSize(); i++)
	{
		stepAlg();
	}
}

void Cube::stepAlg()
{
	if (algPos >= currentAlg.getSize())
	{
		currentAlg = Algorithm("");
		algPos = 0;
		return;
	}

	Move m = currentAlg.getMove(algPos);
	if ((int)m.getTarget() >= 0 && (int)m.getTarget() < 6)	// Regular turns
	{
		CubeFace f = (CubeFace)m.getTarget();
	}
	else if ((int)m.getTarget() >= 6 && (int)m.getTarget() < 9)	// Slice
	{

	}
	else if ((int)m.getTarget() >= 9 && (int)m.getTarget() < 12)	// Cube rotations
	{

	}
}
