#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

out vec4 vertColor;
out vec2 vertUV;
out vec3 worldNormal;
out vec3 worldPos;

uniform mat4 transformMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;


void main() {
    gl_Position =  projectionMatrix* viewMatrix * transformMatrix * vec4(position.x, position.y, position.z , 1.0);
    vertColor = vec4(color, 1.0);
    vertUV = uv;
    worldPos = vec3(transformMatrix * vec4(position,1.0));
    worldNormal = mat3(transpose(inverse(transformMatrix))) * normal;
}
