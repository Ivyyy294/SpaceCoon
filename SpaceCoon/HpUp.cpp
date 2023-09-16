#include "stdafx.h"
#include "HpUp.h"
#include "ShipPlayer.h"

using namespace LarasEngine;

HpUp::HpUp(const int xPos)
	: GameObject (xPos, -100, TYPID_HP_UP)
{
	collisionOn = true;
	collisionDmg = 0;
}

void HpUp::Update ()
{
	Translate (QPointF (0, 2));

	if (GetPosition().y() > screenH)
		deleteMe = true;
}

void HpUp::HandleCrash(LarasEngine::GameObject* obj)
{
	if (obj->GetTypId () == TYPID_PLAYER)
	{
		ShipPlayer* player = static_cast<ShipPlayer*> (obj);
		player->ChangeHitPoints (-1);
		deleteMe = true;
	}
}

