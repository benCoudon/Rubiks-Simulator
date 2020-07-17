#include "Cube.h"

Cube::Cube(Algorithm a)
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

	currentAlg = a;
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

	setAlg(Algorithm());
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

void Cube::resetCube()
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

	Algorithm a;
	currentAlg = a;
	algPos = 0;
}

void Cube::scrambleCube()
{
	resetCube();
	Algorithm scramble = generateScramble();
	setAlg(scramble);
	executeAlg();
}

bool Cube::operator==(const Cube &right) const
{
	for (int i = 0; i < 24; i++)
	{
		if (edgeArr[i].p != right.edgeArr[i].p || edgeArr[i].s != right.edgeArr[i].s || edgeArr[i].next != right.edgeArr[i].next)
			return false;
		if (cornerArr[i].p != right.cornerArr[i].p || cornerArr[i].s != right.cornerArr[i].s || cornerArr[i].t != right.cornerArr[i].t || cornerArr[i].next != right.cornerArr[i].next)
			return false;
	}

	if (currentAlg.toStr() != right.currentAlg.toStr() || algPos != right.algPos)
		return false;

	return true;
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
	int edgeTargets[4];
	int cornerTargets[4];
	for (int i = 0; i < 4; i++)
	{
		edgeTargets[i] = f * 4 + i;
		cornerTargets[i] = f * 4 + i;
	}

	// Due to the way that the cube is stored in memory, odd and even faces rotate in opposite directions
	if ((m.getType() == Move::MoveType::CW && f % 2 == 0) || (m.getType() == Move::MoveType::CCW && f % 2 == 1))
	{
		swapEdges(edgeTargets);
		swapCorners(cornerTargets);
	}
	else if ((m.getType() == Move::MoveType::CCW && f % 2 == 0) || (m.getType() == Move::MoveType::CW && f % 2 == 1))
	{
		swapEdgesReverse(edgeTargets);
		swapCornersReverse(cornerTargets);
	}
	else if (m.getType() == Move::MoveType::DOUBLE)
	{
		swapEdgesDouble(edgeTargets);
		swapCornersDouble(cornerTargets);
	}
	else	// Wide turns
	{
		Move sliceEquiv;	// Create a slice move that makes the regular turn equivalent to a wide turn
		switch (m.getTarget())
		{
		case Move::MoveTarget::UP:
			if (m.getType() == Move::MoveType::WIDECW)
				sliceEquiv.setMove("E'");
			else if (m.getType() == Move::MoveType::WIDECCW)
				sliceEquiv.setMove("E");
			else
				sliceEquiv.setMove("E2");
			break;
		case Move::MoveTarget::FRONT:
			if (m.getType() == Move::MoveType::WIDECW)
				sliceEquiv.setMove("S");
			else if (m.getType() == Move::MoveType::WIDECCW)
				sliceEquiv.setMove("S'");
			else
				sliceEquiv.setMove("S2");
			break;
		case Move::MoveTarget::RIGHT:
			if (m.getType() == Move::MoveType::WIDECW)
				sliceEquiv.setMove("M'");
			else if (m.getType() == Move::MoveType::WIDECCW)
				sliceEquiv.setMove("M");
			else
				sliceEquiv.setMove("M2");
			break;
		case Move::MoveTarget::DOWN:
			if (m.getType() == Move::MoveType::WIDECW)
				sliceEquiv.setMove("E");
			else if (m.getType() == Move::MoveType::WIDECCW)
				sliceEquiv.setMove("E'");
			else
				sliceEquiv.setMove("E2");
			break;
		case Move::MoveTarget::BACK:
			if (m.getType() == Move::MoveType::WIDECW)
				sliceEquiv.setMove("S'");
			else if (m.getType() == Move::MoveType::WIDECCW)
				sliceEquiv.setMove("S");
			else
				sliceEquiv.setMove("S2");
			break;
		case Move::MoveTarget::LEFT:
			if (m.getType() == Move::MoveType::WIDECW)
				sliceEquiv.setMove("M");
			else if (m.getType() == Move::MoveType::WIDECCW)
				sliceEquiv.setMove("M'");
			else
				sliceEquiv.setMove("M2");
			break;
		}
		sliceCube(sliceEquiv);

		if ((m.getType() == Move::MoveType::WIDECW && f % 2 == 0) || (m.getType() == Move::MoveType::WIDECCW && f % 2 == 1))
		{
			swapEdges(edgeTargets);
			swapCorners(cornerTargets);
		}
		else if ((m.getType() == Move::MoveType::WIDECCW && f % 2 == 0) || (m.getType() == Move::MoveType::WIDECW && f % 2 == 1))
		{
			swapEdgesReverse(edgeTargets);
			swapCornersReverse(cornerTargets);
		}
		else if (m.getType() == Move::MoveType::WIDEDOUBLE)
		{
			swapEdgesDouble(edgeTargets);
			swapCornersDouble(cornerTargets);
		}
	}
}

void Cube::sliceCube(Move m)
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

	switch (m.getType())
	{
	case Move::MoveType::CW:
		swapCenters((int*)&targetCenters[0]);
		swapEdges(&targetEdges[0]);

		break;

	case Move::MoveType::CCW:
		swapCentersReverse((int*)&targetCenters[0]);
		swapEdgesReverse(&targetEdges[0]);

		break;

	case Move::MoveType::DOUBLE:
		swapCentersDouble((int*)&targetCenters[0]);
		swapEdgesDouble(&targetEdges[0]);

		break;
	}
}

void Cube::rotateCube(Move m)
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
		centerTarget[1] = (CubeFace)3;
		centerTarget[2] = (CubeFace)5;
		centerTarget[3] = (CubeFace)0;

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

	switch (m.getType())
	{
	case Move::MoveType::CW:
		swapCenters((int*)&centerTarget[0]);

		swapEdges(&edgeTarget[0]);
		swapEdges(&edgeTarget[4]);
		swapEdges(&edgeTarget[8]);

		swapCorners(&cornerTarget[0]);
		swapCorners(&cornerTarget[4]);

		break;

	case Move::MoveType::CCW:
		swapCentersReverse((int*)&centerTarget[0]);

		swapEdgesReverse(&edgeTarget[0]);
		swapEdgesReverse(&edgeTarget[4]);
		swapEdgesReverse(&edgeTarget[8]);

		swapCornersReverse(&cornerTarget[0]);
		swapCornersReverse(&cornerTarget[4]);

		break;

	case Move::MoveType::DOUBLE:
		swapCentersDouble((int*)&centerTarget[0]);

		swapEdgesDouble(&edgeTarget[0]);
		swapEdgesDouble(&edgeTarget[4]);
		swapEdgesDouble(&edgeTarget[8]);

		swapCornersDouble(&cornerTarget[0]);
		swapCornersDouble(&cornerTarget[4]);

		break;
	}
}

void Cube::swapCenters(int pos[])
{
	CubeColor tmpCenter = centerArr[pos[0]];
	centerArr[pos[0]] = centerArr[pos[1]];
	centerArr[pos[1]] = centerArr[pos[2]];
	centerArr[pos[2]] = centerArr[pos[3]];
	centerArr[pos[3]] = tmpCenter;

	recalculateNext();
}

void Cube::swapCentersReverse(int pos[])
{
	CubeColor tmpCenter = centerArr[pos[3]];
	centerArr[pos[3]] = centerArr[pos[2]];
	centerArr[pos[2]] = centerArr[pos[1]];
	centerArr[pos[1]] = centerArr[pos[0]];
	centerArr[pos[0]] = tmpCenter;

	recalculateNext();
}

void Cube::swapCentersDouble(int pos[])
{
	CubeColor tmpCenter = centerArr[pos[0]];
	centerArr[pos[0]] = centerArr[pos[2]];
	centerArr[pos[2]] = tmpCenter;
	tmpCenter = centerArr[pos[1]];
	centerArr[pos[1]] = centerArr[pos[3]];
	centerArr[pos[3]] = tmpCenter;

	recalculateNext();
}

void Cube::swapEdges(int pos[])
{
	Cube::Edge tmpEdge = edgeArr[edgeArr[pos[0]].next];
	edgeArr[edgeArr[pos[0]].next] = edgeArr[edgeArr[pos[1]].next];
	edgeArr[edgeArr[pos[1]].next] = edgeArr[edgeArr[pos[2]].next];
	edgeArr[edgeArr[pos[2]].next] = edgeArr[edgeArr[pos[3]].next];
	edgeArr[edgeArr[pos[3]].next] = tmpEdge;

	tmpEdge = edgeArr[pos[0]];
	edgeArr[pos[0]] = edgeArr[pos[1]];
	edgeArr[pos[1]] = edgeArr[pos[2]];
	edgeArr[pos[2]] = edgeArr[pos[3]];
	edgeArr[pos[3]] = tmpEdge;

	recalculateNext();
}

void Cube::swapEdgesReverse(int pos[])
{
	Cube::Edge tmpEdge = edgeArr[edgeArr[pos[3]].next];
	edgeArr[edgeArr[pos[3]].next] = edgeArr[edgeArr[pos[2]].next];
	edgeArr[edgeArr[pos[2]].next] = edgeArr[edgeArr[pos[1]].next];
	edgeArr[edgeArr[pos[1]].next] = edgeArr[edgeArr[pos[0]].next];
	edgeArr[edgeArr[pos[0]].next] = tmpEdge;

	tmpEdge = edgeArr[pos[3]];
	edgeArr[pos[3]] = edgeArr[pos[2]];
	edgeArr[pos[2]] = edgeArr[pos[1]];
	edgeArr[pos[1]] = edgeArr[pos[0]];
	edgeArr[pos[0]] = tmpEdge;

	recalculateNext();
}

void Cube::swapEdgesDouble(int pos[])
{
	Cube::Edge tmpEdge = edgeArr[edgeArr[pos[0]].next];
	edgeArr[edgeArr[pos[0]].next] = edgeArr[edgeArr[pos[2]].next];
	edgeArr[edgeArr[pos[2]].next] = tmpEdge;
	tmpEdge = edgeArr[edgeArr[pos[1]].next];
	edgeArr[edgeArr[pos[1]].next] = edgeArr[edgeArr[pos[3]].next];
	edgeArr[edgeArr[pos[3]].next] = tmpEdge;

	tmpEdge = edgeArr[pos[0]];
	edgeArr[pos[0]] = edgeArr[pos[2]];
	edgeArr[pos[2]] = tmpEdge;
	tmpEdge = edgeArr[pos[1]];
	edgeArr[pos[1]] = edgeArr[pos[3]];
	edgeArr[pos[3]] = tmpEdge;

	recalculateNext();
}

void Cube::swapCorners(int pos[])
{
	Cube::Corner tmpCorner = cornerArr[cornerArr[cornerArr[pos[0]].next].next];
	cornerArr[cornerArr[cornerArr[pos[0]].next].next] = cornerArr[cornerArr[cornerArr[pos[1]].next].next];
	cornerArr[cornerArr[cornerArr[pos[1]].next].next] = cornerArr[cornerArr[cornerArr[pos[2]].next].next];
	cornerArr[cornerArr[cornerArr[pos[2]].next].next] = cornerArr[cornerArr[cornerArr[pos[3]].next].next];
	cornerArr[cornerArr[cornerArr[pos[3]].next].next] = tmpCorner;

	tmpCorner = cornerArr[cornerArr[pos[0]].next];
	cornerArr[cornerArr[pos[0]].next] = cornerArr[cornerArr[pos[1]].next];
	cornerArr[cornerArr[pos[1]].next] = cornerArr[cornerArr[pos[2]].next];
	cornerArr[cornerArr[pos[2]].next] = cornerArr[cornerArr[pos[3]].next];
	cornerArr[cornerArr[pos[3]].next] = tmpCorner;

	tmpCorner = cornerArr[pos[0]];
	cornerArr[pos[0]] = cornerArr[pos[1]];
	cornerArr[pos[1]] = cornerArr[pos[2]];
	cornerArr[pos[2]] = cornerArr[pos[3]];
	cornerArr[pos[3]] = tmpCorner;

	recalculateNext();
}

void Cube::swapCornersReverse(int pos[])
{
	Cube::Corner tmpCorner = cornerArr[cornerArr[cornerArr[pos[3]].next].next];
	cornerArr[cornerArr[cornerArr[pos[3]].next].next] = cornerArr[cornerArr[cornerArr[pos[2]].next].next];
	cornerArr[cornerArr[cornerArr[pos[2]].next].next] = cornerArr[cornerArr[cornerArr[pos[1]].next].next];
	cornerArr[cornerArr[cornerArr[pos[1]].next].next] = cornerArr[cornerArr[cornerArr[pos[0]].next].next];
	cornerArr[cornerArr[cornerArr[pos[0]].next].next] = tmpCorner;

	tmpCorner = cornerArr[cornerArr[pos[3]].next];
	cornerArr[cornerArr[pos[3]].next] = cornerArr[cornerArr[pos[2]].next];
	cornerArr[cornerArr[pos[2]].next] = cornerArr[cornerArr[pos[1]].next];
	cornerArr[cornerArr[pos[1]].next] = cornerArr[cornerArr[pos[0]].next];
	cornerArr[cornerArr[pos[0]].next] = tmpCorner;

	tmpCorner = cornerArr[pos[3]];
	cornerArr[pos[3]] = cornerArr[pos[2]];
	cornerArr[pos[2]] = cornerArr[pos[1]];
	cornerArr[pos[1]] = cornerArr[pos[0]];
	cornerArr[pos[0]] = tmpCorner;

	recalculateNext();
}

void Cube::swapCornersDouble(int pos[])
{
	Cube::Corner tmpCorner = cornerArr[cornerArr[cornerArr[pos[0]].next].next];
	cornerArr[cornerArr[cornerArr[pos[0]].next].next] = cornerArr[cornerArr[cornerArr[pos[2]].next].next];
	cornerArr[cornerArr[cornerArr[pos[2]].next].next] = tmpCorner; 
	tmpCorner = cornerArr[cornerArr[cornerArr[pos[1]].next].next];
	cornerArr[cornerArr[cornerArr[pos[1]].next].next] = cornerArr[cornerArr[cornerArr[pos[3]].next].next];
	cornerArr[cornerArr[cornerArr[pos[3]].next].next] = tmpCorner;

	tmpCorner = cornerArr[cornerArr[pos[0]].next];
	cornerArr[cornerArr[pos[0]].next] = cornerArr[cornerArr[pos[2]].next];
	cornerArr[cornerArr[pos[2]].next] = tmpCorner;
	tmpCorner = cornerArr[cornerArr[pos[1]].next];
	cornerArr[cornerArr[pos[1]].next] = cornerArr[cornerArr[pos[3]].next];
	cornerArr[cornerArr[pos[3]].next] = tmpCorner;

	tmpCorner = cornerArr[pos[0]];
	cornerArr[pos[0]] = cornerArr[pos[2]];
	cornerArr[pos[2]] = tmpCorner;
	tmpCorner = cornerArr[pos[1]];
	cornerArr[pos[1]] = cornerArr[pos[3]];
	cornerArr[pos[3]] = tmpCorner;

	recalculateNext();
}
