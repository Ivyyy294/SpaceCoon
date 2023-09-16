#pragma once
#include "C:\dev\MyProjects\LarasEngine\Event.h"
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

