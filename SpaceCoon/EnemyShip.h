#pragma once
#include "Ship.h"
#include "Animation.h"
#include "AI.h"
/*
#####ToDo#####
-verhalten an punkte anpassen
#############
*/
using namespace LarasEngine;

class EnemyShip
	: public Ship
	, public AI
{
public:
    EnemyShip (const int xPos, const int yPos, const CoreObject::TypId& _typId = TYPID_ENEMY);
	~EnemyShip() {};

	void HandleCrash(LarasEngine::GameObject* obj) override;
	void Update () override;
	void Init() override;

	//ToDo Verallgemeinern
	double CalculateAngleToPlayer();
protected:
	size_t input;

	void SpawnLaser() override;
	void ReadJson (const QJsonObject& json) override;
	bool IsPlayerInRange();
};
