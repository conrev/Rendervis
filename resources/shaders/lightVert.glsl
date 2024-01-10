#version 330

layout (location = 0) in vec3 position;

uniform mat4 transformMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;


void main() {
    gl_Position =  projectionMatrix * viewMatrix * transformMatrix * vec4(position.x, position.y, position.z , 1.0);
}
