#include "stdafx.h"
#include "ActionsAllgemein.h"
#include "GameObject.h"

using namespace LarasEngine;

ActionFacePlayer::ActionFacePlayer (Ship* _ship)
	: ship (_ship)
{
}

bool ActionFacePlayer::Check ()
{
	return true;
}

void ActionFacePlayer::Run (double lag)
{
	GameObject* player = LE_OH.GetObjectVec (TYPID_PLAYER).at (0).get ();

	QRectF playerRect = player->GetImageRect ();
	QRectF shipRect = ship->GetImageRect ();

	double xDis = std::fabs (shipRect.center ().x () - playerRect.center ().x ());
	double yDis = std::fabs (shipRect.center ().y () - playerRect.center ().y ());

	double param = xDis / yDis;
	double alpha = atan (param) * 180 / PI;
	alpha = std::min (alpha, ship->GetMaxRotAngle ());

	if (playerRect.center ().x () > shipRect.center ().x ())
		ship->SetRotation (-alpha);
	else
		ship->SetRotation (alpha);
}