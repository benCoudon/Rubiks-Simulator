#pragma once

#include <string>

class Move
{
public:
	enum class MoveTarget
	{
		NONE = -1,		// Signifies an invalid state

		UP = 0,			// These are the 6 basic faces of a cube
		FRONT = 1,
		RIGHT = 2,
		DOWN = 3,
		BACK = 4,
		LEFT =  5,

		MIDDLE = 6,		// Slice between R and L
		EQUATOR = 7,	// Slice between U and D
		SIDE = 8,		// Slice between F and B

		ROTATIONX = 9,	// Cube rotation where R and L maintain position
		ROTATIONY = 10,	// Cube rotation where U and D maintain position
		ROTATIONZ = 11, // Cube rotation where F and B maintain position
	};

	enum class MoveType
	{
		NONE = -1,		// Signifies an invalid state

		CW = 0,			// Clockwise 90 degrees
		CCW = 1,		// Counter-clockwise 90 degrees
		DOUBLE = 2,		// 180 degree rotation

		WIDECW = 3,		// Wide clockwise (Can not be used for targets > 5)
		WIDECCW = 4,	// Wide counter-clockwise (Can not be used for targets > 5)
		WIDEDOUBLE = 5	// Wide double (Can not be used for targets > 5)
	};

	Move();
	Move(const std::string &s);
	Move(MoveTarget tar, MoveType ty);

	int setMove(const std::string &s);	// Returns 0 on success and 1 if the string could not be parsed

	MoveTarget getTarget() const { return target; }
	MoveType getType() const { return type; }

	std::string toStr() const;

private:
	MoveTarget target;	// Stores which face or position the move acts on
	MoveType type;		// Stores the type of move performed on the target

	int parseStandard(const std::string &s);	// Parses the 2nd character if the first is a standard move
	int parseWide(const std::string &s);		// Parses the 2nd character if the first is a wide move (lower case notation)
	int parseSlice(const std::string &s);		// Parses the 2nd character if the first is a slice move
	int parseRotation(const std::string &s);	// Parses the 2nd character if the first is a rotation
};
