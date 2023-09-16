#include "stdafx.h"
#include "Laser.h"
#include "Explosion.h"

using namespace LarasEngine;

Laser::Laser(int x, int y, double r, bool _up)
	: Projectile (x, y, r, TYPID_LASER)
	, punkte (GlobalGameValues::Me().scorePoints)
	, up (_up)
	, subTyp (TYPID_LASER)
{
	MoveCenter(QPoint (x, y));
	LE_OH.PlaySound(TYPID_LASER, 0.1f);

	collisionWhiteList.push_back (TYPID_LASER);
	collisionWhiteList.push_back (TYPID_LASER_BLUE);
	collisionWhiteList.push_back (TYPID_HP_UP);
	collisionWhiteList.push_back (TYPID_SHIELD_UP);

	QRectF rect = GetImageRect ();
	rect.setWidth (rect.width () * 1.2);
	rect.setHeight (rect.height () * 1.2);
	SetCollisionRect (rect);
}


Laser::~Laser(void)
{
}

void Laser::Update ()
{
	Projectile::Update();

	//verhinder eine Kollision mit dem Schutzschield beim abschießen
	if (lifetimeMs >= 32)
		collisionOn = true;

	if (lifetimeMs >= 80 && subTyp == TYPID_LASER)
	{
		subTyp = TYPID_LASER_2;
		SwitchImage(TYPID_LASER_2);
	}

	if (lifetimeMs >= 320 && subTyp == TYPID_LASER_2)
	{
		subTyp = TYPID_LASER_3;
		SwitchImage(TYPID_LASER_3);
	}

	QRectF rect = GetImageRect ();
	if (rect.y() < 0 || rect.y() > screenH)
		deleteMe = true;
}

void Laser::HandleCrash(LarasEngine::GameObject* obj)
{
	const std::string& objTypId = obj->GetTypId ();

	QRectF r = GetAreaOfCollision (obj);
	Explosion::SpawnExplosion(r.center().x(), r.center().y());
	deleteMe = true;
}

LaserBlue::LaserBlue (int x, int y, double r, int _speed, bool _up)
	: Projectile (x, y, r, TYPID_LASER_BLUE)
	, punkte (GlobalGameValues::Me ().scorePoints)
	, up (_up)
	, subTyp (TYPID_LASER_BLUE)
{
	MoveCenter (QPoint (x, y));
	hitPoints = 1;
	collisionDmg = 6;

	collisionOn = false;
	/*if (targetTyp == TYPID_LASER)
		collisionOn = true;*/

	LE_OH.PlaySound (TYPID_LASER, 0.01f);
}

void LaserBlue::Update ()
{
	Projectile::Update ();

	//verhinder eine Kollision mit dem Schutzschield beim abschießen
	if (lifetime >= 5)
		collisionOn = true;

	if (lifetime >= 5 && subTyp == TYPID_LASER_BLUE)
	{
		subTyp = TYPID_LASER_BLUE_2;
		SwitchImage (TYPID_LASER_BLUE_2);
	}

	if (lifetime >= 20 && subTyp == TYPID_LASER_BLUE_2)
	{
		subTyp = TYPID_LASER_BLUE_3;
		SwitchImage (TYPID_LASER_BLUE_3);
	}

	QRectF rect = GetImageRect ();
	if (rect.y () < 0 || rect.y () > screenH)
		deleteMe = true;
}

void LaserBlue::HandleCrash (LarasEngine::GameObject* obj)
{
	const std::string& objTypId = obj->GetTypId ();

	if (objTypId != TYPID_LASER
		&& objTypId != TYPID_LASER_BLUE
		&& objTypId != TYPID_HP_UP
		&& objTypId != TYPID_SHIELD_UP)
	{
		QRectF r = GetAreaOfCollision (obj);
		Explosion::SpawnExplosion (r.center ().x (), r.center ().y ());
		deleteMe = true;
	}
}
