#version 330 core
  
layout (location = 0) in vec3 position; //Important to Vertex Shader as it is the positions
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord; // {The vertex shader only reads them out then passes them on

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{

    gl_Position = projection * view * model * vec4(position, 1.0f); // Setting vertex position
	TexCoord = vec2(texCoord.x, 1.0 - texCoord.y);
}