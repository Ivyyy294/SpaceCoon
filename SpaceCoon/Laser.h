#pragma once
#include "Projectile.h"
#include <QtMultimedia/qsoundeffect.h>

class Laser :
	public LarasEngine::Projectile
{
public:
	enum Version
	{
		LASER_PLAYER,
		LASER_ENEMY
	};

	Laser (int x, int y, double r, bool _up = true);
	~Laser(void);

	void Update () override;
	void HandleCrash(LarasEngine::GameObject* obj) override;

private:
	const int punkte;
	bool up;
	TypId subTyp;
};

class LaserBlue
	: public LarasEngine::Projectile
{
public:
	LaserBlue (int x, int y, double r, int _speed, bool _up = true);
	~LaserBlue (void) {};

	void Update () override;
	void HandleCrash (LarasEngine::GameObject* obj) override;

private:
	const int punkte;
	bool up;
	TypId subTyp;
};
