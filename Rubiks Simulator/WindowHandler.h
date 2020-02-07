#pragma once

#define GLEW_STATIC
#include <GL/glew.h>	// GLEW must be included before any opengl headers

#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>

#include <glm/glm.hpp>

class WindowHandler
{
public:
	sf::Window window;

	WindowHandler();
	~WindowHandler();

	int glInit();
	void glLoop();

	void generateColorData();

private:
	GLuint vbo, colorBuffer;	// Vertex and color buffers
	GLuint shaderProgram;		// Shader program created by createShaderProgram()
	GLuint matrixUniform;		// Uniform variable equal to projectionMatrix * cameraMatrix

	void generateVertexData();
	int createShaderProgram(std::string &vertexPath, std::string &fragmentPath);
};
