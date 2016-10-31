#pragma once 
#define GLEW_STATIC
#include <glew.h>
#include <string>

class ShaderLoader
{
public:
	ShaderLoader();
	~ShaderLoader();

	GLuint CreateShader(char * VertexShaderName, char * FragmentShaderName);

private:
	std::string ReadShaderFile(char *filename);

private:
	
	GLuint vertexShader;
	GLuint fragmentShader;

	GLuint shaderProgram;
};

