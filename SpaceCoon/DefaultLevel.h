#pragma once
#include "Level.h"
#include "HUD.h"
#include "ShipPlayer.h"

using namespace LarasEngine;

class DefaultLevel
	: public Level
{
public:
	DefaultLevel ();
	~DefaultLevel ();

	void Start() override;
	void ProcessInput () override;
	void DoPostWork() override;

	virtual LevelId GetLevelId () const override { return LEVELID_NORMAL; };

	static Level* CreateMethod () { return new DefaultLevel; };

	ShipPlayer* player;
};

