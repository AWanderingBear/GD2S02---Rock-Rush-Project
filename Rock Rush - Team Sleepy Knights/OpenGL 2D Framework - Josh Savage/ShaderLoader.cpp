#include "ShaderLoader.h"
#include <fstream>
#include <vector>
#include <iostream>

ShaderLoader::ShaderLoader()
{
}

ShaderLoader::~ShaderLoader()
{
}

GLuint ShaderLoader::CreateShader(char* VertexShaderName, char* FragmentShaderName)
{

	int _iCompileResult;

	//Start By Reading the Shaders
	std::string _strVertexSource = ReadShaderFile(VertexShaderName);
	std::string _strFragmentSource = ReadShaderFile(FragmentShaderName);

	//Conversions to a pointer to be used and the size of the data behind the pointer
	const char* _cpVertexSource = _strVertexSource.c_str();
	const int _iVertexSourceSize = _strVertexSource.size();

	const char* _cpFragmentSource = _strFragmentSource.c_str();
	const int _iFragmentSourceSize = _strFragmentSource.size();

	//Now process the shaders

	//********
	// Vertex
	//********
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &_cpVertexSource, &_iVertexSourceSize);
	glCompileShader(vertexShader);

	//Error handling
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &_iCompileResult);

	if (_iCompileResult == GL_FALSE) {

		int _iInfoLogSize = 0;
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &_iInfoLogSize); //Get Error log size
		std::vector<char> _cShaderLog(_iInfoLogSize); // Initialise vector to be the size of the error log

		glGetShaderInfoLog(vertexShader, _iInfoLogSize, NULL, &_cShaderLog[0]); //Get the info from the error log
		std::cout << "Error compiling" << VertexShaderName << ", a vertex shader." << std::endl << "Log as follows : " <<  std::endl << &_cShaderLog[0] << std::endl;
		return -1;
	}

	//**********
	// Fragment
	//**********
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &_cpFragmentSource, &_iFragmentSourceSize);
	glCompileShader(fragmentShader);

	//Error handling
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &_iCompileResult);

	if (_iCompileResult == GL_FALSE) {

		int _iInfoLogSize = 0;
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &_iInfoLogSize); //Get Error log size
		std::vector<char> _cShaderLog(_iInfoLogSize); // Initialise vector to be the size of the error log

		glGetShaderInfoLog(fragmentShader, _iInfoLogSize, NULL, &_cShaderLog[0]); //Get the info from the error log
		std::cout << "Error compiling" << FragmentShaderName << ", a fragment shader." << std::endl << "Log as follows: " << std::endl << &_cShaderLog[0] << std::endl;
		return -1;
	}

	//*********************
	// SHADER PROGRAM TIME
	//*********************

	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	//Error handling
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &_iCompileResult);

	if (_iCompileResult == GL_FALSE) {

		int _iInfoLogSize = 0;
		glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &_iInfoLogSize); //Get Error log size
		std::vector<char> _cProgramLog(_iInfoLogSize); // Initialise vector to be the size of the error log

		glGetShaderInfoLog(fragmentShader, _iInfoLogSize, NULL, &_cProgramLog[0]); //Get the info from the error log
		std::cout << "Error compiling Shader Program comprising:" << VertexShaderName << " & " << FragmentShaderName << std::endl;
		std::cout << "Error Log is as follows:" << std::endl << &_cProgramLog[0] << std::endl;

		return -1;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}

std::string ShaderLoader::ReadShaderFile(char * filename)
{
	std::string ShaderContent;
	std::ifstream file(filename, std::ios::in);

	if (!file.good()) {

		std::cout << "Cannot Read " << filename << ", during shader compilation" << std::endl;
		std::terminate();
	}

	file.seekg(0, std::ios::end);
	ShaderContent.resize((unsigned int)file.tellg());
	file.seekg(0, std::ios::beg);
	file.read(&ShaderContent[0], ShaderContent.size());
	file.close();
	return ShaderContent;
}
