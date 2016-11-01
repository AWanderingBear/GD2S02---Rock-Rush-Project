#pragma once
#include <Box2D/Box2D.h>
#include "GameAgent.h"
#include "Meteor.h"
#include "SpecialMeteor.h"

class MeteorCollisionHandler : public b2ContactListener
{
	//Int value type, 0 = ground, 1 = shootable, 2 = environment, 3 = Meteor, 4 = Special Meteor 8 = player

	void BeginContact(b2Contact* contact) override
	{
		GameAgent* bodyAUserData = (GameAgent*)contact->GetFixtureA()->GetUserData();
		GameAgent* bodyBUserData = (GameAgent*)contact->GetFixtureB()->GetUserData();

		int AType = bodyAUserData->GetType();
		int BType = bodyBUserData->GetType();

		if (AType == 3) {

			Meteor* meteor = (Meteor*)bodyAUserData;

			if (BType == 8) {
				Player* player = (Player*)bodyBUserData;
				player->SetCurrentlyTouching(bodyAUserData);
			}
		}
		else if (AType == 4)
		{
			SpecialMeteor* specialMeteor = (SpecialMeteor*)bodyAUserData;

			if (BType == 8) {
				Player* player = (Player*)bodyBUserData;
				player->SetCurrentlyTouching(bodyAUserData);
			}
		}
		else if (AType == 0)
		{
			if (BType == 8)
			{
				Player* player = (Player*)bodyBUserData;
				player->ResetJumps();
			}
		}
		else if (AType == 8) {
			Player* player = (Player*)bodyAUserData;

			if (BType == 3) {
				Meteor* meteor = (Meteor*)bodyBUserData;
				player->SetCurrentlyTouching(bodyBUserData);
			}
			if (BType == 4)
			{
				SpecialMeteor* specialMeteor = (SpecialMeteor*)bodyBUserData;
				player->SetCurrentlyTouching(bodyBUserData);
			}
			if (BType == 0)
			{
				player->ResetJumps();
			}
		}
	}

	void EndContact(b2Contact* contact) override
	{
		GameAgent* bodyAUserData = (GameAgent*)contact->GetFixtureA()->GetUserData();
		GameAgent* bodyBUserData = (GameAgent*)contact->GetFixtureB()->GetUserData();

		int AType = bodyAUserData->GetType();
		int BType = bodyBUserData->GetType();

		if (AType == 3) {

			Meteor* meteor = (Meteor*)bodyAUserData;

			if (BType == 8) {
				Player* player = (Player*)bodyBUserData;
				player->SetCurrentlyTouching(nullptr);
			}
		}
		if (AType == 4) {

			SpecialMeteor* specialMeteor = (SpecialMeteor*)bodyAUserData;

			if (BType == 8) {
				Player* player = (Player*)bodyBUserData;
				player->SetCurrentlyTouching(nullptr);
			}
		}
		else if (AType == 8) {
			Player* player = (Player*)bodyAUserData;

			if (BType == 3) {
				Meteor* meteor = (Meteor*)bodyBUserData;
				player->SetCurrentlyTouching(nullptr);
			}
			if (BType == 4) {
				SpecialMeteor* specialMeteor = (SpecialMeteor*)bodyBUserData;
				player->SetCurrentlyTouching(nullptr);
			}
		}
	}
};

