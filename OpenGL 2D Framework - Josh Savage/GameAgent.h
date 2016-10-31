#pragma once

//Local Includes
#include "Model.h"
#include <Box2D\Box2D.h>

class GameAgent
{
public:
	GameAgent(GLuint Shader, std::string _strTexture, 
		std::vector<GLfloat> Vertices, std::vector<GLuint> Elements,  
		glm::vec3 Position, float Rotation, Camera* Camera, b2Body* Physics, int Type);
	GameAgent(GLuint Shader, std::string _strTexture, std::vector<GLfloat> Vertices, std::vector<GLuint> Elements, glm::vec3 Position, float Rotation, Camera * Camera);
	~GameAgent();

	void Update();
	void Render();

	b2Body* GetPhysics();


	int GetType();

protected:

	AgentType AgentBehaviour;
	Model AgentModel;

	glm::vec3 m_Position;
	float m_Rotation;

	b2Body* PhysicsBody;
	
	int ObjectType;

	void AddUpwardsVelocity(float _upwards);
	void AddSidewaysForce(float _sideForce);
};

