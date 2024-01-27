#version 330

in vec4 vertColor;
in vec2 vertUV;
in vec3 worldPos;
in vec3 worldNormal;

out vec4 FragColor;

uniform vec3 lightColor;
uniform vec3 viewPosition;
uniform vec3 lightPosition;
uniform sampler2D textureData;

void main()
{
    vec4 objectColor = texture2D(textureData, vertUV);
    
    FragColor = objectColor;

}
