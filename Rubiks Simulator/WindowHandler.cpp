#include "WindowHandler.h"

#include <fstream>
#include <sstream>
#include <vector>

#include "glm/gtc/matrix_transform.hpp"

void addQuad(std::vector<glm::vec3> &buffer, double x, double y, double z, double dx, double dy, double dz);

WindowHandler::WindowHandler()
{
	glInit();
}

WindowHandler::~WindowHandler()
{
	window.close();
}

int WindowHandler::glInit()
{
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 0;
	settings.majorVersion = 3;
	settings.minorVersion = 3;

	window.create(sf::VideoMode(800, 600), "Rubik's Cube", sf::Style::Close, settings);
	window.setVerticalSyncEnabled(true);

	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		printf("GLEW Error: %s\n", glewGetErrorString(error));
		return 1;
	}

	glClearColor(0.2f, 0.2f, 0.2f, 0.2f);

	std::string vertexPath = "vertex.glsl";
	std::string fragmentPath = "fragment.glsl";
	createShaderProgram(vertexPath, fragmentPath);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// Fill vbo with vertex data
	glGenBuffers(1, &vbo);
	generateVertexData();

	// Fill colorBuffer with color data
	glGenBuffers(1, &colorBuffer);
	generateColorData();

	glm::mat4 projectionMat = glm::perspective(glm::radians(75.0), 4.0 / 3.0, 0.1, 100.0);
	glm::mat4 cameraMat = glm::lookAt(glm::vec3(1.5, 1.5, 1.5), glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.0, 1.0, 0.0));
	glm::mat4 viewMat = projectionMat * cameraMat;

	matrixUniform = glGetUniformLocation(shaderProgram, "viewMat");
	glUniformMatrix4fv(matrixUniform, 1, GL_FALSE, &viewMat[0][0]);

	return 0;
}

void WindowHandler::glLoop()
{
	window.setActive(true);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Enable vbo
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Enable colorBuffer
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, (2 * 3 * 3 * 6 * 6));

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(0);

	window.display();
	window.setActive(false);
}

void WindowHandler::generateColorData()
{
	std::vector<glm::vec3> colorData;

	for (int i = 0; i < (3 * 3 * 6 * 6); i++)	// Fills in black for all cube data
	{
		colorData.push_back(glm::vec3(0.0, 0.0, 0.0));
	}

	for (int i = 0; i < (3 * 3 * 6 * 6); i++)	// Fills all white for cube pieces
	{
		colorData.push_back(glm::vec3(1.0, 1.0, 1.0));
	}

	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, colorData.size() * sizeof(glm::vec3), &colorData.front(), GL_STATIC_COPY);
}

void WindowHandler::generateVertexData()
{
	std::vector<glm::vec3> cube;

	double dVertex = 1.0 / 3.0;

	// Current algorithm creates 2592 bytes (4*9*6*12)
	for (double i = 0.0; i < 1.0; i += 1.0 / 3.0)		// Optimize this to use indicies later
	{
		for (double o = 0.0; o < 1.0; o += 1.0 / 3.0)
		{
			addQuad(cube, i, o, 0.0, dVertex, dVertex, 0.0);	// XY
			addQuad(cube, i, o, 1.0, dVertex, dVertex, 0.0);

			addQuad(cube, i, 0.0, o, dVertex, 0.0, dVertex);	// XZ
			addQuad(cube, i, 1.0, o, dVertex, 0.0, dVertex);

			addQuad(cube, 0.0, i, o, 0.0, dVertex, dVertex);	// YZ
			addQuad(cube, 1.0, i, o, 0.0, dVertex, dVertex);
		}
	}

	dVertex = 1.0 / 9.0;

	for (double i = 1.0 / 9.0; i < 1.0; i += 1.0 / 3.0)		// Optimize this to use indicies later
	{
		for (double o = 1.0 / 9.0; o < 1.0; o += 1.0 / 3.0)
		{
			addQuad(cube, i, o, -0.01, dVertex, dVertex, 0.0);	// XY
			addQuad(cube, i, o, 1.01, dVertex, dVertex, 0.0);

			addQuad(cube, i, -0.01, o, dVertex, 0.0, dVertex);	// XZ
			addQuad(cube, i, 1.01, o, dVertex, 0.0, dVertex);

			addQuad(cube, -0.01, i, o, 0.0, dVertex, dVertex);	// YZ
			addQuad(cube, 1.01, i, o, 0.0, dVertex, dVertex);
		}
	}

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, cube.size() * sizeof(glm::vec3), &cube.front(), GL_STATIC_COPY);
}

int WindowHandler::createShaderProgram(std::string &vertexPath, std::string &fragmentPath)
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

	file.open(fragmentPath);	// Import the shader code from the given file
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

	success = NULL;	// Error checking on the fragment shader
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[1024];
		glGetShaderInfoLog(fragmentShader, sizeof(infoLog), NULL, infoLog);
		printf("Error compiling fragmentShader: %s\n", infoLog);
		return 2;
	}

	shaderProgram = glCreateProgram();	// Bind the 2 shader objects to the shader program
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

void addQuad(std::vector<glm::vec3> &buffer, double x, double y, double z, double dx, double dy, double dz)
{
	buffer.push_back(glm::vec3(x, y, z));
	buffer.push_back(glm::vec3(x + dx, y, z + dz));
	buffer.push_back(glm::vec3(x, y + dy, z + dz));

	buffer.push_back(glm::vec3(x + dx, y + dy, z + dz));
	buffer.push_back(glm::vec3(x, y + dy, z));
	buffer.push_back(glm::vec3(x + dx, y, z));
}