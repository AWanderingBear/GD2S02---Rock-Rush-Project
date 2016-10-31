#include "Meteor.h"



Meteor::Meteor(GLuint Shader, std::string _strTexture, std::vector<GLfloat> Vertices, std::vector<GLuint> Elements, glm::vec3 Position, float Rotation, Camera * Camera, b2Body* Physics): GameAgent(Shader, _strTexture, Vertices, Elements, Position, Rotation, Camera, Physics, 3)
{
	Alive = true;
}

Meteor::~Meteor()
{
}

bool Meteor::Update(float deltaTime)
{
	GameAgent::Update();
	
	if (holdingJoint == nullptr) {

		LifeTime += deltaTime;

		if (LifeTime > LifeSpan) {

			Alive = false;
		}
	}

	return Alive;
}

void Meteor::Render()
{
	GameAgent::Render();
}

b2Body * Meteor::GetPhysics()
{
	return GameAgent::GetPhysics();
}

int Meteor::GetType()
{
	return GameAgent::GetType();
}

void Meteor::Kill()
{
	Alive = false;
}

void Meteor::CreateJoint(Player* _Player)
{
	DeleteJoint();	//Check and delete current joint

	LifeTime = 0.0f;

	GetPhysics()->SetLinearVelocity(b2Vec2(0.0f, 0.0f)); //Reset speed so we don't get infinite jumping xD
	b2WeldJointDef md;
	md.bodyA = _Player->GetPhysics();
	md.bodyB = GetPhysics();
	md.localAnchorB = b2Vec2(0.0f, 2.2f);
	holdingJoint = (b2WeldJoint*)GetPhysics()->GetWorld()->CreateJoint(&md);
	currentlyConnectedPlayer = _Player;
	currentlyConnectedPlayer->SetCurrentlyHolding(this);
}

void Meteor::DeleteJoint()	//Delete joint so that the next one will be the only one.
{
	if (holdingJoint != nullptr)
	{
		GetPhysics()->GetWorld()->DestroyJoint(holdingJoint);
		holdingJoint = nullptr;
		currentlyConnectedPlayer->SetCurrentlyHolding(NULL);
	}

}
