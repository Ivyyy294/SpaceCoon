#pragma once
#include "Event.h"

class SpawnMeteorit :
    public LarasEngine::Event
{
public:
    SpawnMeteorit();

    bool CheckCondition();
    void Run();
private:
    int maxCount;
};

