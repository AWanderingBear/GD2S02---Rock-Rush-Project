#include <iostream>

#include "Scene.h"
#include "QueryCallback.h"
#include "Game.h"

Scene::Scene(Camera* Camera, Game* Game, int TotalFirable, int TotalPigs)
{

	m_Camera = Camera;
	b2Vec2 gravity(0.0f, 10.0f);
	World = new b2World(gravity);
	MaxFired = TotalFirable;
	GameInstance = Game;
	MeteorCount = TotalPigs;
}

Scene::~Scene()
{
	delete World;
}

void Scene::Update()
{


	if (FiredCount >= MaxFired) {

		if (SwitchCount > 300) {

			GameInstance->NextScene();
		}
		else {
			SwitchCount += 1;
		}
	}

	m_Camera->Update();
	World->Step(1.0f / 60.0f, 6, 2);

	for (auto const& Agent : WorldAgents) {

		Agent->Update();
		Agent->Render();
	}

	for (int i = 0; i < (int)NormalMeteors.size(); i++) {

		Meteor* Agent = NormalMeteors[i];

		Agent->Update();

		Agent->Render();
	}

	for (int i = 0; i < (int)SpecialMeteors.size(); i++) {

		SpecialMeteor* Agent = SpecialMeteors[i];

		Agent->Update();

		Agent->Render();
	}


	for (int i = 0; i < (int)Shootables.size(); i++) {

		Shootable* Agent = Shootables[i];

		int ReturnCode = Agent->Update();

		//if (ReturnCode == 1 && Firing == nullptr) {

		//	Firing = Agent;

		//	//Jointing the object
		//	b2DistanceJointDef jd;
		//	jd.frequencyHz = 0.5f;
		//	jd.dampingRatio = 0.0f;

		//	jd.bodyA = RailgunPieces[0];
		//	jd.localAnchorA.Set(10.0, 1.5);
		//	jd.bodyB = Agent->GetPhysics();
		//	jd.length = 4.0f;

		//	//LaunchJoint[0] = World->CreateJoint(&jd);

		//	jd.bodyA = RailgunPieces[1];
		//	jd.localAnchorA.Set(10.0, -1.5);
		//	LaunchJoint[1] = World->CreateJoint(&jd);

		//	FiredCount += 1;
		//}
		//else if (ReturnCode == 2 && Firing != nullptr) {

		//	World->DestroyJoint(LaunchJoint[0]);
		//	World->DestroyJoint(LaunchJoint[1]);
		//	Firing = nullptr;
		//	HandleRelease();
		//}

		//else if (ReturnCode == 3) {

		//	Shootables.erase(Shootables.begin() + i);
		//	World->DestroyBody(Agent->GetPhysics());
		//	m_mouseJoint = nullptr;
		//	delete Agent;
		//	break;
		//}

		Agent->Render();
	}

	for (int i = 0; i < (int)Players.size(); i++)
	{
		Player* Agent = Players[i];

		//if (!ReturnCode) print debug message
		int ReturnCode = Agent->Update();
		Agent->Render();
	}
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

void Scene::HandleKeyInput(int _key)
{
	//Player 0 movement
	if (_key == GLFW_KEY_UP)
		Players[0]->Move(GLFW_KEY_UP);
	if (_key == GLFW_KEY_DOWN)
		Players[0]->Move(GLFW_KEY_DOWN);
	if (_key == GLFW_KEY_LEFT)
		Players[0]->Move(GLFW_KEY_LEFT);
	if (_key == GLFW_KEY_RIGHT)
		Players[0]->Move(GLFW_KEY_RIGHT);

	//Player 1 movement
	if (_key == GLFW_KEY_U)
		Players[1]->Move(GLFW_KEY_UP);
	if (_key == GLFW_KEY_J)
		Players[1]->Move(GLFW_KEY_DOWN);
	if (_key == GLFW_KEY_H)
		Players[1]->Move(GLFW_KEY_LEFT);
	if (_key == GLFW_KEY_K)
		Players[1]->Move(GLFW_KEY_RIGHT);
}

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
