#version 330

in vec3 colorPass;

out vec4 color;

void main()
{
	color = vec4(colorPass, 1.0);
}
