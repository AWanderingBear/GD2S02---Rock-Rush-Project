#include "GameAgent.h"
#include <Box2D\Box2D.h>
#include <iostream>

GameAgent::GameAgent(GLuint Shader, std::string _strTexture,
	std::vector<GLfloat> Vertices, std::vector<GLuint> Elements,
	glm::vec3 Position, float Rotation, Camera* Camera, b2Body* Physics, int Type)
	//Int value type, 0 = ground, 1 = shootable, 2 = environment, 3 = Meteor, 4 = player
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

void GameAgent::Update()	//A - I think this automatically updates the OpenGL position based on the box2D body position??
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

void GameAgent::AddUpwardsVelocity(float _upwards)
{	//Directly changes the bodys velocity to make jumps jumpier.
	//Stupid fucking code cant fucking switch between fucking vec2 and b2vec2 fucking hell.
	b2Vec2 newVelocity = PhysicsBody->GetLinearVelocity();	//Gets the old
	newVelocity.y = -_upwards;
	PhysicsBody->ApplyLinearImpulseToCenter(newVelocity, true);
	PhysicsBody->SetLinearVelocity(newVelocity);
}

void GameAgent::AddSidewaysForce(float _sideForce)
{
	b2Vec2 newVelocity = PhysicsBody->GetLinearVelocity();
	newVelocity.x = _sideForce;
	PhysicsBody->SetLinearVelocity(newVelocity);
	PhysicsBody->SetLinearDamping(0.5f);
}

int GameAgent::GetType()
{
	return ObjectType;
}
