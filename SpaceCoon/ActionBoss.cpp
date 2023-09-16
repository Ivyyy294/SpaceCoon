#include "stdafx.h"
#include "ActionBoss.h"
#include "StaticField.h"

ActionBossSpawnFriends::ActionBossSpawnFriends (Boss* _boss)
	: friendsSpawned (false)
	, boss (_boss)
{
	baseHp = boss->GetHitPoints ();
}

void ActionBossSpawnFriends::Run (double lag)
{
	double screenW = LE_OH.GetPrimaryScreenGeometry ().width ();
	LE_ADD_O (new EnemyShip (screenW * 0.25, 0));
	LE_ADD_O (new EnemyShip (screenW * 0.85, 0));
	friendsSpawned = true;
}

bool ActionBossSpawnFriends::Check ()
{
	double tmp = double (boss->GetHitPoints ()) / double (baseHp);

	if (!friendsSpawned && tmp < 0.5f)
		return true;

	return false;
}

ActionBossShield::ActionBossShield (Boss* _boss)
	: AIPrimaryAction (false)
	, boss (_boss)
	, explosionTimer (0.f)
	, staticField (nullptr)
{
	baseHp = boss->GetShield()->GetHitPoints ();
	allowSubActions = false;
}

ActionBossShield::~ActionBossShield ()
{
}

void ActionBossShield::Run (double lag)
{
	if (boss->GetHitPoints () > 0)
	{
		lifeTime += lag;
		explosionTimer += lag;

		if (staticField == nullptr)
		{
			staticField = static_cast <StaticField*> (LE_ADD_O (new StaticField (boss)));
			staticField->MoveCenter (boss->GetShield ()->GetCenter ());
		}
		else
			staticField->MoveCenter (boss->GetShield ()->GetCenter ());

		if (lifeTime > 180.f)
		{
			boss->GetShield ()->ChangeHitPoints (-baseHp);
			staticField->SetDeleteMe ();
			staticField = nullptr;
			done = true;
		}
	}
	else
		done = true;
}

bool ActionBossShield::Check ()
{
	int hp = boss->GetShield ()->GetHitPoints ();

	if (hp <= 0)
	{
		lifeTime = 0.f;
		explosionTimer = 0.f;
		done = false;

		return true;
	}

	return false;
}
