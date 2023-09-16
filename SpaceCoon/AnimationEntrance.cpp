#include "stdafx.h"
#include "AnimationEntrance.h"

AnimationEntrance::AnimationEntrance (Ship* ship)
	: LarasEngine::Animation (ship)
	//, dest (_dest)
{
}

void AnimationEntrance::Update (const size_t& playerInput, const double lag)
{
	++frameCount;

	deleteMe = frameCount > 240;

	if (!deleteMe)
		object->ApplyVelocity (QPointF (0.f, 2.f));
	//QPointF pos = object->GetCenter ();
	//deleteMe = dest == pos;

	//if (!deleteMe)
	//{
	//	QPointF deviation = dest - pos;
	//	QPointF tmpVelocity;

	//	if (pos.x () != dest.x ())
	//	{
	//		double xOffset = std::fabs (object->GetVelocity ().x ());
	//		
	//		if (deviation.x () <= 0.f)
	//		{
	//			xOffset *= -1;

	//			if (deviation.x () > xOffset)
	//				xOffset = deviation.x ();
	//		}
	//		else if (deviation.x () < xOffset)
	//			xOffset = deviation.x ();
	//		
	//		tmpVelocity.setX (xOffset);
	//	}

	//	if (pos.y () != dest.y ())
	//	{
	//		double yOffset = std::fabs (object->GetVelocity ().y ());

	//		if (deviation.y () <= 0.f)
	//		{
	//			yOffset *= -1;

	//			if (deviation.y () > yOffset)
	//				yOffset = deviation.y ();
	//		}
	//		else if (deviation.y() < yOffset)
	//			yOffset = deviation.y ();

	//		tmpVelocity.setY (yOffset);
	//	}

	//	object->ApplyVelocity (tmpVelocity);
	//	//ship->input |= Input::Key_Down;
	//}
}
