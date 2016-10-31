#pragma once

//Global Includes
#define GLEW_STATIC
#include "glew.h"
#include <vector>

//Local Includes
#include "Texture.h"
#include "Camera.h"


class Model
{

public:
	Model();
	~Model();

	void Initialise(ModelType Load, FragmentType Fill, GLuint Shader, std::string _strTexture, std::vector<GLfloat> Vertices, std::vector<GLuint> Elements, Camera* Camera);
	void Render();
	void Update(glm::vec3 Position, float Rotation);

private:

	ModelType LoadType;
	FragmentType FillType;

	GLuint VBO, VAO, EBO, ShaderProgram;

	std::vector<GLfloat> m_Vertices;
	std::vector<GLuint> m_Elements;

	Texture ModelTex;

	Camera* m_Camera;
	int screenWidth, screenHeight;
};

