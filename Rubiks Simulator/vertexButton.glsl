#version 330

layout (location = 2) in vec2 position;

void main()
{
	gl_Position = vec4(position, 0.0, 1.0);
}
