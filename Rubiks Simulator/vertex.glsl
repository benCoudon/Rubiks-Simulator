#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 colorIn;

out vec3 colorPass;

uniform mat4 viewMat;

void main()
{
	colorPass = colorIn;
	gl_Position = viewMat * vec4(position, 1.0);
}
