#pragma once
#include "GameAgent.h"

enum BirdState {

	Nothing,
	Clicked,
	Launching,
	Launched
};

class Shootable :
	protected GameAgent
{

public:
	Shootable(GLuint Shader, std::string _strTexture, std::vector<GLfloat> Vertices, std::vector<GLuint> Elements, glm::vec3 Position, float Rotation, Camera * Camera, b2Body* Physics, int Type);
	~Shootable();

	int Update();
	void Render();

	b2Body* GetPhysics();

	int GetType();

private:

	BirdState Current;
	float Alive;
};

