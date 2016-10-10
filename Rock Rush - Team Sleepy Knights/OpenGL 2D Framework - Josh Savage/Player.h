#pragma once
#include "GameAgent.h"
class Player :
	 protected GameAgent
{
public:
	Player(GLuint Shader, std::string _strTexture, std::vector<GLfloat> Vertices, std::vector<GLuint> Elements, glm::vec3 Position, float Rotation, Camera * Camera, b2Body* Physics);
	~Player();

	bool Update(float deltaTime);
	void Render();
	b2Body* GetPhysics();
	int GetType();
	void Player::SetSpeed(float playerSpeed);
	void Move(int key);

	void SetCurrentlyTouching(GameAgent* object);
	GameAgent* GetCurrentlyTouching();
	void SetCurrentlyHolding(GameAgent* object);
	GameAgent* GetCurrentlyHolding();

	void Kill();

private:
	float m_Speed;

	GLfloat DeltaTime = 0.0f;	// Time between current frame and last frame
	GLfloat lastFrame = 0.0f;  	// Time of last frame

	GameAgent* currentlyTouching = nullptr;		//The GameAgent that the player is currently touching.
	GameAgent* currentlyHolding = nullptr;		//Need a second variable because my logic was faulty with when things are being touched when held.
	//bool isHolding;						//Whether the player is currently holding a meteor	

	bool Alive;
	float DeathCounter = 0;
	float DeathTime;

	int PlayerCode;

	int RemainingJumps = 6;
};

