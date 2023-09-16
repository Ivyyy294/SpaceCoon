#include "stdafx.h"
#include "SpawnBoss.h"
#include "EnemyShip.h"
#include "Boss.h"

using namespace LarasEngine;

SpawnBoss::SpawnBoss(int t)
    : trigger (t)
{
}

bool SpawnBoss::CheckCondition()
{
	int tmp = std::floor (GlobalGameValues::Me ().scorePoints / trigger);

	if (last < tmp)
	{
		last = tmp;
		return true;;
	}

	return false;
}

void SpawnBoss::Run()
{
    LE_ADD_O (new Boss());
    //GlobalGameValues::Me().bossActive = true;
    //active = false;
}
