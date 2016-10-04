#pragma once
#include "GameAgent.h"
class Player :
	 protected GameAgent

{
public:
	Player(GLuint Shader, std::string _strTexture, std::vector<GLfloat> Vertices, std::vector<GLuint> Elements, glm::vec3 Position, float Rotation, Camera * Camera, b2Body* Physics);
	~Player();

	bool Update();
	void Render();
	b2Body* GetPhysics();
	int GetType();
	void Player::SetSpeed(float playerSpeed);
	void Move(int key);

private:

	float m_Speed;

	GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
	GLfloat lastFrame = 0.0f;  	// Time of last frame
};

