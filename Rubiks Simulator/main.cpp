#include <iostream>

#include "Algorithm.h"
#include "Move.h"

#include "WindowHandler.h"

int main()
{
	//Create the window and set some settings
	Cube c;
	WindowHandler wh(c);

	//Main program loop
	bool running = true;
	while (running)
	{
		//Event handling
		sf::Event event;
		while (wh.window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				running = false;

			if (event.type == sf::Event::MouseButtonReleased)
			{
				wh.rubik.setAlg(Algorithm("D"));
				wh.rubik.stepAlg();
				wh.generateColorData();
			}
		}

		//OpenGL calls
		wh.glLoop();
	}

	//Cleanup program
	wh.window.close();

	return 0;
}
