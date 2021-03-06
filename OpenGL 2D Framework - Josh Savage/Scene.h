#pragma once
//Global Includes
#include <vector>
#include "Dependencies\Box2D\Box2D.h"

//Local Includes
#include "GameAgent.h"
#include "Shootable.h"
#include "Meteor.h"
#include "Player.h"
#include "SpecialMeteor.h"

class Game;

class Scene
{
public:
	Scene(Camera* Camera, Game* Game, int TotalFirable, int TotalPigs);
	~Scene();

	void Update();

	void AddGameAgent(GameAgent* Adding);
	void AddShootable(Shootable* Adding);
	void AddRailGun(b2Body* Railgun, int index);
	void AddMeteor(Meteor* Adding);
	void AddSpecialMeteor(SpecialMeteor* Adding);
	void AddPlayer(Player* Adding);
	int GetP1Score();
	int GetP2Score();

	Player* GetPlayer(int player);
	Camera* GetCamera();

	b2World* GetWorld();

	void HandleClick(glm::vec2 mousePos);
	void HandleRelease();
	void HandleMove(glm::vec2 mousePos);
	void HandleKeyInput(int _key);
	void HandleMenuKeyInput(int _key);

	void EnableScore();

	//std::vector<Player>GetPlayer();

	void SetLaunchJoint(b2Joint* joint, int index);
	b2Joint* GetLaunchJoint(int index);


	void SetPrisma(b2Body* PrismaticBody, b2PrismaticJoint* PrismaticJoint);

private:

	std::vector<GameAgent*> WorldAgents;
	Camera* m_Camera;

	b2World* World;
	b2MouseJoint* m_mouseJoint;
	b2Joint* LaunchJoint[2];
	std::vector<Shootable*> Shootables;
	Shootable* Firing;

	b2Body* RailgunPieces[2];

	std::vector<b2Body*> prismaBodies;
	std::vector<b2PrismaticJoint*> prisma;

	//Firable
	int FiredCount = 0;
	int WinningScore;

	//Meteors
	int MeteorCount;
	std::vector<Meteor*> NormalMeteors;
	std::vector<SpecialMeteor*> SpecialMeteors; //I can't be bothered learning the logic so copying everything.

	//Players
	std::vector<Player*> Players;

	bool DisplayScore = false; 

	int P1Score;
	int P2Score;
	int P1FinalScore;
	int P2FinalScore;

	Game* GameInstance;
	int SwitchCount;
};

