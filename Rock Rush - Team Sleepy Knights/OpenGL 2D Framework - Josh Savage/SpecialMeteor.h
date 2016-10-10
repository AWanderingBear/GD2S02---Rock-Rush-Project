#pragma once
#include "GameAgent.h"
#include "Player.h"
class SpecialMeteor :
	protected GameAgent

{
public:
	SpecialMeteor(GLuint Shader, std::string _strTexture, std::vector<GLfloat> Vertices, std::vector<GLuint> Elements, glm::vec3 Position, float Rotation, Camera * Camera, b2Body* Physics);
	~SpecialMeteor();

	bool Update();
	void Render();
	b2Body* GetPhysics();
	int GetType();
	void Kill();

	void CreateJoint(Player* player);			//The Meteor creates and deletes the joints.
	void DeleteJoint();

private:

	bool Alive;
	//CreateJoint calls this if needed.
	b2WeldJoint* holdingJoint = nullptr;					//The enemies current joint
	Player* currentlyConnectedPlayer;	//I couldn't think of any better way to reset the player carrying bool than to store the player in here to us in functions, sorry for ugly code.
};
