#include "stdafx.h"
#include "AnimationFacePlayer.h"

void AnimationFacePlayer::Update (const size_t& playerInput, const double lag)
{
	auto& playerVec = LE_OH.GetObjectVec (TYPID_PLAYER);

	if (!playerVec.empty ())
	{
		LarasEngine::GameObject* player = playerVec.at (0).get ();
		double xDis = std::fabs (object->GetRect ().center ().x () - player->GetRect ().center ().x ());
		double yDis = std::fabs (object->GetRect ().center ().y () - player->GetRect ().center ().y ());

		double param = xDis / yDis;
		double alpha = atan (param) * 180 / PI;
		alpha = std::min (alpha, maxRotAngle);

		if (player->GetRect ().center ().x () > object->GetRect ().center ().x ())
			object->SetRotation (-alpha);
		else
			object->SetRotation (alpha);
	}
}
