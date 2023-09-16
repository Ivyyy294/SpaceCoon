#pragma once
#include "Event.h"
#include "ShipPlayer.h"
using namespace LarasEngine;

class SpawnHealthBubble :
    public Event
{
public:
    SpawnHealthBubble (size_t t);
    bool CheckCondition();
    void Run();

private:
    size_t last;
    size_t trigger;
    ShipPlayer* player;
};

