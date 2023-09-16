#pragma once
#include "Level.h"
#include "HUD.h"

using namespace LarasEngine;

class IntroLevel :
    public Level
{
public:
    IntroLevel();

    void Start() override;
    void ProcessInput() override;
    void DoPostWork() override {};

    virtual LevelId GetLevelId () const override { return LEVELID_INTRO; };
private:
    //HUD hud;
};

