#ifndef WINDOW_HANDLER_H
#define WINDOW_HANDLER_H

#include <vector>

#define GLEW_STATIC
#include <GL/glew.h>	// GLEW must be included before any opengl headers

#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>

#include <glm/glm.hpp>

#include "Button.h"
#include "Cube.h"

class WindowHandler
{
public:
	WindowHandler();
	WindowHandler(Cube c);
	~WindowHandler();

	int glInit();
	void glLoop();

	void addButton(Button b);
	void clearButtons();
	void checkButtons(float x, float y);

	void generateColorData();

	sf::Window window;

	Cube rubik;

private:
	GLuint vboCube, colorBuffer;	// Vertex and color buffers
	GLuint shaderProgramCube, shaderProgramButton;		// Shader program created by createShaderProgram()
	GLuint matrixUniform;		// Uniform variable equal to projectionMatrix * cameraMatrix

	GLuint vboButtons;

	std::vector<Button> bList;

	void generateCubeVertexData();
	void generateButtonVertexData();

	int createShaderProgram(std::string &vertexPath, std::string &fragmentPath);
};

#endif
