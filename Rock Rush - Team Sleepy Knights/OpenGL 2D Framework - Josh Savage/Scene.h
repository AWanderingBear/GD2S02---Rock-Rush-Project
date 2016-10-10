#pragma once
//Global Includes
#include <vector>
#include "Dependencies\Box2D\Box2D.h"

//Local Includes
#include "GameAgent.h"
#include "Shootable.h"
#include "Enemy.h"
#include "Player.h"
#include "TextLabel.h"

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
	void AddEnemy(Enemy* Adding);
	void AddPlayer(Player* Adding);

	Player* GetPlayer(int player);
	Camera* GetCamera();

	b2World* GetWorld();

	void HandleClick(glm::vec2 mousePos);
	void HandleRelease();
	void HandleMove(glm::vec2 mousePos);
	void HandleKeyInput();

	//std::vector<Player>GetPlayer();

	void SetLaunchJoint(b2Joint* joint, int index);
	b2Joint* GetLaunchJoint(int index);

	void SetPrisma(b2Body* PrismaticBody, b2PrismaticJoint* PrismaticJoint);

	std::vector<TextLabel> vecLabels;

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
	int MaxFired;
	//Enemies
	int EnemyCount;
	std::vector<Enemy*> Enemies;

	/*Player* pPlayer;*/
	Game* GameInstance;
	int SwitchCount;
	std::vector<Player*> Players;

};

