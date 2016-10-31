#include "Shootable.h"

Shootable::Shootable(GLuint Shader, std::string _strTexture, std::vector<GLfloat> Vertices, std::vector<GLuint> Elements, glm::vec3 Position, float Rotation, Camera * Camera, b2Body* Physics, int Type) : GameAgent(Shader, _strTexture, Vertices, Elements, Position, Rotation, Camera, Physics, Type)
{
	Current = Nothing;
}


Shootable::~Shootable()
{
}

int Shootable::Update()
{
	GameAgent::Update();

	if (PhysicsBody->GetPosition().x < 9 && Current == Nothing) {

		Current = Launching;
		return 1;
	}
	else if (PhysicsBody->GetPosition().x > 9.5 && Current == Launching) {

		Current = Launched;
		if (GameAgent::GetType() == 4) {

			PhysicsBody->SetLinearDamping(-50.0f);
		}
		else if (GameAgent::GetType() == 5) {

			PhysicsBody->SetGravityScale(-1.0);
		}
		return 2;
	}

	else if (Current == Launched) {

		Alive++;

		if (Alive > 240) {

			return 3;
		}
	}

	return 0;
}

void Shootable::Render()
{
	GameAgent::Render();
}

b2Body * Shootable::GetPhysics()
{
	return GameAgent::GetPhysics();
}

int Shootable::GetType() {

	return GameAgent::GetType();
}
