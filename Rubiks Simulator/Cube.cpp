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
		edgeArr[i].next = -1;
	}

	for (int i = 0; i < 24; i++)
	{
		cornerArr[i].p = (CubeColor)(i / 4);
		cornerArr[i].s = (CubeColor)((i / 4 + i % 4 + (i % 4 < 2 ? 1 : 2)) % 6);
		cornerArr[i].t = (CubeColor)((i / 4 + i % 4 + (i % 4 < 1 ? 2 : i % 4 != 3 ? 3 : 4)) % 6);
		cornerArr[i].next = -1;
	}

	for (int i = 0; i < 24; i++)
	{
		if ((i / 4) % 2 == 1)	// Swap secondary and tertiary for odd faces
		{
			CubeColor tmp = cornerArr[i].s;
			cornerArr[i].s = cornerArr[i].t;
			cornerArr[i].t = tmp;
		}
	}

	recalculateNext();

	currentAlg = Algorithm("");
	algPos = 0;
}

CubeColor Cube::getCenter(CubeFace f) const
{
	return CubeColor(centerArr[f]);
}

Cube::Edge Cube::getEdge(CubeFace f, int pos) const
{
	return edgeArr[f * 4 + pos];
}

Cube::Corner Cube::getCorner(CubeFace f, int pos) const
{
	return cornerArr[f * 4 + pos];
}

void Cube::setAlg(Algorithm a)
{
	currentAlg = a;
	algPos = 0;
}

void Cube::setAlg(Move m)
{
	currentAlg = Algorithm(m);
	algPos = 0;
}

void Cube::executeAlg()
{
	for (int i = algPos; i < currentAlg.getSize(); i++)
	{
		stepAlg();
	}

	setAlg(Algorithm(""));
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
		turnCube(m);
	}
	else if ((int)m.getTarget() >= 6 && (int)m.getTarget() < 9)	// Slice
	{
		sliceCube(m);
	}
	else if ((int)m.getTarget() >= 9 && (int)m.getTarget() < 12)	// Cube rotations
	{
		rotateCube(m);
	}

	algPos++;
}

void Cube::recalculateNext()
{
	for (int i = 0; i < 24; i++)
	{
		for (int o = 0; o < 24; o++)
		{
			if (edgeArr[i].p == edgeArr[o].s && edgeArr[i].s == edgeArr[o].p)
			{
				edgeArr[i].next = o;
				break;
			}
		}
	}

	for (int i = 0; i < 24; i++)
	{
		for (int o = 0; o < 24; o++)
		{
			if (cornerArr[i].p == cornerArr[o].s && cornerArr[i].s == cornerArr[o].t && cornerArr[i].t == cornerArr[o].p)
			{
				cornerArr[i].next = o;
				break;
			}
		}
	}
}

void Cube::turnCube(Move m)
{
	CubeFace f = (CubeFace)m.getTarget();

	if ((m.getType() == Move::MoveType::CW && f % 2 == 0) || (m.getType() == Move::MoveType::CCW && f % 2 == 1))
	{
		turnNormal(f);
	}
	else if ((m.getType() == Move::MoveType::CCW && f % 2 == 0) || (m.getType() == Move::MoveType::CW && f % 2 == 1))
	{
		turnReverse(f);
	}
	else if (m.getType() == Move::MoveType::DOUBLE)
	{
		turnDouble(f);
	}

	recalculateNext();
}

void Cube::sliceCube(Move m)
{
	switch (m.getType())
	{
	case Move::MoveType::CW:
		sliceNormal(m);
		break;

	case Move::MoveType::CCW:
		sliceReverse(m);
		break;

	case Move::MoveType::DOUBLE:
		sliceDouble(m);
		break;
	}

	recalculateNext();
}

void Cube::rotateCube(Move m)
{
	switch (m.getType())
	{
	case Move::MoveType::CW:
		rotateNormal(m);
		break;

	case Move::MoveType::CCW:
		rotateReverse(m);
		break;

	case Move::MoveType::DOUBLE:
		rotateDouble(m);
		break;
	}

	recalculateNext();
}

void Cube::turnNormal(int f)
{
	Cube::Edge tmpEdge = edgeArr[edgeArr[f * 4].next];
	edgeArr[edgeArr[f * 4].next] = edgeArr[edgeArr[f * 4 + 1].next];
	edgeArr[edgeArr[f * 4 + 1].next] = edgeArr[edgeArr[f * 4 + 2].next];
	edgeArr[edgeArr[f * 4 + 2].next] = edgeArr[edgeArr[f * 4 + 3].next];
	edgeArr[edgeArr[f * 4 + 3].next] = tmpEdge;

	tmpEdge = edgeArr[f * 4];
	edgeArr[f * 4] = edgeArr[f * 4 + 1];
	edgeArr[f * 4 + 1] = edgeArr[f * 4 + 2];
	edgeArr[f * 4 + 2] = edgeArr[f * 4 + 3];
	edgeArr[f * 4 + 3] = tmpEdge;

	Cube::Corner tmpCorner = cornerArr[cornerArr[cornerArr[f * 4].next].next];
	cornerArr[cornerArr[cornerArr[f * 4].next].next] = cornerArr[cornerArr[cornerArr[f * 4 + 1].next].next];
	cornerArr[cornerArr[cornerArr[f * 4 + 1].next].next] = cornerArr[cornerArr[cornerArr[f * 4 + 2].next].next];
	cornerArr[cornerArr[cornerArr[f * 4 + 2].next].next] = cornerArr[cornerArr[cornerArr[f * 4 + 3].next].next];
	cornerArr[cornerArr[cornerArr[f * 4 + 3].next].next] = tmpCorner;

	tmpCorner = cornerArr[cornerArr[f * 4].next];
	cornerArr[cornerArr[f * 4].next] = cornerArr[cornerArr[f * 4 + 1].next];
	cornerArr[cornerArr[f * 4 + 1].next] = cornerArr[cornerArr[f * 4 + 2].next];
	cornerArr[cornerArr[f * 4 + 2].next] = cornerArr[cornerArr[f * 4 + 3].next];
	cornerArr[cornerArr[f * 4 + 3].next] = tmpCorner;

	tmpCorner = cornerArr[f * 4];
	cornerArr[f * 4] = cornerArr[f * 4 + 1];
	cornerArr[f * 4 + 1] = cornerArr[f * 4 + 2];
	cornerArr[f * 4 + 2] = cornerArr[f * 4 + 3];
	cornerArr[f * 4 + 3] = tmpCorner;
}

void Cube::turnReverse(int f)
{
	Cube::Edge tmpEdge = edgeArr[edgeArr[f * 4 + 3].next];
	edgeArr[edgeArr[f * 4 + 3].next] = edgeArr[edgeArr[f * 4 + 2].next];
	edgeArr[edgeArr[f * 4 + 2].next] = edgeArr[edgeArr[f * 4 + 1].next];
	edgeArr[edgeArr[f * 4 + 1].next] = edgeArr[edgeArr[f * 4].next];
	edgeArr[edgeArr[f * 4].next] = tmpEdge;

	tmpEdge = edgeArr[f * 4 + 3];
	edgeArr[f * 4 + 3] = edgeArr[f * 4 + 2];
	edgeArr[f * 4 + 2] = edgeArr[f * 4 + 1];
	edgeArr[f * 4 + 1] = edgeArr[f * 4];
	edgeArr[f * 4] = tmpEdge;

	Cube::Corner tmpCorner = cornerArr[cornerArr[cornerArr[f * 4 + 3].next].next];
	cornerArr[cornerArr[cornerArr[f * 4 + 3].next].next] = cornerArr[cornerArr[cornerArr[f * 4 + 2].next].next];
	cornerArr[cornerArr[cornerArr[f * 4 + 2].next].next] = cornerArr[cornerArr[cornerArr[f * 4 + 1].next].next];
	cornerArr[cornerArr[cornerArr[f * 4 + 1].next].next] = cornerArr[cornerArr[cornerArr[f * 4].next].next];
	cornerArr[cornerArr[cornerArr[f * 4].next].next] = tmpCorner;

	tmpCorner = cornerArr[cornerArr[f * 4 + 3].next];
	cornerArr[cornerArr[f * 4 + 3].next] = cornerArr[cornerArr[f * 4 + 2].next];
	cornerArr[cornerArr[f * 4 + 2].next] = cornerArr[cornerArr[f * 4 + 1].next];
	cornerArr[cornerArr[f * 4 + 1].next] = cornerArr[cornerArr[f * 4].next];
	cornerArr[cornerArr[f * 4].next] = tmpCorner;

	tmpCorner = cornerArr[f * 4 + 3];
	cornerArr[f * 4 + 3] = cornerArr[f * 4 + 2];
	cornerArr[f * 4 + 2] = cornerArr[f * 4 + 1];
	cornerArr[f * 4 + 1] = cornerArr[f * 4];
	cornerArr[f * 4] = tmpCorner;
}

void Cube::turnDouble(int f)
{
	Cube::Edge tmpEdge = edgeArr[edgeArr[f * 4].next];
	edgeArr[edgeArr[f * 4].next] = edgeArr[edgeArr[f * 4 + 2].next];
	edgeArr[edgeArr[f * 4 + 2].next] = tmpEdge;
	Cube::Edge tmpEdge2 = edgeArr[edgeArr[f * 4 + 1].next];
	edgeArr[edgeArr[f * 4 + 1].next] = edgeArr[edgeArr[f * 4 + 3].next];
	edgeArr[edgeArr[f * 4 + 3].next] = tmpEdge2;

	tmpEdge = edgeArr[f * 4];
	edgeArr[f * 4] = edgeArr[f * 4 + 2];
	edgeArr[f * 4 + 2] = tmpEdge;
	tmpEdge2 = edgeArr[f * 4 + 1];
	edgeArr[f * 4 + 1] = edgeArr[f * 4 + 3];
	edgeArr[f * 4 + 3] = tmpEdge2;

	Cube::Corner tmpCorner = cornerArr[cornerArr[cornerArr[f * 4].next].next];
	cornerArr[cornerArr[cornerArr[f * 4].next].next] = cornerArr[cornerArr[cornerArr[f * 4 + 2].next].next];
	cornerArr[cornerArr[cornerArr[f * 4 + 2].next].next] = tmpCorner;
	Cube::Corner tmpCorner2 = cornerArr[cornerArr[cornerArr[f * 4 + 1].next].next];
	cornerArr[cornerArr[cornerArr[f * 4 + 1].next].next] = cornerArr[cornerArr[cornerArr[f * 4 + 3].next].next];
	cornerArr[cornerArr[cornerArr[f * 4 + 3].next].next] = tmpCorner2;

	tmpCorner = cornerArr[cornerArr[f * 4].next];
	cornerArr[cornerArr[f * 4].next] = cornerArr[cornerArr[f * 4 + 2].next];
	cornerArr[cornerArr[f * 4 + 2].next] = tmpCorner;
	tmpCorner2 = cornerArr[cornerArr[f * 4 + 1].next];
	cornerArr[cornerArr[f * 4 + 1].next] = cornerArr[cornerArr[f * 4 + 3].next];
	cornerArr[cornerArr[f * 4 + 3].next] = tmpCorner2;

	tmpCorner = cornerArr[f * 4];
	cornerArr[f * 4] = cornerArr[f * 4 + 2];
	cornerArr[f * 4 + 2] = tmpCorner;
	tmpCorner2 = cornerArr[f * 4 + 1];
	cornerArr[f * 4 + 1] = cornerArr[f * 4 + 3];
	cornerArr[f * 4 + 3] = tmpCorner2;
}

void Cube::sliceNormal(Move m)
{
	CubeFace targetCenters[4];
	int targetEdges[4];
	switch (m.getTarget())
	{
	case Move::MoveTarget::MIDDLE:
		targetCenters[0] = (CubeFace)4;
		targetCenters[1] = (CubeFace)3;
		targetCenters[2] = (CubeFace)1;
		targetCenters[3] = (CubeFace)0;

		targetEdges[0] = 17;
		targetEdges[1] = 12;
		targetEdges[2] = 5;
		targetEdges[3] = 0;

		break;

	case Move::MoveTarget::EQUATOR:
		targetCenters[0] = (CubeFace)5;
		targetCenters[1] = (CubeFace)4;
		targetCenters[2] = (CubeFace)2;
		targetCenters[3] = (CubeFace)1;

		targetEdges[0] = 21;
		targetEdges[1] = 16;
		targetEdges[2] = 9;
		targetEdges[3] = 4;

		break;

	case Move::MoveTarget::SIDE:
		targetCenters[0] = (CubeFace)5;
		targetCenters[1] = (CubeFace)3;
		targetCenters[2] = (CubeFace)2;
		targetCenters[3] = (CubeFace)0;

		targetEdges[0] = 20;
		targetEdges[1] = 13;
		targetEdges[2] = 8;
		targetEdges[3] = 1;

		break;
	}

	CubeColor tmp = centerArr[targetCenters[0]];
	centerArr[targetCenters[0]] = centerArr[targetCenters[1]];
	centerArr[targetCenters[1]] = centerArr[targetCenters[2]];
	centerArr[targetCenters[2]] = centerArr[targetCenters[3]];
	centerArr[targetCenters[3]] = tmp;

	Cube::Edge tmpEdge = edgeArr[edgeArr[targetEdges[0]].next];
	edgeArr[edgeArr[targetEdges[0]].next] = edgeArr[edgeArr[targetEdges[1]].next];
	edgeArr[edgeArr[targetEdges[1]].next] = edgeArr[edgeArr[targetEdges[2]].next];
	edgeArr[edgeArr[targetEdges[2]].next] = edgeArr[edgeArr[targetEdges[3]].next];
	edgeArr[edgeArr[targetEdges[3]].next] = tmpEdge;

	tmpEdge = edgeArr[targetEdges[0]];
	edgeArr[targetEdges[0]] = edgeArr[targetEdges[1]];
	edgeArr[targetEdges[1]] = edgeArr[targetEdges[2]];
	edgeArr[targetEdges[2]] = edgeArr[targetEdges[3]];
	edgeArr[targetEdges[3]] = tmpEdge;
}

void Cube::sliceReverse(Move m)
{
	CubeFace targetCenters[4];
	int targetEdges[4];
	switch (m.getTarget())
	{
	case Move::MoveTarget::MIDDLE:
		targetCenters[0] = (CubeFace)4;
		targetCenters[1] = (CubeFace)3;
		targetCenters[2] = (CubeFace)1;
		targetCenters[3] = (CubeFace)0;

		targetEdges[0] = 17;
		targetEdges[1] = 12;
		targetEdges[2] = 5;
		targetEdges[3] = 0;

		break;

	case Move::MoveTarget::EQUATOR:
		targetCenters[0] = (CubeFace)5;
		targetCenters[1] = (CubeFace)4;
		targetCenters[2] = (CubeFace)2;
		targetCenters[3] = (CubeFace)1;

		targetEdges[0] = 21;
		targetEdges[1] = 16;
		targetEdges[2] = 9;
		targetEdges[3] = 4;

		break;

	case Move::MoveTarget::SIDE:
		targetCenters[0] = (CubeFace)5;
		targetCenters[1] = (CubeFace)3;
		targetCenters[2] = (CubeFace)2;
		targetCenters[3] = (CubeFace)0;

		targetEdges[0] = 20;
		targetEdges[1] = 13;
		targetEdges[2] = 8;
		targetEdges[3] = 1;

		break;
	}

	CubeColor tmp = centerArr[targetCenters[3]];
	centerArr[targetCenters[3]] = centerArr[targetCenters[2]];
	centerArr[targetCenters[2]] = centerArr[targetCenters[1]];
	centerArr[targetCenters[1]] = centerArr[targetCenters[0]];
	centerArr[targetCenters[0]] = tmp;

	Cube::Edge tmpEdge = edgeArr[edgeArr[targetEdges[3]].next];
	edgeArr[edgeArr[targetEdges[3]].next] = edgeArr[edgeArr[targetEdges[2]].next];
	edgeArr[edgeArr[targetEdges[2]].next] = edgeArr[edgeArr[targetEdges[1]].next];
	edgeArr[edgeArr[targetEdges[1]].next] = edgeArr[edgeArr[targetEdges[0]].next];
	edgeArr[edgeArr[targetEdges[0]].next] = tmpEdge;

	tmpEdge = edgeArr[targetEdges[3]];
	edgeArr[targetEdges[3]] = edgeArr[targetEdges[2]];
	edgeArr[targetEdges[2]] = edgeArr[targetEdges[1]];
	edgeArr[targetEdges[1]] = edgeArr[targetEdges[0]];
	edgeArr[targetEdges[0]] = tmpEdge;
}

void Cube::sliceDouble(Move m)
{
	CubeFace targetCenters[4];
	int targetEdges[4];
	switch (m.getTarget())
	{
	case Move::MoveTarget::MIDDLE:
		targetCenters[0] = (CubeFace)4;
		targetCenters[1] = (CubeFace)3;
		targetCenters[2] = (CubeFace)1;
		targetCenters[3] = (CubeFace)0;

		targetEdges[0] = 17;
		targetEdges[1] = 12;
		targetEdges[2] = 5;
		targetEdges[3] = 0;

		break;

	case Move::MoveTarget::EQUATOR:
		targetCenters[0] = (CubeFace)5;
		targetCenters[1] = (CubeFace)4;
		targetCenters[2] = (CubeFace)2;
		targetCenters[3] = (CubeFace)1;

		targetEdges[0] = 21;
		targetEdges[1] = 16;
		targetEdges[2] = 9;
		targetEdges[3] = 4;

		break;

	case Move::MoveTarget::SIDE:
		targetCenters[0] = (CubeFace)5;
		targetCenters[1] = (CubeFace)3;
		targetCenters[2] = (CubeFace)2;
		targetCenters[3] = (CubeFace)0;

		targetEdges[0] = 20;
		targetEdges[1] = 13;
		targetEdges[2] = 8;
		targetEdges[3] = 1;

		break;
	}

	CubeColor tmp = centerArr[targetCenters[0]];
	centerArr[targetCenters[0]] = centerArr[targetCenters[2]];
	centerArr[targetCenters[2]] = tmp;
	tmp = centerArr[targetCenters[1]];
	centerArr[targetCenters[1]] = centerArr[targetCenters[3]];
	centerArr[targetCenters[3]] = tmp;

	Cube::Edge tmpEdge = edgeArr[edgeArr[targetEdges[0]].next];
	edgeArr[edgeArr[targetEdges[0]].next] = edgeArr[edgeArr[targetEdges[2]].next];
	edgeArr[edgeArr[targetEdges[2]].next] = tmpEdge;
	tmpEdge = edgeArr[edgeArr[targetEdges[1]].next];
	edgeArr[edgeArr[targetEdges[1]].next] = edgeArr[edgeArr[targetEdges[3]].next];
	edgeArr[edgeArr[targetEdges[3]].next] = tmpEdge;

	tmpEdge = edgeArr[targetEdges[0]];
	edgeArr[targetEdges[0]] = edgeArr[targetEdges[2]];
	edgeArr[targetEdges[2]] = tmpEdge;
	tmpEdge = edgeArr[targetEdges[1]];
	edgeArr[targetEdges[1]] = edgeArr[targetEdges[3]];
	edgeArr[targetEdges[3]] = tmpEdge;
}

void Cube::rotateNormal(Move m)
{
	CubeFace centerTarget[4];
	int edgeTarget[12];
	int cornerTarget[8];

	switch (m.getTarget())
	{
	case Move::MoveTarget::ROTATIONX:
		centerTarget[0] = (CubeFace)0;
		centerTarget[1] = (CubeFace)1;
		centerTarget[2] = (CubeFace)3;
		centerTarget[3] = (CubeFace)4;

		edgeTarget[0] = 0;
		edgeTarget[1] = 5;
		edgeTarget[2] = 12;
		edgeTarget[3] = 17;

		edgeTarget[4] = 1;
		edgeTarget[5] = 4;
		edgeTarget[6] = 15;
		edgeTarget[7] = 18;

		edgeTarget[8] = 3;
		edgeTarget[9] = 6;
		edgeTarget[10] = 13;
		edgeTarget[11] = 16;

		cornerTarget[0] = 0;
		cornerTarget[1] = 4;
		cornerTarget[2] = 15;
		cornerTarget[3] = 17;

		cornerTarget[4] = 3;
		cornerTarget[5] = 5;
		cornerTarget[6] = 12;
		cornerTarget[7] = 16;

		break;

	case Move::MoveTarget::ROTATIONY:
		centerTarget[0] = (CubeFace)1;
		centerTarget[1] = (CubeFace)2;
		centerTarget[2] = (CubeFace)4;
		centerTarget[3] = (CubeFace)5;

		edgeTarget[0] = 4;
		edgeTarget[1] = 9;
		edgeTarget[2] = 16;
		edgeTarget[3] = 21;

		edgeTarget[4] = 7;
		edgeTarget[5] = 10;
		edgeTarget[6] = 17;
		edgeTarget[7] = 20;

		edgeTarget[8] = 5;
		edgeTarget[9] = 8;
		edgeTarget[10] = 19;
		edgeTarget[11] = 22;

		cornerTarget[0] = 7;
		cornerTarget[1] = 9;
		cornerTarget[2] = 16;
		cornerTarget[3] = 20;

		cornerTarget[4] = 4;
		cornerTarget[5] = 8;
		cornerTarget[6] = 19;
		cornerTarget[7] = 21;

		break;

	case Move::MoveTarget::ROTATIONZ:
		centerTarget[0] = (CubeFace)2;
		centerTarget[1] = (CubeFace)0;
		centerTarget[2] = (CubeFace)5;
		centerTarget[3] = (CubeFace)3;

		edgeTarget[0] = 1;
		edgeTarget[1] = 8;
		edgeTarget[2] = 13;
		edgeTarget[3] = 20;

		edgeTarget[4] = 2;
		edgeTarget[5] = 9;
		edgeTarget[6] = 12;
		edgeTarget[7] = 23;

		edgeTarget[8] = 0;
		edgeTarget[9] = 11;
		edgeTarget[10] = 14;
		edgeTarget[11] = 21;

		cornerTarget[0] = 1;
		cornerTarget[1] = 8;
		cornerTarget[2] = 12;
		cornerTarget[3] = 23;

		cornerTarget[4] = 0;
		cornerTarget[5] = 11;
		cornerTarget[6] = 13;
		cornerTarget[7] = 20;
		
		break;
	}

	CubeColor tmpCenter = centerArr[centerTarget[0]];
	centerArr[centerTarget[0]] = centerArr[centerTarget[1]];
	centerArr[centerTarget[1]] = centerArr[centerTarget[2]];
	centerArr[centerTarget[2]] = centerArr[centerTarget[3]];
	centerArr[centerTarget[3]] = tmpCenter;

	Cube::Edge tmpEdge = edgeArr[edgeArr[edgeTarget[0]].next];
	edgeArr[edgeArr[edgeTarget[0]].next] = edgeArr[edgeArr[edgeTarget[1]].next];
	edgeArr[edgeArr[edgeTarget[1]].next] = edgeArr[edgeArr[edgeTarget[2]].next];
	edgeArr[edgeArr[edgeTarget[2]].next] = edgeArr[edgeArr[edgeTarget[3]].next];
	edgeArr[edgeArr[edgeTarget[3]].next] = tmpEdge;
}

void Cube::rotateReverse(Move m)
{

}

void Cube::rotateDouble(Move m)
{

}
