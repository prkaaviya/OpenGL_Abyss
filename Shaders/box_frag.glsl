#version 330 core

in vec2 TexCoord;         // Interpolated texture coordinates
out vec4 FragColor;       // Final fragment color

uniform sampler2D textureSampler; // Texture uniform

void main()
{
    FragColor = texture(textureSampler, TexCoord); // Sample the texture
}