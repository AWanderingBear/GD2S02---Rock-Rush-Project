#include "GameAgent.h"
#include <Box2D\Box2D.h>
#include <iostream>

GameAgent::GameAgent(GLuint Shader, std::string _strTexture,
	std::vector<GLfloat> Vertices, std::vector<GLuint> Elements,
	glm::vec3 Position, float Rotation, Camera* Camera, b2Body* Physics, int Type)
	//Int value type, 0 = ground, 1 = shootable, 2 = environment, 3 = enemy
{
	m_Position = Position;
	m_Rotation = Rotation;

	AgentModel.Initialise(Vertex, Textured, Shader, _strTexture, Vertices, Elements, Camera);

	PhysicsBody = Physics;

	ObjectType = Type;
} 

GameAgent::GameAgent(GLuint Shader, std::string _strTexture,
	std::vector<GLfloat> Vertices, std::vector<GLuint> Elements,
	glm::vec3 Position, float Rotation, Camera* Camera)
{
	m_Position = Position;
	m_Rotation = Rotation;

	AgentModel.Initialise(Vertex, Textured, Shader, _strTexture, Vertices, Elements, Camera);
}

GameAgent::~GameAgent()
{

}

void GameAgent::Update()
{
	if (PhysicsBody != nullptr) {

		if (PhysicsBody->GetType() == b2_dynamicBody) {

			b2Vec2 Passing = PhysicsBody->GetPosition();
			m_Position.x = Passing.x * 25;
			m_Position.y = Passing.y * 25;

			float Angle = PhysicsBody->GetAngle();
			Angle =  glm::degrees(Angle);
			if (Angle > 360) {
				Angle -= 360;
			}
			else if (Angle < -360) {
				Angle += 360;
			}

			m_Rotation = Angle;
		}
	}
	AgentModel.Update(m_Position, m_Rotation);
}

void GameAgent::Render()
{
	AgentModel.Render();
}

b2Body * GameAgent::GetPhysics()
{
	return PhysicsBody;
}

int GameAgent::GetType()
{
	return ObjectType;
}
