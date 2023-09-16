#pragma once
#include "Event.h"
#include "EnemyShip.h"

class SpawnEnemy :
    public LarasEngine::Event
{
public:
    SpawnEnemy (int _trigger);

    bool CheckCondition();
    void Run();

private:
    int last;
    int trigger;
};

