#include "stdafx.h"
#include "ShipPlayer.h"
#include "Explosion.h"
#include "Input.h"

using namespace LarasEngine;

ShipPlayer::ShipPlayer ()
	: Ship(0, 0, TYPID_PLAYER)
	, maxHitPoints (0)
	, maxHitpointsShild (0)
{
	QRectF rect = GetImageRect();
	int xPos = (screenW - rect.width()) / 2;
	int yPos = (screenH - rect.width() - 150);
	SetPosition(QPoint(xPos, yPos));	
	collisionOn = true;
	animations.AddAnimation (new AnimationShipMove (this));
}

ShipPlayer::~ShipPlayer(void)
{
}

void ShipPlayer::HandleCrash(GameObject* obj)
{
	GameObject::TypId objTypId = obj->GetTypId ();
	int dmgTaken = 0;

	//Unverwundbar, solange der Alarm anhält
	//oder das Schild noch energie hat
	if (shield->GetHitPoints() > 0)
		return;
	else if (objTypId == TYPID_ROCKET
		|| objTypId == TYPID_ASTEROID)
		dmgTaken = 1;
	else
		dmgTaken = obj->GetCollisionDmg();

	if (dmgTaken != 0)
	{
		ChangeHitPoints (dmgTaken);
		Explosion::SpawnExplosion2 (GetAreaOfCollision (obj));
	}
}

void ShipPlayer::Update ()
{
	if (hitPoints > 0)
	{
		Ship::Update ();

		if ((Input::Me ().TestKey (Input::Key::Key_D)
			|| Input::Me ().TestKey (Input::Key::Key_Q)) && shield != nullptr)
			shield->ShieldBurst ();
	}
	else
		DrawDeathAnimation ();
}

float ShipPlayer::GetShieldIntegrity()
{
	if (shield != nullptr)
	{
		float a = shield->GetHitPoints();
		float b = shield->GetMaxHp();
		float tmp = a / b;
		return tmp;
	}
	else
		return 0.f;
}

void ShipPlayer::RechargeShield(const int v)
{
	int heal = std::min (int (maxHitpointsShild - shield->GetHitPoints()), v);
	shield->ChangeHitPoints(-heal);
}

size_t ShipPlayer::GetHitPointsShield () const
{
	size_t r = 0;

	if (shield != nullptr)
		r = shield->GetHitPoints ();

	return r;
}

void ShipPlayer::ReadJson (const QJsonObject& json)
{
	Ship::ReadJson (json);
	GlobalGameValues::Me().playerHealth = hitPoints;

	maxHitPoints = json["MaxHitPoints"].toInt ();
	maxHitpointsShild = json["MaxHitpointsShild"].toInt ();
	rotationSpeed = json["rotationSpeed"].toDouble ();
}

void ShipPlayer::SpawnLaser()
{
	QRectF rect = GetImageRect ();
	int yOffset = rect.height () * 0.2;

	QLineF l (rect.center (), QPointF (rect.center ().x (), rect.top() - yOffset));

	if (rotation != 0.0)
		l.setAngle (l.angle() - rotation);

	static_cast <Laser*> (LE_ADD_O(new Laser (l.x2 (), l.y2 (), rotation, true)))->SetLaunchVelocity (velocity);
}

void ShipPlayer::DrawDeathAnimation ()
{
	static double timePast = 0.f;
	static char stage = 0;
	const double max = 0.25f;

	QRectF rect = GetImageRect ();

	if (stage == 0)
	{
		GlobalGameValues::Me ().showHUDDmgIndicator = true;
		++stage;
		timePast = 0.f;
	}
	else if (stage == 1 && timePast >= max)
	{
		Explosion::SpawnExplosion2 (rect.topRight ());
		Explosion::SpawnExplosion2 (rect.topLeft ());
		Explosion::SpawnExplosion2 (rect.bottomRight ());
		Explosion::SpawnExplosion2 (rect.bottomLeft ());
		visible = false;
		++stage;
		timePast = 0.f;
	}
	else if (stage == 2 && timePast >= max)
	{
		Explosion::SpawnExplosion2 (rect);
		++stage;
		timePast = 0.f;
	}
	else if (stage == 3 && timePast >= max * 3)
	{
		stage = 0;
		deleteMe = true;
	}

	timePast += TimeInfo::Me ().GetDeltaTime ();
}

void ShipPlayer::Translate (const QPointF& _point)
{
	QRectF rect = GetImageRect ();
	QPointF tmp = _point;

	//Right left
	if (rect.topRight ().x () + tmp.x () >= screenW
		|| rect.topLeft ().x () + tmp.x () <= 0.f)
		tmp.setX (0);

	//top  bottom
	if (rect.bottomRight ().y () + tmp.y () >= screenH
		|| rect.topRight ().y () + tmp.y () <= 0.f)
		tmp.setY (0);

	if (!tmp.isNull ())
		GameObject::Translate (tmp);
}

void ShipPlayer::ChangeHitPoints (const int damage)
{
	GameObject::ChangeHitPoints (damage);

	GlobalGameValues::Me ().playerHealth = hitPoints;

	if (damage > 0)
		GlobalGameValues::Me ().showHUDDmgIndicator = true;

	if (GlobalGameValues::Me ().playerHealth <= 0)
	{
		GlobalGameValues::Me ().showHUDDmgIndicator = true;
		//deleteMe = true;
	}
}

AnimationShipMove::AnimationShipMove (Ship* ship)
	: Animation (0, ship, "Move")
{
	done = false;
}

void AnimationShipMove::Run (double lag)
{
	ShipPlayer* ship = static_cast <ShipPlayer*> (object);
	const double maxAngle = ship->maxRotAngle;
	double angle = ship->GetRotation ();
	const float rotationSpeed = ship->GetRotationSped () * TimeInfo::Me().GetFactor();

	bool turnLeft = false;
	bool turnRight = false;

	if (!done)
	{
		if (Input::Me ().TestKey (Input::Key::Key_Left))
			turnLeft = true;
		else if (Input::Me ().TestKey (Input::Key::Key_Right))
			turnRight = true;
		else
		{
			double tmp = rotationSpeed * 0.5;
			
			if (std::fabs (angle) < tmp)
				angle = 0.0;
			else
			{
				if (angle < 0.0)
					angle += rotationSpeed * 0.5;
				else if (angle > 0.0)
					angle -= rotationSpeed* 0.5;
			}
		}

		//Turn left
		if (turnLeft && angle > -maxAngle)
			angle -= rotationSpeed;

		//Turn right
		if (turnRight && angle < maxAngle)
			angle += rotationSpeed;


		ship->SetRotation (angle);
	}
	else
		ship->SetRotation (0.0);
}