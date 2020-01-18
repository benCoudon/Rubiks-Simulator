#include <iostream>

#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>

#include "Move.h"

int main()
{
	//Create the window and set some settings
	sf::Window window; 
	window.create(sf::VideoMode(800, 600), "Rubik's Cube");
	window.setVerticalSyncEnabled(true);

	//Main program loop
	bool running = true;
	while (running)
	{
		//Event handling
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				running = false;
		}

		//Do the cube logic

		//OpenGL calls
		window.setActive(true);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		window.display();
		window.setActive(false);
	}

	//Cleanup program
	window.close();

	return 0;
}
