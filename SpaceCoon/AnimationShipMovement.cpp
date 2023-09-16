#include "stdafx.h"
#include "Input.h"
#include "AnimationShipMovement.h"

AnimationShipMovement::AnimationShipMovement (Ship* ship)
	: LarasEngine::Animation (ship)
{
}

void AnimationShipMovement::Update (const size_t& playerInput, const double lag)
{
	Ship* ship = static_cast <Ship*> (object);
	const double maxAngle = ship->GetMaxRotAngle();
	double angle = ship->GetRotation ();

	bool turnLeft = false;
	bool turnRight = false;

	char input = ship->GetInput();

	if (input & LarasEngine::Input::Key_Left)
		turnLeft = true;
	else if (input & LarasEngine::Input::Key_Right)
		turnRight = true;
	else
	{
		if (angle < 0.0)
			turnRight = true;
		else if (angle > 0.0)
			turnLeft = true;
	}

	//Turn left
	if (turnLeft && angle > -maxAngle)
		--angle;

	//Turn right
	if (turnRight && angle < maxAngle)
		++angle;


	ship->SetRotation (angle);
}
