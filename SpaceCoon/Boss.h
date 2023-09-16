#pragma once
#include "EnemyShip.h"
#include "EnergyShield.h"
#include "Input.h"

using namespace LarasEngine;


class Boss :
    public EnemyShip
{
public:
	Boss();

	void Init() override;
	virtual void ReadJson (const QJsonObject& json) override;
	void HandleCrash (LarasEngine::GameObject* obj) override;
	inline EnergyShield* GetShield () { return shield; };
protected:
	virtual void SpawnLaser () override;

	int salvoCount;
	double salvoAngle;
};

