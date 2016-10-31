#include "Texture.h"
#include "SOIL.h"
#include <iostream>

Texture::Texture(){


}

Texture::~Texture()
{
}

void Texture::Initialise(std::string TexName)
{

	//Use SOIL to load the image data
	_pImageData = SOIL_load_image(TexName.c_str(), &_iWidth, &_iHeight, 0, SOIL_LOAD_RGB);

	if (_pImageData == nullptr) {

		std::cout << "Error during texture loading for: " << TexName << std::endl;
	}

	//Make and bind the texture object
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	//Pass the ImageData to the Texture object
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _iWidth, _iHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, _pImageData);
	// (Texture Target, Mipmap Level, Storage Format, Width, Height, Always 0, Format of the Image, Data type of the image, Image Data to be used)
	glGenerateMipmap(GL_TEXTURE_2D);

	//Texturing Filters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//Cleaning up
	SOIL_free_image_data(_pImageData);
	glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint Texture::GetTexture()
{

	return texture;
}
