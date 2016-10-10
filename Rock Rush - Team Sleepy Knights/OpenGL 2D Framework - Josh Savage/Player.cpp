#include "Player.h"
#include "Meteor.h"
#include "SpecialMeteor.h"

Player::Player(GLuint Shader, std::string _strTexture, std::vector<GLfloat> Vertices, std::vector<GLuint> Elements, glm::vec3 Position, float Rotation, Camera * Camera, b2Body* Physics)
	: GameAgent(Shader, _strTexture, Vertices, Elements, Position, Rotation, Camera, Physics, 8)
{
	SetSpeed(600.0f);
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
		GameAgent::AddUpwardsVelocity(NormalizedSpeed);
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



