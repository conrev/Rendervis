#version 330

in vec4 vertColor;
out vec4 FragColor;

uniform vec4 cycledColor;

void main()
{
    FragColor = cycledColor;
}
