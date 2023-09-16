#pragma once

#include "ship.h"
#include "Animation.h"
#include "GlobalGameValues.h"

/*
#####ToDo#####
-Schutzschilde
-verschiedene modelle für low life
#############
*/

class ShipPlayer: public Ship
{
public:
	ShipPlayer();
	~ShipPlayer(void);

	void HandleCrash(GameObject* obj);
	void Update () override;
	
	inline float GetRotationSped () { return rotationSpeed; };
	float GetShieldIntegrity();
	void RechargeShield(const int v);
	size_t GetHitPointsShield () const;
	inline size_t GetMaxHitPoints () const { return maxHitPoints; };
	inline size_t GetMaxHitPointsShield () const { return maxHitpointsShild; };
	void Translate (const QPointF& _point) override;
	void ChangeHitPoints (const int damage) override;

	static GameObject* CreateMethod () { return new ShipPlayer; };
protected:
	virtual void ReadJson (const QJsonObject& json) override;
	virtual void SpawnLaser() override;
	void DrawDeathAnimation ();
	
	float rotationSpeed{ 0.f };
	size_t maxHitPoints;
	size_t maxHitpointsShild;
};

class AnimationShipMove
	: public LarasEngine::Animation
{
public:
	AnimationShipMove (Ship* ship);
	~AnimationShipMove () {};
protected:
	virtual void Run (double lag) override;
};