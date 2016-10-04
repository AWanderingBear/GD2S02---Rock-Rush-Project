#include "Player.h"

Player::Player(GLuint Shader, std::string _strTexture, std::vector<GLfloat> Vertices, std::vector<GLuint> Elements, glm::vec3 Position, float Rotation, Camera * Camera, b2Body* Physics)
	: GameAgent(Shader, _strTexture, Vertices, Elements, Position, Rotation, Camera, Physics, 3)
{

	SetSpeed(600.0f);
		
	//Position = glm::vec3(0.0f, 0.0f, 0.0f);
}

Player::~Player()
{

}

bool Player::Update()
{
	//Time normalization
	GLfloat currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	//if (possible bug)
	//{
	//	return false
	//}

	GameAgent::Update(); // Code breaks here in Debug Mode.

	return true;
}

void Player::Render()
{
	GameAgent::Render();
}

b2Body * Player::GetPhysics()
{
	return GameAgent::GetPhysics();
}

void Player::SetSpeed(float playerSpeed)
{
	m_Speed = playerSpeed;
}

void Player::Move(int key)
{
	GLfloat NormalizedSpeed = m_Speed * deltaTime;

	if (key == GLFW_KEY_LEFT) {

	}

	if (key == GLFW_KEY_RIGHT) {

	}
}

int Player::GetType()
{
	return GameAgent::GetType();
}


