#include "stdafx.h"
#include "Boss.h"
#include "Input.h"
#include "ActionBoss.h"
#include "Rocket.h"

using namespace LarasEngine;

Boss::Boss()
    : EnemyShip (0,0, TYPID_BOSS)
 {
    SetPosition((screenW - GetImageRect().width()) / 2, 0);
}

void Boss::Init()
{
    EnemyShip::Init();
	 AddPrimaryAIAction (1, new ActionBossShield (this));
	// AddSubAIAction (3, new ActionBossSpawnFriends (this));
}

void Boss::ReadJson (const QJsonObject& json)
{
	EnemyShip::ReadJson (json);
	salvoCount = json["LaserSalvo"].toInt ();
	salvoAngle = json["LaserSalvoAngle"].toDouble ();
}

void Boss::HandleCrash (LarasEngine::GameObject* obj)
{
	Ship::HandleCrash (obj);

	if (deleteMe)
		GlobalGameValues::Me ().scorePoints += 200;
}

void Boss::SpawnLaser ()
{
	QRectF rect = GetImageRect ();
	int xPos = rect.center ().x ();

	if (rotation != 0.0)
	{
		int xOffset = tan (std::fabs (rotation) * PI / 180) * (GetImage().height () / 2);

		if (rotation > 0.0)
			xPos -= xOffset;
		else if (rotation < 0.0)
			xPos += xOffset;
	}

	int yPos = rect.bottomRight ().y ();

	double r1 = salvoAngle;
	double r2 = r1 * (salvoCount - 1);
	double r3 = -r2 / 2;

	for (int i = 0; i < salvoCount; ++i)
	{
		double rTmp = r3 + r1 * i + rotation;
		LE_ADD_O (new Rocket (xPos, yPos, rTmp));
	}
}

