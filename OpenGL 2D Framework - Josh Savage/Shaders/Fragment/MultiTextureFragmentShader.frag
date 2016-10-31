#version 330 core

in vec3 OutColor; //Taking the color and texture coords we stored in the vertex array from the vertex shader
in vec2 TexCoord;

out vec4 color; //Outputting color to the next stage (required output)

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

void main()
{
    color = mix(texture(ourTexture1, TexCoord), texture(ourTexture2, TexCoord), 0.2);
}