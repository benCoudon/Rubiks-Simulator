#pragma once

#include <glm/glm.hpp>

enum ButtonType
{
	RESET = 0,
	SCRAMBLE = 1,
};

class Button
{
public:
	Button(double x, double y, double scale, double aspectRatio, ButtonType t);

	bool intersect(double mouseX, double mouseY);

	void setClickFunction(ButtonType t);

	ButtonType getType() { return type;	};
	glm::vec4 getPos() const;

private:
	double xPos, yPos;
	double xScale, yScale;

	ButtonType type;
};