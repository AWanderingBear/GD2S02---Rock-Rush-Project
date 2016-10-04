#version 330 core

out vec4 color;

in vec3 OutColor;

void main()
{
    color = vec4(OutColor, 1.0f);
} 