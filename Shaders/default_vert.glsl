#version 330 core

layout (location = 0) in vec3 pos;

uniform mat4 model;
uniform mat4 projection;

void main() {
    gl_Position = model * projection * vec4(0.4 * pos.x, 0.4 * pos.y, pos.z, 1.0);
}