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
		CubeFace targets[4];
		if (m.getTarget() == Move::MoveTarget::ROTATIONX)
		{
			targets[0] = (CubeFace)0;
			targets[1] = (CubeFace)1;
			targets[2] = (CubeFace)3;
			targets[3] = (CubeFace)4;
		}
		else if (m.getTarget() == Move::MoveTarget::ROTATIONY)
		{
			targets[0] = (CubeFace)1;
			targets[1] = (CubeFace)2;
			targets[2] = (CubeFace)4;
			targets[3] = (CubeFace)5;
		}
		else
		{
			targets[0] = (CubeFace)0;
			targets[1] = (CubeFace)5;
			targets[2] = (CubeFace)3;
			targets[3] = (CubeFace)2;
		}

		if (m.getType() == Move::MoveType::CCW)
		{
			CubeFace buf = targets[0];
			targets[0] = targets[3];
			targets[3] = buf;
			buf = targets[1];
			targets[1] = targets[2];
			targets[2] = buf;
		}
		else if (m.getType() == Move::MoveType::DOUBLE)
		{

		}

		CubeColor centerBuf = centerArr[targets[0]];
		centerArr[targets[0]] = centerArr[targets[1]];
		centerArr[targets[1]] = centerArr[targets[2]];
		centerArr[targets[2]] = centerArr[targets[3]];
		centerArr[targets[3]] = centerBuf;

		for (int i = 0; i < 4; i++)
		{
			Cube::Edge edgeBuf = edgeArr[targets[0] * 4 + i];
			edgeArr[targets[0] * 4 + i] = edgeArr[targets[1] * 4 + i];
			edgeArr[targets[1] * 4 + i] = edgeArr[targets[2] * 4 + i];
			edgeArr[targets[2] * 4 + i] = edgeArr[targets[3] * 4 + i];
			edgeArr[targets[3] * 4 + i] = edgeBuf;

			Cube::Corner cornerBuf = cornerArr[targets[0] * 4 + i];
			cornerArr[targets[0] * 4 + i] = cornerArr[targets[1] * 4 + i];
			cornerArr[targets[1] * 4 + i] = cornerArr[targets[2] * 4 + i];
			cornerArr[targets[2] * 4 + i] = cornerArr[targets[3] * 4 + i];
			cornerArr[targets[3] * 4 + i] = cornerBuf;
		}
	}
}
