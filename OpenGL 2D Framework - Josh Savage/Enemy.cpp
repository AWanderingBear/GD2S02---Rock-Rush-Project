#include "Enemy.h"



Enemy::Enemy(GLuint Shader, std::string _strTexture, std::vector<GLfloat> Vertices, std::vector<GLuint> Elements, glm::vec3 Position, float Rotation, Camera * Camera, b2Body* Physics): GameAgent(Shader, _strTexture, Vertices, Elements, Position, Rotation, Camera, Physics, 3)
{
	Alive = true;
}

Enemy::~Enemy()
{
}

bool Enemy::Update()
{
	GameAgent::Update();
	return Alive;
}

void Enemy::Render()
{
	GameAgent::Render();
}

b2Body * Enemy::GetPhysics()
{
	return GameAgent::GetPhysics();
}

int Enemy::GetType()
{
	return GameAgent::GetType();
}

void Enemy::Kill()
{

	Alive = false;
}
