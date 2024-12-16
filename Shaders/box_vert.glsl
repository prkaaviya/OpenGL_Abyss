#version 330 core

layout(location = 0) in vec3 aPos;       // Vertex position
layout(location = 1) in vec2 aTexCoord;  // Texture coordinate

out vec2 TexCoord;  // Pass texture coordinates to fragment shader

uniform mat4 model;       // Model transformation matrix
uniform mat4 view;        // View transformation matrix
uniform mat4 projection;  // Projection transformation matrix

void main()
{
    TexCoord = aTexCoord;  // Pass texture coordinates
    gl_Position = projection * view * model * vec4(aPos, 1.0); // Transform vertex position
}