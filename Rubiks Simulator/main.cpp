#include <iostream>
#include <fstream>
#include <sstream>

#define GLEW_STATIC
#include <GL/glew.h>

#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>

#include <glm/glm.hpp>

#include "Move.h"
#include "Algorithm.h"

glm::vec3 cube[] =
{
	glm::vec3(0.0, 0.0, 0.0),
	glm::vec3(1.0, 0.0, 0.0),
	glm::vec3(1.0, 1.0, 0.0),

	glm::vec3(0.0, 0.0, 0.0),
	glm::vec3(0.0, 1.0, 0.0),
	glm::vec3(1.0, 1.0, 0.0)
};

int createShaderProgram(std::string &vertexPath, std::string &fragmentPath)
{
	std::ifstream file(vertexPath);	// Import the shader code from the given file
	if (!file.is_open())
	{
		printf("Error opening vertex shader source at %s\n", vertexPath.c_str());
		return 1;
	}
	std::stringstream buf;	// Use a stringstream as a buffer for the entire file
	buf << file.rdbuf();
	std::string vertexTmp = buf.str();

	buf = std::stringstream();	// Clear the ifstream and stringstream
	file.close();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const char* vertexCStr = vertexTmp.c_str();
	glShaderSource(vertexShader, 1, &vertexCStr, NULL);	// Bind the shader source to the shader object
	glCompileShader(vertexShader);

	GLint success;	// Error checking on the vertex shader
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[1024];
		glGetShaderInfoLog(vertexShader, sizeof(infoLog), NULL, infoLog);
		printf("Error compiling vertexShader: %s\n", infoLog);
		return 2;
	}
	
	std::ifstream file(fragmentPath);	// Import the shader code from the given file
	if (!file.is_open())
	{
		printf("Error opening fragment shader source at %s\n", fragmentPath.c_str());
		return 1;
	}
	buf << file.rdbuf();	// Use a stringstream as a buffer for the entire file
	std::string fragmentTmp = buf.str();

	file.close();	// Close the file again

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char* fragmentCStr = fragmentTmp.c_str();
	glShaderSource(fragmentShader, 1, &fragmentCStr, NULL);	// Bind the shader source to the shader object
	glCompileShader(fragmentShader);

	GLint success;	// Error checking on the fragment shader
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[1024];
		glGetShaderInfoLog(fragmentShader, sizeof(infoLog), NULL, infoLog);
		printf("Error compiling fragmentShader: %s\n", infoLog);
		return 2;
	}

	GLuint shaderProgram = glCreateProgram();	// Bind the 2 shader objects to the shader program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	GLchar errorLog[1024];	// Check for errors with the shader program
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (success == 0) {
		glGetProgramInfoLog(shaderProgram, sizeof(errorLog), NULL, errorLog);
		printf("Error linking shader program: %s\n", errorLog);
		return 3;
	}

	glValidateProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, sizeof(errorLog), NULL, errorLog);
		printf("Shader program error: %s\n", errorLog);
		return 3;
	}

	glUseProgram(shaderProgram);

	return 0;
}

int glInit(sf::Window &window, GLuint &vbo)
{
	window.create(sf::VideoMode(800, 600), "Rubik's Cube");
	window.setVerticalSyncEnabled(true);

	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		printf("GLEW Error: %s\n", glewGetErrorString(error));
		return 1;
	}

	glClearColor(0.2f, 0.2f, 0.2f, 0.2f);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);

	return 0;
}

void glLoop(sf::Window &window, GLuint &vbo)
{
	window.setActive(true);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);

	window.display();
	window.setActive(false);
}

int main()
{
	//Create the window and set some settings
	sf::Window window;
	GLuint vbo;
	glInit(window, vbo);

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
		glLoop(window, vbo);
	}

	//Cleanup program
	window.close();

	return 0;
}
