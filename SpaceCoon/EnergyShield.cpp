#include "stdafx.h"
#include "Laser.h"
#include "EnergyShield.h"
#include "ship.h"
#include "Explosion.h"

using namespace LarasEngine;

EnergyShield::EnergyShield(int _hitPoints, double _scale)
	: GameObject (0, 0, TYPID_SHIELD)
	, maxHp (_hitPoints)
{
	collisionOn = true;
	hitPoints = _hitPoints;
	collisionWhiteList.push_back (TYPID_ENEMY);
	collisionWhiteList.push_back (TYPID_PLAYER);
	collisionWhiteList.push_back (TYPID_HP_UP);
	collisionWhiteList.push_back (TYPID_SHIELD_UP);
	collisionWhiteList.push_back (TYPID_BOSS);

	QRectF rect = GetImageRect ();
	rect.setWidth (rect.width () * 0.85);
	rect.setHeight (rect.height () * 0.85);
	SetCollisionRect (rect);

	shieldBurst = new LarasEngine::ShieldBurst (this);
	LE_ADD_O (shieldBurst);
	//oWidth = GetImage ().width ();
}

void EnergyShield::Draw(QPainter* painter)
{
	if (!shieldBurst->GetActive() && hitPoints > 0)
		GameObject::Draw(painter);
}

void EnergyShield::Update ()
{
	collisionOn = !shieldBurst->GetActive () && hitPoints > 0;
}

void EnergyShield::HandleCrash(GameObject* obj)
{
	TypId id = obj->GetTypId();

	ChangeHitPoints(obj->GetCollisionDmg());
	
	Explosion::SpawnExplosion2 (GetAreaOfCollision (obj));
}

void EnergyShield::ShieldBurst ()
{
	uint cost = shieldBurst->GetCost ();

	if (hitPoints >= cost && !shieldBurst->GetActive ())
	{
		ChangeHitPoints (cost);
		shieldBurst->SetActive ();
	}
}

void EnergyShield::ReadJson (const QJsonObject& json)
{
	//shieldBurstCost = json["shieldBurstCost"].toInt ();
}
