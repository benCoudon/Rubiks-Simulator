#include <iostream>

#include "Algorithm.h"
#include "Move.h"

#include "WindowHandler.h"

#include "AlgorithmList.h"

int main()
{
	//Create the window and set some settings
	WindowHandler wh;
	wh.addButton(Button(-.8, .8, .1, 4.0 / 3.0, RESET));
	wh.addButton(Button(.7, .8, .1, 4.0 / 3.0, SCRAMBLE));
	wh.addButton(Button(-.8, -.8, .1, 4.0 / 3.0, SOLVE));

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
				wh.checkButtons((float)event.mouseButton.x, (float)event.mouseButton.y);
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
