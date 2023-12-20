#version 330

in vec4 vertColor;
in vec2 vertUV;
out vec4 FragColor;


uniform sampler2D textureData;

void main()
{
    FragColor = texture2D(textureData, vertUV);

}
