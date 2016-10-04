#pragma once
#include "GameAgent.h"
class Enemy :
	protected GameAgent
	
{
public:
	Enemy(GLuint Shader, std::string _strTexture, std::vector<GLfloat> Vertices, std::vector<GLuint> Elements, glm::vec3 Position, float Rotation, Camera * Camera, b2Body* Physics);
	~Enemy();

	bool Update();
	void Render();
	b2Body* GetPhysics();
	int GetType();
	void Kill();

private:

	bool Alive;
};
