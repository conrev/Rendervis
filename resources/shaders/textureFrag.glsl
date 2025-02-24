#version 330

in vec4 vertColor;
in vec2 vertUV;
in vec3 worldPos;
in vec3 worldNormal;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

uniform vec3 lightColor;
uniform vec3 viewPosition;
uniform vec3 lightPosition;
uniform Material material;

out vec4 FragColor;

void main() {
    FragColor =  texture2D(material.diffuse, vertUV);
}