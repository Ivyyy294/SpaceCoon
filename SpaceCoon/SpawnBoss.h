#pragma once
#include "Event.h"

class SpawnBoss :
    public LarasEngine::Event
{
public:
    SpawnBoss(int t);

    bool CheckCondition();
    void Run();

private:
    int trigger;
	 int last{ 0 };
};

