#include "Button.h"

Button::Button(double x, double y, double scale, double aspectRatio, ButtonType t)
{
	xPos = x;
	yPos = y;
	xScale = scale;
	yScale = scale * aspectRatio;
	type = t;
}

bool Button::intersect(double mouseX, double mouseY)
{
	if (mouseX < xPos || mouseX > xPos + xScale)
		return false;
	if (mouseY < yPos || mouseY > yPos + yScale)
		return false;

	return true;
}

void Button::setClickFunction(ButtonType t)
{
	type = t;
}

glm::vec4 Button::getPos() const
{
	return glm::vec4(xPos, yPos, xScale, yScale);
}
