#pragma once

#include "AI.h"

class ActionFacePlayer
	: public LarasEngine::AIAction
{
public:
	ActionFacePlayer (Ship* _ship);

	virtual void Run (double lag) override;
	virtual bool Check () override;

protected:
	Ship* ship;
};