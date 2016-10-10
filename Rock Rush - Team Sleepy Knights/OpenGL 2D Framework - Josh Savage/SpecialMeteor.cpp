#include "SpecialMeteor.h"



SpecialMeteor::SpecialMeteor(GLuint Shader, std::string _strTexture, std::vector<GLfloat> Vertices, std::vector<GLuint> Elements, glm::vec3 Position, float Rotation, Camera * Camera, b2Body* Physics) : GameAgent(Shader, _strTexture, Vertices, Elements, Position, Rotation, Camera, Physics, 4)
{
	Alive = true;
}

SpecialMeteor::~SpecialMeteor()
{
}

bool SpecialMeteor::Update()
{
	GameAgent::Update();
	return Alive;
}

void SpecialMeteor::Render()
{
	GameAgent::Render();
}

b2Body * SpecialMeteor::GetPhysics()
{
	return GameAgent::GetPhysics();
}

int SpecialMeteor::GetType()
{
	return GameAgent::GetType();
}

void SpecialMeteor::Kill()
{

	Alive = false;
}

void SpecialMeteor::CreateJoint(Player* _Player)
{
	DeleteJoint();	//Check and delete current joint

	GetPhysics()->SetLinearVelocity(b2Vec2(0.0f, 0.0f)); //Reset speed so we don't get infinite jumping xD
	b2WeldJointDef md;
	md.bodyA = _Player->GetPhysics();
	md.bodyB = GetPhysics();
	md.localAnchorB = b2Vec2(0.0f, 2.2f);
	holdingJoint = (b2WeldJoint*)GetPhysics()->GetWorld()->CreateJoint(&md);
	currentlyConnectedPlayer = _Player;
	currentlyConnectedPlayer->SetCurrentlyHolding(this);
}

void SpecialMeteor::DeleteJoint()	//Delete joint so that the next one will be the only one.
{
	if (holdingJoint != nullptr)
	{
		GetPhysics()->GetWorld()->DestroyJoint(holdingJoint);
		holdingJoint = nullptr;
		currentlyConnectedPlayer->SetCurrentlyHolding(NULL);
	}

}
