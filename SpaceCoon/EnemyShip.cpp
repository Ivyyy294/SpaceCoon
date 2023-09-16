#include "stdafx.h"
#include "EnemyShip.h"
#include "Rocket.h"
#include "Explosion.h"
#include "Input.h"
#include "ActionsEnemyShip.h"
#include "ActionsAllgemein.h"

using namespace LarasEngine;

EnemyShip::EnemyShip (const int xPos, const int yPos, const CoreObject::TypId& _typId)
	: Ship (xPos, yPos, _typId)
{
}

void EnemyShip::HandleCrash(GameObject* obj)
{
	Ship::HandleCrash(obj);

	if (deleteMe)
		GlobalGameValues::Me().scorePoints += 50;
}

void EnemyShip::Update ()
{
	input = 0;

	AI::Run (TimeInfo::Me ().GetFactor ());

	double lag = TimeInfo::Me ().GetFactor ();
	animations.RunAnimations (lag);

	//ApplyHorizontalMovement (input);
	//ApplyVerticalMovement (input);

	if (!velocity.isNull ())
		Translate (velocity * lag);

	if (shield != nullptr)
		shield->MoveCenter (GetCenter ());
}


void EnemyShip::Init()
{
	Ship::Init();

	AddPrimaryAIAction (10, new ActionShipEntrance(this));
	AddPrimaryAIAction (11, new ActionShipEvade (this));
	AddSubAIAction (12, new ActionShootPlayer (this));
	AddSubAIAction (1, new ActionFacePlayer (this));
}

void EnemyShip::SpawnLaser()
{
	QRectF rect = GetImageRect ();

	int xPos = rect.center().x();

	if (rotation != 0.0)
	{
		int xOffset = tan(std::fabs(rotation) * PI / 180) * (GetImage().height() / 2);

		if (rotation > 0.0)
			xPos -= xOffset;
		else if (rotation < 0.0)
			xPos += xOffset;
	}

	int yPos = rect.bottomRight().y();

	LE_ADD_O(new Rocket (xPos, yPos, rotation));
}

void EnemyShip::ReadJson(const QJsonObject& json)
{
	Ship::ReadJson(json);
}

bool EnemyShip::IsPlayerInRange()
{
	QRectF rect = GetImageRect ();
	QRectF rectRange = rect;
	rectRange.setX(rect.x() - rect.width() * 2);
	rectRange.setWidth(rect.width() * 5);

	GameObject* player = LE_OH.GetObjectVec(TYPID_PLAYER).at(0).get();

	double angleToPlayer = CalculateAngleToPlayer();

	return angleToPlayer <= maxRotAngle && angleToPlayer >= (maxRotAngle * -1);
}

double EnemyShip::CalculateAngleToPlayer()
{
	GameObject* player = LE_OH.GetObjectVec(TYPID_PLAYER).at(0).get();
	double xDis = std::fabs(GetCenter().x() - player->GetCenter().x());
	double yDis = std::fabs(GetCenter().y() - player->GetCenter ().y());

	double param = xDis / yDis;
	double alpha = atan(param) * 180 / PI;
	return alpha;
}
