#include "stdafx.h"
#include "SpawnEnemy.h"

using namespace LarasEngine;

SpawnEnemy::SpawnEnemy(int _trigger)
    : trigger (_trigger)
    , last (0)
{
}

bool SpawnEnemy::CheckCondition()
{
    int tmp = std::floor(GlobalGameValues::Me().scorePoints / trigger);

    if (last < tmp)
    {
        last = tmp;
        return LE_OH.GetObjectVec (TYPID_ENEMY).size() < 4
			  && LE_OH.GetObjectVec (TYPID_BOSS).empty();
    }

    return false;
}

void SpawnEnemy::Run()
{
    int wDesktop = LE_OH.GetPrimaryScreenGeometry().width();
    int margin = wDesktop / 8;
    int xPos = margin + rand () % (wDesktop - margin * 2);
    int yPos = -100;
    LE_ADD_O(new EnemyShip(xPos, yPos));
    //active = false;
}
