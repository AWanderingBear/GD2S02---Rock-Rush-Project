#include "Player.h"
#include "Meteor.h"
#include "SpecialMeteor.h"

Player::Player(GLuint Shader, std::string _strTexture, std::vector<GLfloat> Vertices, std::vector<GLuint> Elements, glm::vec3 Position, float Rotation, Camera * Camera, b2Body* Physics)
	: GameAgent(Shader, _strTexture, Vertices, Elements, Position, Rotation, Camera, Physics, 8)
{
	SetSpeed(600.0f);
	Alive = true; 
	DeathTime = 1.0f;
	PlayerCode = 1;
}

Player::~Player()
{

}

bool Player::Update(float deltaTime)
{

	DeltaTime = deltaTime;

	if (Alive) {

		GameAgent::Update(); 
		b2Vec2 Position = PhysicsBody->GetPosition();

		if (Position.y > 31.5f) {

			Kill();
		}
	}
	else {

		DeathCounter += deltaTime;

		if (DeathCounter >= DeathTime) {

			//Bring to life
			Alive = true;
			PhysicsBody->SetGravityScale(1.0f);
			if (PlayerCode == 1) {
				PhysicsBody->SetTransform(b2Vec2(-3.2f, 15.0f), 0);
			}
			else {

				PhysicsBody->SetTransform(b2Vec2(45.6f, 15.0f), 0);
			}
		}
	}

	if (RemainingJumps < 6) {
		RemainingJumps++;
	}

	return true;
}

void Player::Render()
{
	if (Alive) {
		GameAgent::Render();
	}
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
	GLfloat NormalizedSpeed = m_Speed * DeltaTime;

	if (key == GLFW_KEY_LEFT) {
		GameAgent::AddSidewaysForce(-NormalizedSpeed);
	}

	if (key == GLFW_KEY_RIGHT) {
		GameAgent::AddSidewaysForce(NormalizedSpeed);
	}

	if (key == GLFW_KEY_DOWN) { 

		if (currentlyHolding != nullptr)	//Player is already holding something, we throw it away.
		{
			if (GetCurrentlyHolding()->GetType() == 3)	//Check if its a normal meteor
			{
				Meteor* currentObject = (Meteor*)GetCurrentlyHolding();	
				currentObject->DeleteJoint();
				b2Vec2 currentObjectVelocity = currentObject->GetPhysics()->GetLinearVelocity();
				//This is where the thrown objects get their height and speed
				currentObjectVelocity.x *= 1.5f;
				currentObjectVelocity.y += -5.0f;
				currentObject->GetPhysics()->SetLinearVelocity(currentObjectVelocity);
				SetCurrentlyHolding(nullptr);
			}
			else if (GetCurrentlyHolding()->GetType() == 4)	//If not it should be a special one
			{
				SpecialMeteor* currentObject = (SpecialMeteor*)GetCurrentlyHolding();
				currentObject->DeleteJoint();
				b2Vec2 currentObjectVelocity = currentObject->GetPhysics()->GetLinearVelocity();
				//This is where the thrown objects get their height and speed
				currentObjectVelocity.x *= 1.5f;
				currentObjectVelocity.y += -5.0f;
				currentObject->GetPhysics()->SetLinearVelocity(currentObjectVelocity);
				SetCurrentlyHolding(nullptr);
			}
			else
			{
				int i = 0;
				//ERROR CHECKING: THIS BREAKPOINT SHOULD NOT BE REACHED AND SOMETHING HAS GONE WRONG
			}
		}
		else    //The player is not holding something, attempt to pick it up.
		{
			if (currentlyTouching != nullptr)	// Error checking - Important, don't take out.
			{
				if (currentlyTouching->GetType() == 3)
				{
					currentlyHolding = GetCurrentlyTouching();
					Meteor* currentObject = (Meteor*)currentlyHolding;
					currentObject->CreateJoint(this);
				}
				else if (currentlyTouching->GetType() == 4)
				{
					currentlyHolding = GetCurrentlyTouching();
					SpecialMeteor* currentObject = (SpecialMeteor*)currentlyHolding;
					currentObject->CreateJoint(this);
				}
				else
				{
					int i = 0;
					//ERROR CHECKING: THIS BREAKPOINT SHOULD NOT BE REACHED AND SOMETHING HAS GONE WRONG
				}
			}
		}
	}

	if (key == GLFW_KEY_UP) {
		if (RemainingJumps > 0) {
			GameAgent::AddUpwardsVelocity(NormalizedSpeed);
			RemainingJumps--;
		}
	}
}

int Player::GetType()
{
	return GameAgent::GetType();
}

void Player::SetCurrentlyTouching(GameAgent* object)
{
	currentlyTouching = object;
}

GameAgent* Player::GetCurrentlyTouching()
{
	return currentlyTouching;
}

void Player::SetCurrentlyHolding(GameAgent* object)
{
	currentlyHolding = object;
}

GameAgent* Player::GetCurrentlyHolding()
{
	return currentlyHolding;
}

void Player::Kill()
{

	Alive = false;
	PhysicsBody->SetGravityScale(0.0f);
	PhysicsBody->SetTransform(b2Vec2(-10.0f, -10.0f), 0);
}



