#pragma once
#include <string>
#define GLEW_STATIC
#include <glew.h>

class Texture
{
public:
	Texture();
	~Texture();

	void Initialise(std::string TexName);

	GLuint GetTexture();

private:

	unsigned char* _pImageData;
	GLuint texture;
	int _iWidth, _iHeight;
};

