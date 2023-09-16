#include "stdafx.h"
#include "Rocket.h"
#include "Explosion.h"

using namespace LarasEngine;

Rocket::Rocket (int x, int y, double r)
	: Projectile (x, y, r, TYPID_ROCKET)
{
	SetPosition (QPoint (x, y));
	collisionOn = false;

	collisionWhiteList.push_back (TYPID_ROCKET);
	collisionWhiteList.push_back (TYPID_HP_UP);
}

void Rocket::HandleCrash (LarasEngine::GameObject* obj)
{
	if (obj->GetTypId () == TYPID_LASER)
	{
		ChangeHitPoints (obj->GetCollisionDmg ());
		deleteMe = hitPoints <= 0;
	}
	else
	{
		QRectF r = GetAreaOfCollision (obj);
		Explosion::SpawnExplosion (r.center ().x (), r.center ().y ());
		deleteMe = true;
	}
}

void Rocket::Update ()
{
	Projectile::Update ();

	if (!collisionOn && lifetimeMs > 160)
		collisionOn = true;

	if (GetPosition().y () > screenH)
		deleteMe = true;
}