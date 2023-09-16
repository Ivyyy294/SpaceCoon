#pragma once
#include "AI.h"
#include "Boss.h"
#include "EnergyShield.h"
#include "StaticField.h"

class ActionBossSpawnFriends :
	public LarasEngine::AIAction
{
public:
	ActionBossSpawnFriends (Boss* _boss);
	virtual void Run (double lag) override;
	virtual bool Check () override;

private:
	bool friendsSpawned;
	Boss* boss;
	int baseHp;
};

class ActionBossShield
	: public LarasEngine::AIPrimaryAction
{
public:
	ActionBossShield (Boss* _boss);
	~ActionBossShield ();
	virtual void Run (double lag) override;
	virtual bool Check () override;
private:
	Boss* boss;
	double lifeTime;
	double explosionTimer;
	int baseHp;
	StaticField* staticField;
};
