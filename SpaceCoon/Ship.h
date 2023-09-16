#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "EnergyShield.h"

class AnimationShipMove;

class Ship : public LarasEngine::GameObject
{
	friend AnimationShipMove;
public:
	Ship(const int xPos, const int yPos, const CoreObject::TypId& _typId);

	void Update () override;
	void HandleCrash (LarasEngine::GameObject* obj) override;

	inline double GetMaxRotAngle () const { return maxRotAngle; };
	virtual void Shoot(double lag);
protected:
	double maxSpeed;
	int laserMiniCoolDownMs;
	int laserCoolDownMs;
	int laserMaxCount;
	int hitPointsShield;
	double 	maxRotAngle;
	double acceleration;
	double deacceleration{ 0.01 };
	LarasEngine::AnimationHandler animations;
	EnergyShield* shield;
	int shotsCount;

	virtual void ReadJson (const QJsonObject& json) override;
	virtual void Init() override;
	virtual void SpawnLaser();
	
	void ApplyHorizontalMovement ();
	void ApplyVerticalMovement ();
private:
	double GetMotionDelay (double val);
	void MoveLeft ();
	void MoveRight ();
	void MoveTop ();
	void MoveBottom ();

	qint64 miniCd{ 0 };
	qint64 coolDown{ 0 };
	qint64 timerIntern;
};
