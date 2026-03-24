#version 330 core

in vec4 VertColor;
in vec2 UV;

out vec4 FragColor;

void main()
{
	FragColor = VertColor;
}