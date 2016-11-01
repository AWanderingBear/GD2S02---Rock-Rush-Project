#include <iostream>

#include "Scene.h"
#include "QueryCallback.h"
#include "Game.h"

Scene::Scene(Camera* Camera, Game* Game, int TotalFirable, int TotalPigs)
{

	m_Camera = Camera;
	b2Vec2 gravity(0.0f, 10.0f);
	World = new b2World(gravity);
	WinningScore = TotalFirable;
	GameInstance = Game;
	MeteorCount = TotalPigs;
	P1Score = 0;
	P2Score = 0; 
}

Scene::~Scene()
{
	delete World;
}

void Scene::Update()
{
	if (P1Score > WinningScore || P2Score > WinningScore) {

		for (int i = 0; i < (int)Players.size(); i++)
		{
			Player* Agent = Players[i];
			if (i == 0)
			{
				Agent->GetPhysics()->SetTransform(b2Vec2(-3.2f, 15.0f), 0);
				Agent->GetPhysics()->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
			}
			else
			{
				Agent->GetPhysics()->SetTransform(b2Vec2(45.6f, 15.0f), 0);
				Agent->GetPhysics()->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
			}
		}
		GameInstance->NextScene();
		P1FinalScore = P1Score;
		P2FinalScore = P2Score;
		P1Score = 0;
		P2Score = 0;
	}

	m_Camera->Update();
	World->Step(1.0f / 60.0f, 6, 2);

	for (auto const& Agent : WorldAgents) {

		Agent->Update();
		Agent->Render();
	}

	for (int i = 0; i < (int)NormalMeteors.size(); i++) {

		Meteor* Agent = NormalMeteors[i];

		if (Agent != nullptr) {

			bool Alive = Agent->Update(m_Camera->getDeltaTime());
			if (Alive) {

				Agent->Render();
			}
			else {

				NormalMeteors.erase(NormalMeteors.begin() + i);
				World->DestroyBody(Agent->GetPhysics());
				delete Agent;
			}
		}
	}

	for (int i = 0; i < (int)SpecialMeteors.size(); i++) {

		SpecialMeteor* Agent = SpecialMeteors[i];

		bool Alive = Agent->Update();

		if (Alive) {

			Agent->Render();
		}
		else {

			//Scoring
			b2Vec2 Position = Agent->GetPhysics()->GetPosition();

			if (Position.x > 400) {

				//Player1 Scores
				P1Score++;
			}
			else {

				//Player2 Scores
				P2Score++;
			}

			SpecialMeteors.erase(SpecialMeteors.begin() + i);
			World->DestroyBody(Agent->GetPhysics());
			delete Agent;
		}
	}
	if (SpecialMeteors.size() < 1) {
		GameInstance->SpawnSpecialMeteor();
	}
	
	for (int i = 0; i < (int)Players.size(); i++)
	{
		Player* Agent = Players[i];

		if (Agent->GetPhysics()->GetTransform().p.y >= 20.0f)
		{
			if (Agent->underWater == false) 
			{
				b2Vec2 currentVelocity = Agent->GetPhysics()->GetLinearVelocity();
				currentVelocity.y /= 2;
				Agent->GetPhysics()->SetLinearVelocity(currentVelocity);	//Immediate subtle slow when enter water.

				Agent->GetPhysics()->SetLinearDamping(Agent->GetPhysics()->GetLinearDamping()* 5.0f);	//Water is resistant to changes in all movements
				Agent->GetPhysics()->SetGravityScale(0.5f);	//We dont want to cap jumping too hard and this setting seemed to make it decent.
				Agent->underWater = true;
			}
		}
		else
		{
			if (Agent->underWater == true)
			{
				Agent->GetPhysics()->SetLinearDamping(Agent->GetPhysics()->GetLinearDamping()* 0.2f);
				Agent->GetPhysics()->SetGravityScale(1.0f);
				Agent->underWater = false;
			}
		}
		//if (!ReturnCode) print debug message
		int ReturnCode = Agent->Update(m_Camera->getDeltaTime());
		Agent->Render();
	}

	if (DisplayScore) {

		GameInstance->DrawScore(P1Score, P2Score);
	}
}

int Scene::GetP1Score()
{
	return P1FinalScore;
}

int Scene::GetP2Score()
{
	return P2FinalScore;
}
void Scene::AddGameAgent(GameAgent* Adding)
{

	WorldAgents.push_back(Adding);
}

void Scene::AddShootable(Shootable * Adding)
{

	Shootables.push_back(Adding);
}

void Scene::AddRailGun(b2Body * Railgun, int index)
{
	RailgunPieces[index] = Railgun;
}

void Scene::AddMeteor(Meteor * Adding)
{
	NormalMeteors.push_back(Adding);
}

void Scene::AddSpecialMeteor(SpecialMeteor * Adding)
{
	SpecialMeteors.push_back(Adding);
}

void Scene::AddPlayer(Player* Adding)
{
	Players.push_back(Adding);
}

Player * Scene::GetPlayer(int i)
{
	return Players[i];
}

Camera * Scene::GetCamera()
{
	return m_Camera;
}

b2World * Scene::GetWorld()
{
	return World;
}

void Scene::HandleClick(glm::vec2 mousePos)
{

	if (m_mouseJoint != nullptr)
	{
		return;
	}

	glm::vec2 mWorldPos = m_Camera->ScreenToBox2D(mousePos);
	b2Vec2 p(mWorldPos.x, mWorldPos.y);
	std::cout << p.x << ", " << p.y << std::endl;
	// Make a small box.
	b2AABB aabb;
	b2Vec2 d;
	d.Set(0.001f, 0.001f);
	aabb.lowerBound = p - d;
	aabb.upperBound = p + d;

	QueryCallback callback(p);
	World->QueryAABB(&callback, aabb);

	if (callback.m_fixture)
	{
		b2Body* body = callback.m_fixture->GetBody();
		b2MouseJointDef md;
		md.bodyA = WorldAgents[1]->GetPhysics();
		md.bodyB = body;
		md.target = p;
		md.maxForce = 100000.0f * body->GetMass();
		m_mouseJoint = (b2MouseJoint*)World->CreateJoint(&md);
		body->SetAwake(true);
		m_mouseJoint->SetTarget(p);
	}
}

void Scene::HandleRelease()
{
	if (m_mouseJoint) {
		World->DestroyJoint(m_mouseJoint);
		m_mouseJoint = nullptr;
	}
}

void Scene::HandleMove(glm::vec2 mousePos)
{
	//Need to add a drop handler for if the player tries to move an object too far ahead
	glm::vec2 worldMouse = m_Camera->ScreenToBox2D(mousePos);
	b2Vec2 p(worldMouse.x, worldMouse.y);

	if (m_mouseJoint)
	{
		m_mouseJoint->SetTarget(p);
	}
}

void Scene::HandleMenuKeyInput(int _key)
{
	if (_key == GLFW_KEY_ENTER)
		GameInstance->NextScene();
	if (_key == GLFW_KEY_SPACE)
		GameInstance->GoToScene(3);
	if (_key == GLFW_KEY_BACKSPACE)
		GameInstance->GoToScene(0);
}

void Scene::HandleKeyInput(int _key)
{
	
	//Player 0 movement
	if (_key == GLFW_KEY_W)
		Players[0]->Move(GLFW_KEY_UP);
	if (_key == GLFW_KEY_S)
		Players[0]->Move(GLFW_KEY_DOWN);
	if (_key == GLFW_KEY_A)
		Players[0]->Move(GLFW_KEY_LEFT);
	if (_key == GLFW_KEY_D)
		Players[0]->Move(GLFW_KEY_RIGHT);

	//Player 1 movement
	if (_key == GLFW_KEY_I)
		Players[1]->Move(GLFW_KEY_UP);
	if (_key == GLFW_KEY_K)
		Players[1]->Move(GLFW_KEY_DOWN);
	if (_key == GLFW_KEY_J)
		Players[1]->Move(GLFW_KEY_LEFT);
	if (_key == GLFW_KEY_L)
		Players[1]->Move(GLFW_KEY_RIGHT);
}

<<<<<<< HEAD
=======
void Scene::EnableScore()
{
	DisplayScore = true;
}
>>>>>>> origin/Josh_Branch

void Scene::SetLaunchJoint(b2Joint * joint, int index)
{
	LaunchJoint[index] = joint;
}

b2Joint * Scene::GetLaunchJoint(int index)
{
	return LaunchJoint[index];
}

void Scene::SetPrisma(b2Body * PrismaticBody, b2PrismaticJoint * PrismaticJoint)
{
	prisma.push_back(PrismaticJoint);
	prismaBodies.push_back(PrismaticBody);
}
