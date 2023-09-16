#pragma once
#include "Animation.h"
class AnimationShipMovement :
	public LarasEngine::Animation
{
	public:
		AnimationShipMovement (Ship* ship);

	protected:
		virtual void Update (const size_t& playerInput, const double lag) override;
};

