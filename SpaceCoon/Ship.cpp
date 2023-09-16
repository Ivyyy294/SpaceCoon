#include "stdafx.h"
#include "Ship.h"
#include "Laser.h"
#include "Input.h"
#include "Explosion.h"

using namespace LarasEngine;

Ship::Ship(const int xPos, const int yPos, const CoreObject::TypId& _typId)
	: GameObject (xPos, yPos, _typId)
	, miniCd (0)
	, shotsCount (0)
	, coolDown (0)
	, maxRotAngle (0.0)
	, maxSpeed (0)
	, acceleration (0.f)
	, shield (nullptr)
{
	collisionOn = true;
	timerIntern = QDateTime::currentMSecsSinceEpoch ();
}

void Ship::Update ()
{
	double lag = TimeInfo::Me ().GetFactor ();
	animations.RunAnimations(lag);

	ApplyHorizontalMovement ();
	ApplyVerticalMovement ();

	if (!velocity.isNull ())
		Translate (velocity * lag);

	if (!shield->IsShieldBurstActive ())
	{
		if (Input::Me ().TestKey (Input::Key::Key_F)
			|| Input::Me ().TestKey (Input::Key::Key_Space))
			Shoot(lag);
	}

	if (shield != nullptr)
		shield->MoveCenter (GetCenter());
}

void Ship::HandleCrash(LarasEngine::GameObject* obj)
{
	GameObject::TypId objTypId = obj->GetTypId ();
	int dmgTaken = 0;

	//Unverwundbar, solange der Alarm anhält
	//oder das Schild noch energie hat
	if (shield->GetHitPoints () > 0
		|| objTypId == TYPID_HP_UP
		|| objTypId == TYPID_SHIELD_UP)
		return;
	else if (objTypId == TYPID_ASTEROID)
		dmgTaken = 1;
	else
		dmgTaken = obj->GetCollisionDmg ();

	if (dmgTaken != 0)
	{
		ChangeHitPoints (dmgTaken);

		if (hitPoints <= 0)
		{
			QRectF objRect = obj->GetImageRect ();

			Explosion::SpawnExplosion (objRect.center ().x (), objRect.topRight ().y ());
			Explosion::SpawnExplosion (objRect.topRight ().x (), objRect.topRight ().y ());
			Explosion::SpawnExplosion (objRect.topLeft ().x (), objRect.topLeft ().y ());
		}
	}

	deleteMe = hitPoints <= 0;
}

double Ship::GetMotionDelay (double val)
{
	if (std::fabs (val) < 0.01)
		return 0.0;
	else
	{
		double tmp = std::max (0.03, std::fabs (val) * deacceleration);
		return (val - tmp * (val < 0.0 ? -1.0 : 1.0));
	}
}

void Ship::ApplyHorizontalMovement ()
{
	if (Input::Me ().TestKey (Input::Key::Key_Left))
		MoveLeft ();

	if (Input::Me ().TestKey (Input::Key::Key_Right))
		MoveRight ();
	
	if (!Input::Me().TestKey (Input::Key::Key_Left)
		&& !Input::Me ().TestKey (Input::Key::Key_Right))
	{
		velocity.setX (GetMotionDelay (velocity.x()));
	}
}

void Ship::ApplyVerticalMovement ()
{
	if (Input::Me ().TestKey (Input::Key::Key_Up))
		MoveTop ();
	if (Input::Me ().TestKey (Input::Key::Key_Down))
		MoveBottom ();
	if (!Input::Me ().TestKey (Input::Key::Key_Up)
		&& !Input::Me ().TestKey (Input::Key::Key_Down))
	{
		velocity.setY (GetMotionDelay (velocity.y ()));
	}
}

void Ship::MoveLeft ()
{
	if (velocity.x() > -maxSpeed)
		velocity += QPointF (-maxSpeed * acceleration, 0.f);
}

void Ship::MoveRight ()
{
	if (velocity.x () < maxSpeed)
		velocity += QPointF (maxSpeed * acceleration, 0.f);
}

void Ship::MoveTop ()
{
	if (velocity.y () > -maxSpeed)
		velocity += QPointF (0.f, -maxSpeed * acceleration);
}

void Ship::MoveBottom ()
{
	if (velocity.y () < maxSpeed)
		velocity += QPointF (0.f, maxSpeed * acceleration);
}

void Ship::Shoot (double lag)
{
	qint64 lagMs = std::floor (lag * LE_OH.GetTargetMsPerUpdate ());
	//qint64 current = QDateTime::currentMSecsSinceEpoch ();

	if (miniCd > 0)
	{
		miniCd -= lagMs;
		return;
	}

	if (shotsCount < laserMaxCount && coolDown <= 0)
	{
		shotsCount++;

		SpawnLaser ();
		miniCd = laserMiniCoolDownMs;
	}
	else if (shotsCount >= laserMaxCount)
	{
		shotsCount = 0;
		coolDown = laserCoolDownMs;
	}
	else
		coolDown -= lagMs;

	//timerIntern = current;
}

void Ship::ReadJson (const QJsonObject& json)
{
	GameObject::ReadJson (json);
	maxSpeed = velocity.y();
	laserCoolDownMs = json["LaserCoolDownMs"].toInt();
	laserMaxCount = json["LaserMaxCount"].toInt();
	laserMiniCoolDownMs = json["LaserMiniCoolDownMs"].toInt();
	hitPointsShield = json["hitpointsShild"].toInt();
	maxRotAngle = json["MaxRotAngle"].toDouble();
	acceleration = json["acceleration"].toDouble ();
	deacceleration = json["deacceleration"].toDouble ();

	velocity = QPointF (0.f, 0.f);
}

void Ship::Init()
{
	if (hitPointsShield > 0)
	{
		shield = new EnergyShield(hitPointsShield);
		LE_ADD_O (shield);
	}
}

void Ship::SpawnLaser()
{
	QRectF rect = GetImageRect ();
	double xPos = rect.center().x();

	if (rotation != 0.0)
	{
		int xOffset = tan(std::fabs(rotation) * PI / 180) * (GetImage().height() / 2);

		if (rotation > 0.0)
			xPos -= xOffset;
		else if (rotation < 0.0)
			xPos += xOffset;
	}

	double yPos = rect.bottomRight().y() + rect.height() / 3;

	LE_ADD_O(new Laser(xPos, yPos, rotation, false));
}
