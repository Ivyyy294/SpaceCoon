#include "stdafx.h"
#include "Meteorit.h"
#include "Laser.h"
#include "Explosion.h"
#include <qdebug.h>

using namespace LarasEngine;

Meteorit::Meteorit(int xPos, int yPos, TypId id)
	: GameObject (xPos, yPos, TYPID_ASTEROID)
	, subTyp (id)
{
	collisionOn = true;

	LoadImage(subTyp);

	SetPosition(xPos, yPos);

	QRectF rect = GetImageRect ();
	rect.setWidth (rect.width () * 0.9);
	rect.setHeight (rect.height () * 0.9);
	SetCollisionRect (rect);

	LoadJson();
}

Meteorit::~Meteorit(void)
{
}

void Meteorit::SpawnMeteorit ()
{
	double size = 1.0;

	int rsize = rand() % 100;
	TypId id = TYPID_ASTEROID_128;

	if (rsize <= 25)
		id = TYPID_ASTEROID_256;

	Meteorit* m (new Meteorit(0, 0, id));

	int rndX = rand() % (LE_OH.GetPrimaryScreenGeometry().width () - m->GetImage().width()) * 13;
	int rndY = rand() % 100 * 13;

	int x = rndX / 13;
	int y = -200;

	m->SetPosition(x, y);

	GameObject::Vec& vector = LE_OH.GetObjectVec (TYPID_ASTEROID);

	if (vector.empty())
		LE_ADD_O(m);
	else
	{
		bool ok = true;

		for (GameObject::Shared o : vector)
		{
			if (m->CheckCrash(o.get())
				|| m->CheckCrashX(o.get()))
			{
				ok = false;
				break;
			}
		}
				
		if (ok)
			LE_ADD_O(m);
		else
			delete (m);
	}
}

void Meteorit::ApplyTrajectory ()
{
	velocity.setX (CalculateXViaRotation (velocity.y(), trajectory));
}

void Meteorit::ReadJson (const QJsonObject& json)
{
	GameObject::ReadJson(json);
	hitPoints = subTyp == TYPID_ASTEROID_128 ? json["hitpoints128"].toInt() : json["hitpoints256"].toInt();
	trajectory = json["maxTrajectory"].toDouble();
	offsetRotation = json["maxRotation"].toDouble();
	baseHp = hitPoints;
}

void Meteorit::Init()
{
	int r = rand() % 100;

	if (r < 50)
	{
		trajectory = -trajectory + rand() % (int)(trajectory * 2);
		ApplyTrajectory ();
	}
	else
		trajectory = 0;

	offsetRotation = offsetRotation * r * 0.01;

	int r2 = rand () % 100;

	if (r2 < 50)
		offsetRotation *= -1;

	velocity.setY (1 + GlobalGameValues::Me ().difficulty + rand() % (velocity.toPoint().y()));
}

void Meteorit::SpawnExplosionAtCollision(LarasEngine::GameObject* obj)
{
	QRectF r = GetAreaOfCollision (obj);

	if (r.width() >= r.height())
	{
		Explosion::SpawnExplosion(r.center().x(), r.center().y());
		Explosion::SpawnExplosion(r.topLeft().x(), r.center().y());
		Explosion::SpawnExplosion(r.topRight().x(), r.center().y());
	}
	else
	{
		Explosion::SpawnExplosion(r.center().x(), r.center().y());
		Explosion::SpawnExplosion(r.center().x(), r.topLeft().y());
		Explosion::SpawnExplosion(r.center().x(), r.bottomLeft().y());
	}
}

int Meteorit::GetScorePoints() const
{
	return baseHp;
}

void Meteorit::SetStartPosition(const int x, const int y)
{
	SetPosition(x, y);
}

void Meteorit::Update ()
{
	Translate (velocity * TimeInfo::Me ().GetFactor ());

	rotation += offsetRotation;

	deleteMe = GetPosition().y() >= screenH;
}

void Meteorit::HandleCrash(GameObject* obj)
{
	if (hitPoints > 0)
	{
		GameObject::TypId objTypId = obj->GetTypId ();

		if (objTypId == TYPID_PLAYER
			|| objTypId == TYPID_ENEMY
			|| objTypId == TYPID_SHIELD)
		{
			hitPoints = 0;
			deleteMe = true;
			SpawnExplosionAtCollision(obj);
		}
		else if (objTypId == TYPID_ASTEROID)
		{
			trajectory *= -1;
			ApplyTrajectory ();
			hitPoints -= baseHp / 3;

			SpawnExplosionAtCollision(obj);
		}
		else
		{
			ChangeHitPoints (obj->GetCollisionDmg());

			if (hitPoints <= 0)
				GlobalGameValues::Me().scorePoints += GetScorePoints();
		}

		if (hitPoints <= std::ceil(baseHp / 0.7)
			&& indexImage < 1)
		{
			SwitchImage(subTyp + "_2");
			indexImage++;
		}
		else if (hitPoints <= std::ceil(baseHp * 0.4)
			&& indexImage < 2)
		{
			SwitchImage(subTyp + "_3");
			indexImage++;
		}
	}

	deleteMe = hitPoints <= 0;
}
