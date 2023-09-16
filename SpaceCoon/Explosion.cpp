#include "stdafx.h"
#include "Explosion.h"

using namespace LarasEngine;

Explosion::Explosion(int x, int y)
	: GameObject(0, 0, TYPID_EXPLOSION)
	, drawCounter(0)
	, subTyp (TYPID_EXPLOSION)
{
	SetPosition (x, y);
	collisionOn = false;
	LE_OH.PlaySound(TYPID_EXPLOSION, 1.0f);
}


Explosion::~Explosion()
{
}

void Explosion::Update ()
{
	drawCounter += TimeInfo::Me ().GetFactor ();;

	if (drawCounter >=5.f && subTyp == TYPID_EXPLOSION)
	{
		subTyp = TYPID_EXPLOSION_2;
		SwitchImage(TYPID_EXPLOSION_2);
	}
	else if (drawCounter >= 10.f && subTyp == TYPID_EXPLOSION_2)
	{
		subTyp = TYPID_EXPLOSION_3;
		SwitchImage(TYPID_EXPLOSION_3);
	}

	deleteMe = drawCounter >= 15.f
		? true
		: false;
}

void Explosion::SpawnExplosion(int x, int y)
{
	const auto& vec = LE_OH.GetObjectVec(TYPID_EXPLOSION);

	for (const auto& i : vec)
	{
		QRectF tmpRect = i->GetImageRect ();
		QRectF oldRect(0, 0, tmpRect.width(), tmpRect.height() / 2);
		QRectF newRect = oldRect;

		oldRect.moveCenter(tmpRect.center());
		newRect.moveCenter(QPoint (x, y));

		if (oldRect.intersects (newRect))
			return;
	}

	LE_ADD_O(new Explosion(x, y));
}

void Explosion::SpawnExplosion2 (const QRectF& r)
{
	GameObject* e = LE_ADD_O (new Explosion (0, 0));
	e->MoveCenter (r.center ());
}

void Explosion::SpawnExplosion2 (const QPointF& p)
{
	LE_ADD_O (new Explosion (p.x(), p.y()));
}
