#pragma once
#include <Box2D/Box2D.h>
#include "GameAgent.h"
#include "Enemy.h"

class EnemyCollisionHandler : public b2ContactListener
{

	void BeginContact(b2Contact* contact) {

		GameAgent* bodyAUserData = (GameAgent*)contact->GetFixtureA()->GetUserData();
		GameAgent* bodyBUserData = (GameAgent*)contact->GetFixtureB()->GetUserData();

		int AType = bodyAUserData->GetType();
		int BType = bodyBUserData->GetType();


		if (AType == 3) {

			Enemy* enemy = (Enemy*)bodyAUserData;

			if (BType == 0 || BType == 1 || BType == 4 || BType == 5) {

				enemy->Kill();
			}
		}
		else if (BType == 3) {

			Enemy* enemy = (Enemy*)bodyBUserData;

			if (AType == 0 || AType == 1 || AType == 4 || AType == 5) {

				enemy->Kill();
			}
		}
	}
};

