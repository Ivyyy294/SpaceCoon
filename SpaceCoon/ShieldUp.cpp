#include "stdafx.h"
#include "ShieldUp.h"

using namespace LarasEngine;

ShieldUp::ShieldUp(const int x, const int y)
	: GameObject (x, y, TYPID_SHIELD_UP)
	, value (0)
{
	collisionOn = true;
}

void ShieldUp::Update ()
{
	Translate (QPointF (0, 2));

	if (GetPosition().y() > screenH)
		deleteMe = true;
}

void ShieldUp::HandleCrash(LarasEngine::GameObject* obj)
{
	if (obj->GetTypId() == TYPID_PLAYER)
	{
		deleteMe = true;
		ShipPlayer* p = static_cast <ShipPlayer*> (LE_OH.GetObjectVec(TYPID_PLAYER).at(0).get());
		p->RechargeShield(value);
	}
}

void ShieldUp::ReadJson (const QJsonObject& json)
{
	value = json["value"].toInt ();
}
