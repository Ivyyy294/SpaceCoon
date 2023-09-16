#pragma once
#include "Animation.h"

class AnimationFacePlayer :
	public LarasEngine::Animation
{
	public:
		AnimationFacePlayer (LarasEngine::GameObject* object, double _maxRotAngle)
			: Animation (object)
			, maxRotAngle (_maxRotAngle)
		{};

		virtual void Update (const size_t& playerInput, const double lag) override;
	protected:
		double maxRotAngle;
};

