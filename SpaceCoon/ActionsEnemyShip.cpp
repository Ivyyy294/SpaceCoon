#include "stdafx.h"
#include "ActionsEnemyShip.h"
#include <qline.h>

ActionShipEntrance::ActionShipEntrance (GameObject* _object)
	: AIPrimaryAction (false)
	, frameNr (0)
	, object (_object)
{
}

void ActionShipEntrance::Run (double lag)
{
	done = ++frameNr > 120;

	EnemyShip* ship = static_cast <EnemyShip*> (object);

	if (!done)
		ship->Translate (QPointF (0.f, 2.f));
}

bool ActionShipEntrance::Check ()
{
	return !done;
}


ActionShootPlayer::ActionShootPlayer (EnemyShip* _ship)
	: ship (_ship)
{
}

void ActionShootPlayer::Run (double lag)
{
	ship->Shoot (lag);
}

bool ActionShootPlayer::Check ()
{
	GameObject* player = LE_OH.GetObjectVec (TYPID_PLAYER).at (0).get ();

	double angleToPlayer = ship->CalculateAngleToPlayer ();

	return angleToPlayer <= ship->GetMaxRotAngle () && angleToPlayer >= (ship->GetMaxRotAngle () * -1);
}

ActionShipEvade::ActionShipEvade (GameObject* _object)
	: AIPrimaryAction(true)
	, object (_object)
	, frameNr (0)
{
	r1 = GetRadiusToRectF (_object->GetImageRect());
	objectCenter = _object->GetCenter();
}

void ActionShipEvade::Run (double lag)
{
	double xOffset = 2.f;
	objectCenter = object->GetCenter();

	CollisionInfo& mostUrgent = collisionObjects.at (0);

	for (size_t i = 1; i < collisionObjects.size (); ++i)
	{
		if (collisionObjects.at (i).dist < mostUrgent.dist)
			mostUrgent = collisionObjects.at (i);
	}

	if (mostUrgent.center.x () > objectCenter.x ())
		currentInput = LarasEngine::Input::Key::Key_Left;
	else if (mostUrgent.center.x () < objectCenter.x ())
		currentInput = LarasEngine::Input::Key::Key_Right;

	bool leftPossible = objectCenter.x () - r1 - xOffset > 0.f;
	bool rightPossible = objectCenter.x () + r1 + xOffset < LE_OH.GetPrimaryScreenGeometry ().width ();

	if (leftPossible && currentInput == LarasEngine::Input::Key::Key_Left)
		object->Translate (QPointF (xOffset * -1.f, 0.f) * lag);
	else if (rightPossible && currentInput == LarasEngine::Input::Key::Key_Right)
		object->Translate (QPointF (xOffset, 0.f) * lag);

	done = true;
}

bool ActionShipEvade::Check ()
{
	collisionObjects.clear ();
	objectCenter = object->GetCenter();

	for (const auto& i : LE_OH.GetObjectVec (TYPID_ASTEROID))
	{
		CollisionInfo c;

		if (IsCollisionPossible (*i, c))
			collisionObjects.push_back (c);
	}

	if (collisionObjects.size () > 0)
		done = false;

	return collisionObjects.size() > 0;
}

bool ActionShipEvade::IsCollisionPossible (const GameObject& o, CollisionInfo& collision) const
{
	QRectF rect = o.GetCollisionRect();
	QPointF oRectCenter = rect.center ();
	collision.r = GetRadiusToRectF (rect);

	if (oRectCenter.y() - collision.r <= objectCenter.y() + r1)
	{
		QLineF b (QPointF(0.f, rect.center().y()), QPointF (0.f, objectCenter.y()));

		const Meteorit* m = static_cast <const Meteorit*> (&o);

		double tanA = tan (std::fabs (m->GetTrajectory()) * PI / 180);
		double a = tanA * b.length ();

		if (m->GetTrajectory () < 0.f)
			a *= -1.f;

		collision.center = QPointF (rect.center ().x () + a, objectCenter.y ());

		QLineF dist (objectCenter , collision.center);

		collision.dist = dist.length() - r1 - collision.r;

		return collision.dist <= 0.f;
	}

	return false;
}

double ActionShipEvade::GetRadiusToRectF (const QRectF& rect) const
{
	QLineF line (rect.center (), rect.topRight ());
	return line.length();
}
