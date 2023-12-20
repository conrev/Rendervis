#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 uv;

out vec4 vertColor;
out vec2 vertUV;


void main() {
    gl_Position = vec4(position.x, position.y, position.z , 1.0);
    vertColor = vec4(color, 1.0);
    vertUV = uv;
}
