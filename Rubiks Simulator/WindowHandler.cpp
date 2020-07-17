#include "WindowHandler.h"

#include <fstream>
#include <sstream>
#include <vector>

#include "glm/gtc/matrix_transform.hpp"

#include "OldPochmann.h"

void addQuad(std::vector<glm::vec3> &buffer, double x, double y, double z, double dx, double dy, double dz);
void addQuad(std::vector<glm::vec2> &buffer, glm::vec4 posScale);
void addColor(std::vector<glm::vec3> &buffer, glm::vec3 color);

WindowHandler::WindowHandler()
{
	glInit();
}

WindowHandler::WindowHandler(Cube c)
{
	rubik = c;
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

	std::string vertexPathCube = "vertexCube.glsl";
	std::string fragmentPathCube = "fragmentCube.glsl";
	shaderProgramCube = createShaderProgram(vertexPathCube, fragmentPathCube);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// Fill vbo with vertex data
	glGenBuffers(1, &vboCube);
	generateCubeVertexData();

	// Fill colorBuffer with color data
	glGenBuffers(1, &colorBuffer);
	generateColorData();

	glm::mat4 projectionMat = glm::perspective(glm::radians(80.0), 4.0 / 3.0, 0.1, 100.0);
	//glm::mat4 projectionMat = glm::ortho(-1.0, 1.0, -1.0, 1.0, 0.1, 100.0);	// Orthographic projection
	glm::mat4 cameraMat = glm::lookAt(glm::vec3(1.25, 1.5, 1.5), glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.0, 1.0, 0.0));
	glm::mat4 viewMat = projectionMat * cameraMat;

	matrixUniform = glGetUniformLocation(shaderProgramCube, "viewMat");
	glUniformMatrix4fv(matrixUniform, 1, GL_FALSE, &viewMat[0][0]);

	std::string vertexPathButton = "vertexButton.glsl";
	std::string fragmentPathButton = "fragmentButton.glsl";
	shaderProgramButton = createShaderProgram(vertexPathButton, fragmentPathButton);

	glGenBuffers(1, &vboButtons);
	generateButtonVertexData();

	return 0;
}

void WindowHandler::glLoop()
{
	window.setActive(true);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glUseProgram(shaderProgramCube);

	// Enable vbo for the cube
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vboCube);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Enable colorBuffer
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Draw Cube
	glDrawArrays(GL_TRIANGLES, 0, (6 * 2 * 3 * 3 * 6));

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	
	if (bList.size() > 0)
	{
		glUseProgram(shaderProgramButton);

		// Enable vbo for the buttons
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, vboButtons);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);

		// Draw Buttons
		glDisable(GL_DEPTH_TEST);
		glDrawArrays(GL_TRIANGLES, 0, 6 * bList.size());
		glEnable(GL_DEPTH_TEST);

		glDisableVertexAttribArray(2);
	}

	window.display();
}

void WindowHandler::addButton(Button b)
{
	bList.push_back(b);
	generateButtonVertexData();
}

void WindowHandler::clearButtons()
{
	bList.clear();
	generateButtonVertexData();
}

void WindowHandler::checkButtons(float x, float y)
{
	x /= 800.0;
	x *= 2.0;
	x -= 1.0;

	y /= -600.0;
	y *= 2.0;
	y += 1.0;

	for (unsigned i = 0; i < bList.size(); i++)
	{
		if (bList[i].intersect(x, y))
		{
			switch (bList[i].getType())
			{
			case RESET:
				rubik.resetCube();
				generateColorData();
				break;

			case SCRAMBLE:
				rubik.scrambleCube();
				generateColorData();
				break;

			case SOLVE:
				std::vector<Algorithm> algSet = createSolutionOldPochmann(rubik);
				for (int i = 0; i < algSet.size(); i++)
				{
					rubik.setAlg(algSet[i]);
					rubik.executeAlg();
				}
				break;
			}
		}
	}
}

void WindowHandler::generateColorData()
{
	std::vector<glm::vec3> colorData;

	for (int i = 0; i < (3 * 3 * 6 * 6); i++)	// Fills in black for all cube data
	{
		colorData.push_back(glm::vec3(0.0, 0.0, 0.0));
	}

	// Center color data
	for (int i = 0; i < 6; i++)
	{
		addColor(colorData, cubeColorArr[rubik.getCenter((CubeFace)i)]);
	}

	// Edges
	for (int i = 0; i < 4; i++)
	{
		for (int o = 0; o < 6; o++)
		{
			int edgeOffset = -1;
			switch (o)
			{
			case 0:
				edgeOffset = i < 2 ? 3 - i : i - 2;
				break;
			case 1:
				edgeOffset = i < 2 ? 2 - i : 3 * (3 - i);
				break;
			case 2:
				edgeOffset = i < 2 ? i : 5 - i;
				break;
			case 3:
				edgeOffset = i < 2 ? 1 - i : i;
				break;
			case 4:
				edgeOffset = i < 2 ? 3 * i : i - 1;
				break;
			case 5:
				edgeOffset = i < 2 ? i + 2 : 3 - i;
				break;
			}

			addColor(colorData, cubeColorArr[rubik.getEdge((CubeFace)o, edgeOffset).p]);
		}
	}

	for (int i = 0; i < 4; i++)
	{
		for (int o = 0; o < 6; o++)
		{
			int cornerOffset = -1;
			switch (o)
			{
			case 0:
				cornerOffset = i < 2 ? i + 2 : 3 - i;
				break;
			case 1:
				cornerOffset = i < 2 ? i + 1 : 3 * (i - 2);
				break;
			case 2:
				cornerOffset = i < 2 ? 3 * i : i - 1;
				break;
			case 3:
				cornerOffset = i < 2 ? 1 - i : i;
				break;
			case 4:
				cornerOffset = i < 2 ? 3 * i : i - 1;
				break;
			case 5:
				cornerOffset = i < 2 ? i + 2 : 3 - i;
				break;
			}

			//addColor(colorData, glm::vec3(0.0, 0.0, i * 6.0 / 18.0));

			addColor(colorData, cubeColorArr[rubik.getCorner((CubeFace)o, cornerOffset).p]);
		}
	}

	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, colorData.size() * sizeof(glm::vec3), &colorData.front(), GL_DYNAMIC_COPY);
}

void WindowHandler::generateCubeVertexData()
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

	dVertex = 1.0 / 9.0;	// Spots on the cube are 1/9 wide

	// Centers
	addQuad(cube, 4.0 / 9.0, 1.01, 4.0 / 9.0, dVertex, 0.0, dVertex);
	addQuad(cube, 4.0 / 9.0, 4.0 / 9.0, 1.01, dVertex, dVertex, 0.0);
	addQuad(cube, 1.01, 4.0 / 9.0, 4.0 / 9.0, 0.0, dVertex, dVertex);
	addQuad(cube, 4.0 / 9.0, -0.01, 4.0 / 9.0, dVertex, 0.0, dVertex);
	addQuad(cube, 4.0 / 9.0, 4.0 / 9.0, -0.01, dVertex, dVertex, 0.0);
	addQuad(cube, -0.01, 4.0 / 9.0, 4.0 / 9.0, 0.0, dVertex, dVertex);

	// Edges
	for (double i = 1.0 / 9.0; i < 1.0; i += 1.0 / 3.0)
	{
		for (double o = 1.0 / 9.0; o < 1.0; o += 1.0 / 3.0)
		{
			if ((int)(i * 9.0 + o * 9.0) != 5 && (int)(i * 9.0 + o * 9.0) != 11)	// Skip corners and centers
				continue;

			// Adds in the order of the cube faces and colors
			addQuad(cube, i, 1.01, o, dVertex, 0.0, dVertex);
			addQuad(cube, i, o, 1.01, dVertex, dVertex, 0.0);
			addQuad(cube, 1.01, i, o, 0.0, dVertex, dVertex);
			addQuad(cube, i, -0.01, o, dVertex, 0.0, dVertex);
			addQuad(cube, i, o, -0.01, dVertex, dVertex, 0.0);
			addQuad(cube, -0.01, i, o, 0.0, dVertex, dVertex);
		}
	}

	// Corners
	for (double i = 1.0 / 9.0; i < 1.0; i += 2.0 / 3.0)	
	{
		for (double o = 1.0 / 9.0; o < 1.0; o += 2.0 / 3.0)
		{
			// Adds in the order of the cube faces and colors
			addQuad(cube, i, 1.01, o, dVertex, 0.0, dVertex);
			addQuad(cube, i, o, 1.01, dVertex, dVertex, 0.0);
			addQuad(cube, 1.01, i, o, 0.0, dVertex, dVertex);
			addQuad(cube, i, -0.01, o, dVertex, 0.0, dVertex);
			addQuad(cube, i, o, -0.01, dVertex, dVertex, 0.0);
			addQuad(cube, -0.01, i, o, 0.0, dVertex, dVertex);
		}
	}

	glBindBuffer(GL_ARRAY_BUFFER, vboCube);
	glBufferData(GL_ARRAY_BUFFER, cube.size() * sizeof(glm::vec3), &cube.front(), GL_STATIC_COPY);
}

void WindowHandler::generateButtonVertexData()
{
	if (bList.size() == 0)
		return;

	std::vector<glm::vec2> buttonData;

	for (unsigned i = 0; i < bList.size(); i++)
	{
		addQuad(buttonData, bList[i].getPos());
	}

	glBindBuffer(GL_ARRAY_BUFFER, vboButtons);
	glBufferData(GL_ARRAY_BUFFER, buttonData.size() * sizeof(glm::vec2), &buttonData.front(), GL_STATIC_COPY);
}

int WindowHandler::createShaderProgram(std::string &vertexPath, std::string &fragmentPath)
{
	GLuint shaderProgram;

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

	return shaderProgram;
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

void addQuad(std::vector<glm::vec2> &buffer, glm::vec4 posScale)	// Z and W elements are used as the xScale and yScale respectively
{
	buffer.push_back(glm::vec2(posScale.x, posScale.y));
	buffer.push_back(glm::vec2(posScale.x + posScale.z, posScale.y));
	buffer.push_back(glm::vec2(posScale.x, posScale.y + posScale.w));

	buffer.push_back(glm::vec2(posScale.x + posScale.z, posScale.y));
	buffer.push_back(glm::vec2(posScale.x, posScale.y + posScale.w));
	buffer.push_back(glm::vec2(posScale.x + posScale.z, posScale.y + posScale.w));
}

void addColor(std::vector<glm::vec3> &buffer, glm::vec3 color)
{
	for (int i = 0; i < 6; i++)
	{
		buffer.push_back(color);
	}
}