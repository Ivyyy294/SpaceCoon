#pragma once

#include "Projectile.h"

class Rocket
	: public LarasEngine::Projectile
{
public:
	Rocket (int x, int y, double r);
	void HandleCrash (LarasEngine::GameObject* obj) override;
	void Update () override;
};
