#pragma once
#include "Animation.h"

class AnimationEntrance :
	public LarasEngine::Animation
{
	public:
		AnimationEntrance (Ship* ship/*, QPointF _dest*/);
	protected:
		virtual void Update (const size_t& playerInput, const double lag) override;

		QPointF dest;
		size_t frameCount;
};

