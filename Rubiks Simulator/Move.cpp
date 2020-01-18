#include "Move.h"

Move::Move()
{
	target = MoveTarget::NONE;
	type = MoveType::NONE;
}

int Move::setMove(const std::string &s)
{
	if (s.size() < 1)
		return 1;

	// Standard 6 moves
	if (s[0] == 'U' || s[0] == 'F' || s[0] == 'R' || s[0] == 'B' || s[0] == 'L' || s[0] == 'D')
		return parseStandard(s);

	// Standard 6 wide moves (Lower case notation)
	if (s[0] == 'u' || s[0] == 'f' || s[0] == 'r' || s[0] == 'b' || s[0] == 'l' || s[0] == 'd')
		return parseWide(s);

	// Slice moves
	if (s[0] == 'M' || s[0] == 'E' || s[0] == 'S')
		return parseSlice(s);

	// Cube rotations
	if (s[0] == 'X' || s[0] == 'x' || s[0] == 'Y' || s[0] == 'y' || s[0] == 'Z' || s[0] == 'z')
		return parseRotation(s);
	
	return 1;
}

std::string Move::toStr() const
{
	std::string tmp = "";

	switch (target)
	{
	case MoveTarget::UP:
		tmp += 'U';
		break;
	case MoveTarget::FRONT:
		tmp += 'F';
		break;
	case MoveTarget::RIGHT:
		tmp += 'R';
		break;
	case MoveTarget::BACK:
		tmp += 'B';
		break;
	case MoveTarget::LEFT:
		tmp += 'L';
		break;
	case MoveTarget::DOWN:
		tmp += 'D';
		break;

	case MoveTarget::MIDDLE:
		tmp += 'M';
		break;
	case MoveTarget::EQUATOR:
		tmp += 'E';
		break;
	case MoveTarget::SIDE:
		tmp += 'S';
		break;

	case MoveTarget::ROTATIONX:
		tmp += 'x';
		break;
	case MoveTarget::ROTATIONY:
		tmp += 'y';
		break;
	case MoveTarget::ROTATIONZ:
		tmp += 'z';
		break;
	}

	if (type == MoveType::CCW)
		tmp += '\'';
	else if (type == MoveType::DOUBLE)
		tmp += '2';
	else if (type == MoveType::WIDECW)
		tmp[0] += 'a' - 'A';
	else if (type == MoveType::WIDECCW)
	{
		tmp[0] += 'a' - 'A';
		tmp += '\'';
	}
	else if (type == MoveType::WIDEDOUBLE)
	{
		tmp[0] += 'a' - 'A';
		tmp += '2';
	}

	if (target == MoveTarget::NONE || type == MoveType::NONE)
		tmp = ".";	// Return a period which signals a pause if the move is invalid

	return tmp;
}

int Move::parseStandard(const std::string &s)
{
	switch (s[0])
	{
	case 'U':
		target = MoveTarget::UP;
		break;
	case 'F':
		target = MoveTarget::FRONT;
		break;
	case 'R':
		target = MoveTarget::RIGHT;
		break;
	case 'B':
		target = MoveTarget::BACK;
		break;
	case 'L':
		target = MoveTarget::LEFT;
		break;
	case 'D':
		target = MoveTarget::DOWN;
		break;
	}

	type = MoveType::NONE;
	if (s.size() == 1)
	{
		type = MoveType::CW;	// Clockwise moves are only 1 character long
	}
	else if (s[1] == '\'')
	{
		type = MoveType::CCW;
	}
	else if (s[1] == '2')
	{
		type = MoveType::DOUBLE;
	}
	else if (s[1] == 'w' || s[1] == 'W')	// Wide moves can be denoted by a 'w' or 'W' following the face
	{
		if (s.size() == 2)
		{
			type = MoveType::WIDECW;
		}
		else if (s[2] == '\'')
		{
			type = MoveType::WIDECCW;
		}
		else if (s[2] == '2')
		{
			type = MoveType::WIDEDOUBLE;
		}
	}

	if (type == MoveType::NONE)	// Check for an invalid state
	{
		target = MoveTarget::NONE;
		return 1;
	}

	return 0;
}

int Move::parseWide(const std::string &s)
{
	switch (s[0])
	{
	case 'u':
		target = MoveTarget::UP;
		break;
	case 'f':
		target = MoveTarget::FRONT;
		break;
	case 'r':
		target = MoveTarget::RIGHT;
		break;
	case 'b':
		target = MoveTarget::BACK;
		break;
	case 'l':
		target = MoveTarget::LEFT;
		break;
	case 'd':
		target = MoveTarget::DOWN;
		break;
	}

	type = MoveType::NONE;
	if (s.size() == 1)
	{
		type = MoveType::WIDECW;	// Clockwise moves are only 1 character long
	}
	else if (s[1] == '\'')
	{
		type = MoveType::WIDECCW;
	}
	else if (s[1] == '2')
	{
		type = MoveType::WIDEDOUBLE;
	}

	if (type == MoveType::NONE)	// Check for an invalid state
	{
		target = MoveTarget::NONE;
		return 1;
	}

	return 0;
}

int Move::parseRotation(const std::string & s)
{
	switch (s[0])
	{
	case 'X':
	case 'x':
		target = MoveTarget::ROTATIONX;
		break;
	case 'Y':
	case 'y':
		target = MoveTarget::ROTATIONY;
		break;
	case 'Z':
	case 'z':
		target = MoveTarget::ROTATIONZ;
		break;
	}

	type = MoveType::NONE;
	if (s.size() == 1)
	{
		type = MoveType::CW;	// Clockwise moves are only 1 character long
	}
	else if (s[1] == '\'')
	{
		type = MoveType::CCW;
	}
	else if (s[1] == '2')
	{
		type = MoveType::DOUBLE;
	}

	if (type == MoveType::NONE)	// Check for an invalid state
	{
		target = MoveTarget::NONE;
		return 1;
	}

	return 0;
}

int Move::parseSlice(const std::string & s)
{
	switch (s[0])
	{
	case 'M':
		target = MoveTarget::MIDDLE;
		break;
	case 'E':
		target = MoveTarget::EQUATOR;
		break;
	case 'S':
		target = MoveTarget::SIDE;
		break;
	}

	type = MoveType::NONE;
	if (s.size() == 1)
	{
		type = MoveType::CW;	// Clockwise moves are only 1 character long
	}
	else if (s[1] == '\'')
	{
		type = MoveType::CCW;
	}
	else if (s[1] == '2')
	{
		type = MoveType::DOUBLE;
	}

	if (type == MoveType::NONE)	// Check for an invalid state
	{
		target = MoveTarget::NONE;
		return 1;
	}

	return 0;
}
