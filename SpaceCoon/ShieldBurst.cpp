#include "stdafx.h"
#include "ShieldBurst.h"
#include "Explosion.h"

using namespace LarasEngine;

ShieldBurst::ShieldBurst ()
	: GameObject (0, 0, TYPID_SHIELD_BURST)
{
	collisionWhiteList.push_back (TYPID_ENEMY);
	collisionWhiteList.push_back (TYPID_PLAYER);
	collisionWhiteList.push_back (TYPID_HP_UP);
	collisionWhiteList.push_back (TYPID_SHIELD_UP);
	collisionWhiteList.push_back (TYPID_BOSS);
}

LarasEngine::ShieldBurst::ShieldBurst (GameObject* p)
	: GameObject (0, 0, TYPID_SHIELD_BURST)
	, parent (p)
{
	collisionWhiteList.push_back (TYPID_ENEMY);
	collisionWhiteList.push_back (TYPID_PLAYER);
	collisionWhiteList.push_back (TYPID_HP_UP);
	collisionWhiteList.push_back (TYPID_SHIELD_UP);
	collisionWhiteList.push_back (TYPID_BOSS);
}

void ShieldBurst::Update ()
{
	if (parent != nullptr)
	{
		QPointF newPos = parent->GetCenter ();
		newPos.setY (newPos.y() - 64);
		MoveCenter (newPos);
	}

	if (active)
	{
		if (lifeTime > 1.25)
		{
			LoadImage (TYPID_SHIELD_BURST);
			collisionOn = false;
			active = false;
		}
		else if (lifeTime > 0.15)
			LoadImage (TYPID_SHIELD_BURST_4);
		else if (lifeTime > 0.1)
		{
			collisionOn = true;
			LoadImage (TYPID_SHIELD_BURST_3);
		}
		else if (lifeTime > 0.05)
			LoadImage (TYPID_SHIELD_BURST_2);

		lifeTime += TimeInfo::Me ().GetDeltaTime ();
	}
}

void LarasEngine::ShieldBurst::Draw (QPainter* painter)
{
	if (active)
		GameObject::Draw (painter);
}

void LarasEngine::ShieldBurst::HandleCrash (GameObject* obj)
{
	obj->ChangeHitPoints (obj->GetHitPoints ());
	Explosion::SpawnExplosion2 (GetAreaOfCollision (obj));
}

void LarasEngine::ShieldBurst::SetActive ()
{
	active = true;
	lifeTime = 0.0;
}

void LarasEngine::ShieldBurst::ReadJson (const QJsonObject& json)
{
	GameObject::ReadJson (json);
	cost = json["cost"].toInt ();
}
